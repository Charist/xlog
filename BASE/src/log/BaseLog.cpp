#ifdef __ANDROID__
#include <android/log.h>
#endif

#include "log/BaseLog.h"
#include <assert.h>
#include <poco/File.h>
#include <poco/DateTime.h>
#include <poco/DateTimeFormatter.h>
#include <Poco/ScopedLock.h>
#include <Poco/Timezone.h>

#ifdef WIN32
#define snprintf _snprintf
#endif

namespace mstp {


static const int kOneLogBuffSize = 2048;
static const unsigned int kBufferBlockLength = 150 * 1024;

LogBuffer* BaseLog::m_pLogBuff = nullptr;
Poco::Mutex BaseLog::m_mutexLogBuffer;
Poco::Mutex BaseLog::m_mutexWriteFile;

Poco::Condition BaseLog::m_condWriteFile;
WriteLogFileRunnable BaseLog::m_runnable;
Poco::SharedMemory BaseLog::m_mmap;
bool BaseLog::m_bIsOpen = false;
std::string BaseLog::m_dir;
LogFile* BaseLog::m_logFile = nullptr;
LogSyncMode BaseLog::m_syncMode;

BaseLog::BaseLog(const char* dir, const char* nameprefix, LogSyncMode mode, LogLevel level) : m_level(level)
    , m_bConsoleEnable(true)
{
    m_dir = dir;
    m_syncMode = mode;

    open(mode);
    m_logFile = new LogFile(dir, nameprefix);
}

BaseLog::~BaseLog()
{
    if (nullptr == m_mmap.begin()) // not use the mmap 
    {
        delete (unsigned char*)m_pLogBuff->GetData().Ptr();
    }

    if (nullptr != m_pLogBuff)
    {
        delete m_pLogBuff;
        m_pLogBuff = nullptr;
    }
    if (nullptr != m_logFile)
    {
        delete m_logFile;
        m_logFile = nullptr;
    }
}

void BaseLog::open(LogSyncMode mode)
{
    assert(!m_dir.empty());

    if (m_bIsOpen) {
        //__writetips2file("appender has already been opened. _dir:%s _nameprefix:%s", _dir, _nameprefix);
        return;
    }
    m_bIsOpen = true;

    Poco::File tmpDir(m_dir);
    if (!tmpDir.exists() || 
        (tmpDir.exists() && !tmpDir.isDirectory()))
    {
        tmpDir.createDirectory();
    }
    
    std::string mmap_file_path = m_dir + "/" + "cache.mmap2";

    //Poco::SharedMemory mmapFile;
    if (__openMmapFile(mmap_file_path.c_str(), kBufferBlockLength, m_mmap)) // mmap ok
    { 
        m_pLogBuff = new LogBuffer(m_mmap.begin(), kBufferBlockLength, true);
    }
    else
    {
        char* buffer = new char[kBufferBlockLength];
        memset(buffer, 0, kBufferBlockLength);
        m_pLogBuff = new LogBuffer(buffer, kBufferBlockLength, true);
    }
    __setMode(mode);

    assert(nullptr != m_pLogBuff->GetData().Ptr());
}

void BaseLog::write(const LogInfo& info, const char* format, const va_list& list)
{
    if (info.level > m_level)
    {
        return;
    }

    char buf[kOneLogBuffSize] = {0};
    int headerLen = __logFormater(info, buf, kOneLogBuffSize);

    vsnprintf(buf + headerLen, kOneLogBuffSize - headerLen, format, list);

    buf[strlen(buf)] = '\n';
    __write(buf, strlen(buf), info.level);

    if (m_bConsoleEnable)
    {
        _write_console(buf, strlen(buf), info);
    }
}

int BaseLog::__logFormater(const LogInfo& info, char* outData, int outDataLen)
{
    assert(outData);
    static const char* levelStrings[] = {
        " ",  // none
        "F",  // fatal
        "E",  // error
        "W",  // warn
        "I",  // info
        "D",  // debug
        "T",   //trace
    };

    Poco::LocalDateTime now;
    std::string timeStr = Poco::DateTimeFormatter::format(now.timestamp(), "%H:%M:%S.%i", Poco::Timezone::tzd());
    static const int logHeaderLen = 256;
    char buf[logHeaderLen] = {0};
#ifdef __ANDROID__
    int dataLen = snprintf(buf, logHeaderLen, "%s [%s][%lu] [%s] %s::%s line:%d ", timeStr.c_str(), levelStrings[info.level],
        info.tId, info.tag, info.class_name, info.func_name, info.line);
#else
    int dataLen = snprintf(buf, logHeaderLen, "%s [%s][%lu] %s::%s line:%d ", timeStr.c_str(), levelStrings[info.level],
        info.tId, info.filename, info.func_name, info.line);
#endif
    assert(outDataLen > dataLen);
    
    memcpy(outData, buf, dataLen);
    return dataLen;
}

void BaseLog::__write(const char* data, int len, LogLevel level)
{
    if (LOG_WRITE_MODE_SYNC == m_syncMode)
    {
        __writeSync(data, len);
    }
    else
    {
        __writeASync(data, len, level);
    }
}

void BaseLog::__writeSync(const char* data, int len)
{
    char buffer_crypt[kOneLogBuffSize] = {0};
    size_t outLen = 16 * 1024;

    if (!LogBuffer::OutputBuffer(data, len, buffer_crypt, outLen))
        return;

    __log2file(buffer_crypt, len);
}

void BaseLog::__writeASync(const char* data, int len, LogLevel level)
{
    Poco::Mutex::ScopedLock lock(m_mutexLogBuffer);
    if (nullptr == m_pLogBuff || nullptr == data || len <= 0) 
        return;

    if (m_pLogBuff->GetData().Length() >= kBufferBlockLength*4/5) 
    {
        char temp[128] = {0};
        int ret = snprintf(temp, sizeof(temp), "[F][ sg_buffer_async.Length() >= BUFFER_BLOCK_LENTH*4/5, len: %d\n", (int)m_pLogBuff->GetData().Length());
        m_pLogBuff->Write(temp, ret);
    }

    if (!m_pLogBuff->Write(data, len)) 
        return;


    if (m_pLogBuff->GetData().Length() >= kBufferBlockLength*1/3 || LOG_LEVEL_ERROR >= level) {
        m_condWriteFile.broadcast();
    }

}

void BaseLog::flush()
{
    m_condWriteFile.broadcast();
}

void BaseLog::close()
{
    m_bIsOpen = false;
    m_condWriteFile.broadcast();
    if (m_threadLoger.isRunning())
    {
        m_threadLoger.join();
    }
    m_logFile->close();
}

void BaseLog::__setMode(LogSyncMode mode)
{
    m_syncMode = mode;

    m_condWriteFile.broadcast();

    if (LOG_WRITE_MODE_ASYNC == m_syncMode && !m_threadLoger.isRunning()) 
    {
        m_threadLoger.start(m_runnable);
    }
}


bool BaseLog::__openMmapFile(const char* _filepath, unsigned int _size, Poco::SharedMemory& sm) 
{
    //Shared memory is not supported on Android.
#ifdef __ANDROID__
    return false;
#endif

    if (NULL == _filepath || 0 == strnlen(_filepath, 128) || 0 == _size) 
    {
        return false;
    }
    
    FILE* file = fopen(_filepath, "wb+"); //rb+ 权限冲突
    if (NULL == file) 
    {
        printf("fopen return NULL, error=%d， %s /n", errno, strerror(errno)); // log2file
        remove(_filepath);
        return false;
    }

    // initial data of file, set the data with 0, otherwise can't write the memory of the mmap
    char* zero_data = new char[_size];
    memset(zero_data, 0, _size);
    if (_size != fwrite(zero_data, sizeof(char), _size, file)) 
    {
        fclose(file);
        remove(_filepath);
        delete[] zero_data;
        return false;
    }
    fclose(file);
    delete[] zero_data;

    sm = Poco::SharedMemory(Poco::File(_filepath), Poco::SharedMemory::AM_WRITE);
    
    return sm.begin() != nullptr;
    
}

void BaseLog::__log2file(const void* data, int len)
{
    if (NULL == data || 0 == len || BaseLog::m_dir.empty()) {
        return;
    }

    Poco::Mutex::ScopedLock lock_file(BaseLog::m_mutexWriteFile);

    BaseLog::m_logFile->write2file(data, len);
  
    if (LOG_WRITE_MODE_ASYNC == BaseLog::m_syncMode) 
    {
        BaseLog::m_logFile->close();
    }
}

void BaseLog::_write_console(const char* data, int len, const LogInfo& info)
{
#ifdef __APPLE__ 
    fprintf(stderr, "%s", data);
#elif __ANDROID__
    __android_log_print(8 - info.level, info.tag, "%s", data);
#else
    ::OutputDebugStringA(data);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////// WriteLogFileRunnable /////////////////////////

void WriteLogFileRunnable::run()
{
    while (true) 
    {
        AutoBuffer tmp;
        {
            Poco::Mutex::ScopedLock buffer_lock(BaseLog::m_mutexLogBuffer); 

            if (NULL == BaseLog::m_pLogBuff)
            {
                break;
            }

            BaseLog::m_pLogBuff->Flush(tmp);
        }

        if (nullptr != tmp.Ptr())  
            BaseLog::__log2file(tmp.Ptr(), tmp.Length());


        if (!BaseLog::m_bIsOpen) 
            break;

        // android 平台必须先lock, wait 后再unlock, 否则wait 会一直lock 住conditionMutex 
        Poco::Mutex::ScopedLock buffer_lock(BaseLog::m_mutexLogBuffer);
        BaseLog::m_condWriteFile.wait(BaseLog::m_mutexLogBuffer, 15 * 60 * 1000);
    }
}

///////////////////////////////////////////////////////////////////////////////


} /* namespace mstp */


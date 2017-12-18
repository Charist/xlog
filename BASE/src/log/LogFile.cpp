#ifdef __ANDROID__
#include <android/log.h>
#endif

#include "log/LogFile.h"
#include <Poco/DateTimeFormatter.h>

namespace mstp {
    
    
LogFile::LogFile(const std::string dir, const std::string prefix) : m_dir(dir), m_prefix(prefix), m_logFile(nullptr)
{

}
LogFile::~LogFile()
{
    if (nullptr != m_logFile)
    {
        close();
    }
}

bool LogFile::write2file(const void* data, int len)
{
    if (NULL == data || 0 == len || m_dir.empty()) {
        return false;
    }

    if (__openlogfile()) 
    {
        if (1 != fwrite(data, len, 1, m_logFile)) 
        {
            int err = ferror(m_logFile);
            fprintf(stderr, "__writefile failed, %d /n", err); // consoleLog
            return false;
        }
        return true;
    }
    return false;
}

bool LogFile::__openlogfile() 
{
    Poco::DateTime now;
    std::string timeStr = Poco::DateTimeFormatter::format(now, "%Y_%n_%e");
    std::string logPath = m_dir + "/" + m_prefix + "_" + timeStr + ".log";

    if (nullptr != m_logFile)
    {
        if (m_openFileTime.day() == now.day() && m_openFileTime.month() == now.month() && m_openFileTime.year() == now.year()) 
        {
            return true;
        }
        else
        {
            fclose(m_logFile);
            m_logFile = nullptr;
        }
    }
    m_logFile = fopen(logPath.c_str(), "ab");
    if (nullptr == m_logFile)
    {
#ifndef __ANDROID__
        fprintf(stderr, "fopen return NULL, error=%d， %s /n", errno, strerror(errno)); // consoleLog
#else // !ANDROID  
    __android_log_print(ANDROID_LOG_ERROR, "fopen return NULL", "log name:%s", logPath.c_str());
#endif
    }
    m_openFileTime = now;
    return m_logFile != nullptr;
}

void LogFile::close() 
{
    if (nullptr == m_logFile) 
        return;

    fclose(m_logFile);
    m_logFile = nullptr;
}
   

} /* namespace mstp */


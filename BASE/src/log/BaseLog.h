/*
 * LogBuffer.h
 *
 *  Created on: 2017-3-23
 *  日志模块类，实现同步、异步写文件；文件内存映射
 *
 */
#pragma once
#include <Poco/SharedMemory.h>
#include <Poco/Mutex.h>
#include <Poco/Condition.h>
#include <Poco/Thread.h>
#include <Poco/DateTime.h>

#include "log/LogBuffer.h"
#include "log/LogFile.h"

namespace mstp {


enum LogLevel
{
    LOG_LEVEL_SILENCE = 0,
    LOG_LEVEL_FATAL = 1,
    LOG_LEVEL_ERROR = 2,
    LOG_LEVEL_WARNING = 3,
    LOG_LEVEL_INFO = 4,
    LOG_LEVEL_DEBUG = 5,
    LOG_LEVEL_TRACE = 6,

    LOG_LEVEL_MAX
} ;

enum LogSyncMode
{
    LOG_WRITE_MODE_SYNC,
    LOG_WRITE_MODE_ASYNC
};

struct LogInfo{
    LogLevel level;
    const char* filename;
    const char* class_name;
    const char* func_name;
    const char* tag;
    int line;
    unsigned long tId;
};

class WriteLogFileRunnable : public Poco::Runnable
{

public:
    virtual void run();
};

class BaseLog
{
    friend WriteLogFileRunnable;
public:
    BaseLog(const char* dir, const char* nameprefix, LogSyncMode mode = LOG_WRITE_MODE_SYNC, LogLevel level = LOG_LEVEL_INFO);
    ~BaseLog();

public:

    void open(LogSyncMode mode);
    
    void write(const LogInfo& info, const char* _format, const va_list& list);

    void flush();
    void close();

    bool isOpened() {return m_bIsOpen;}

    void enableConsole(bool enable) { m_bConsoleEnable = enable; }
private:
    void __setMode(LogSyncMode mode);
    bool __openMmapFile(const char* _filepath, unsigned int _size, Poco::SharedMemory&);

    int __logFormater(const LogInfo& info, char* outData, int dataLen);

    void __write(const char* data, int len, LogLevel level);

    //输出控制台
    void _write_console(const char* data, int len, const LogInfo&);

    //同步、异步写文件
    void __writeSync(const char* data, int len);
    void __writeASync(const char* data, int len, LogLevel level);

    static void __log2file(const void* data, int len);

    static bool __openlogfile();
 
    static bool __writefile(const void* _data, size_t _len, FILE* _file);

    static void __closelogfile();

private:
    LogLevel m_level;
    bool m_bConsoleEnable;

    static LogSyncMode m_syncMode;
    static std::string m_dir;

    static bool m_bIsOpen;
    
    static Poco::SharedMemory m_mmap;
    static LogBuffer* m_pLogBuff;

    static Poco::Mutex m_mutexLogBuffer;
    static Poco::Mutex m_mutexWriteFile;

    static Poco::Condition m_condWriteFile;

    Poco::Thread m_threadLoger;

    static WriteLogFileRunnable m_runnable;

    static LogFile* m_logFile;

};


} /* namespace mstp */


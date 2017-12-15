
#include "log/MarsLog.h"

namespace mstp {



static BaseLog* sg_pBaseLog = nullptr;

void init_mstp_log(const char* dir, LogSyncMode mode, LogLevel level)
{
    sg_pBaseLog = new BaseLog(dir, "sdk", mode, level);
}

void close_mstp_log()
{
    if (nullptr != sg_pBaseLog)
    {
        sg_pBaseLog->close();
        delete sg_pBaseLog;
        sg_pBaseLog = nullptr;
    }
}
#ifdef __ANDROID__
void print_mstp_log(int level, const char* tag, const char* file_name, const char* class_name, const char* function_name, int line, const char* fmt, ...)
#else
void print_mstp_log(int level, const char* file_name, const char* class_name, const char* function_name, int line, const char* fmt, ...)
#endif
{
    if (nullptr != sg_pBaseLog)
    {
        LogInfo info;
        info.filename = file_name;
        info.class_name = class_name;
        info.func_name = function_name;
        info.level = (LogLevel)level;
        info.tId = Poco::Thread::currentTid();
        info.line = line;
#ifdef __ANDROID__
        info.tag = tag;
#endif
        va_list valist;
        va_start(valist, fmt);
        sg_pBaseLog->write(info, fmt, valist);
        va_end(valist);

    }
}

void flush_mstp_log()
{
    if (nullptr != sg_pBaseLog)
    {
        sg_pBaseLog->flush();
    }

}

void enable_console_log(bool enable)
{
    if (nullptr != sg_pBaseLog)
    {
        sg_pBaseLog->enableConsole(enable);
    }
}


} /* namespace mstp */


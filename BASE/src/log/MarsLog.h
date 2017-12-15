#pragma once
#ifdef __ANDROID__
#include <android/log.h>
#endif
#include "log/BaseLog.h"

namespace mstp {

void init_mstp_log(const char* dir, LogSyncMode mode = LOG_WRITE_MODE_ASYNC, LogLevel level = LOG_LEVEL_INFO);
void close_mstp_log(); 

#ifdef __ANDROID__
void print_mstp_log(int level, const char* tag, const char* file_name, const char* class_name, const char* function_name, int line, const char* fmt, ...);
#else
void print_mstp_log(int level, const char* file_name, const char* class_name, const char* function_name, int line, const char* fmt, ...);
#endif
void flush_mstp_log();
void enable_console_log(bool enable);

#ifdef WIN32
#define log_f(fmt, ...) print_mstp_log(LOG_LEVEL_FATAL, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define log_e(fmt, ...) print_mstp_log(LOG_LEVEL_ERROR, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define log_w(fmt, ...) print_mstp_log(LOG_LEVEL_WARNING, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define log_i(fmt, ...) print_mstp_log(LOG_LEVEL_INFO, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define log_d(fmt, ...) print_mstp_log(LOG_LEVEL_DEBUG, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define log_t(fmt, ...) print_mstp_log(LOG_LEVEL_TRACE, __FILE__, "", __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#elif __ANDROID__
#define log_f(fmt, a...) print_mstp_log(LOG_LEVEL_FATAL, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_e(fmt, a...) print_mstp_log(LOG_LEVEL_ERROR, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_w(fmt, a...) print_mstp_log(LOG_LEVEL_WARNING, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_i(fmt, a...) print_mstp_log(LOG_LEVEL_INFO, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_d(fmt, a...) print_mstp_log(LOG_LEVEL_DEBUG, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_t(fmt, a...) print_mstp_log(LOG_LEVEL_TRACE, "MSTP", __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#else
#define log_f(fmt, a...) print_mstp_log(LOG_LEVEL_FATAL, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_e(fmt, a...) print_mstp_log(LOG_LEVEL_ERROR, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_w(fmt, a...) print_mstp_log(LOG_LEVEL_WARNING, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_i(fmt, a...) print_mstp_log(LOG_LEVEL_INFO, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_d(fmt, a...) print_mstp_log(LOG_LEVEL_DEBUG, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#define log_t(fmt, a...) print_mstp_log(LOG_LEVEL_TRACE, __FILE__, "", __FUNCTION__, __LINE__, fmt, ##a)
#endif

} /* namespace mstp */


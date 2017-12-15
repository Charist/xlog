#include "LogSyncTest.h"
#include "log/MarsLog.h"

using namespace mstp;

LogSyncTest::LogSyncTest(void)
{
}


LogSyncTest::~LogSyncTest(void)
{
}

void LogSyncTest::SetUpTestCase() 
{ 
    init_mstp_log("D:\\log_sync", LOG_WRITE_MODE_SYNC);
    enable_console_log(false);
    std::cout << "LogSyncTest: Mstp Log initial." << std::endl;
}

void LogSyncTest::TearDownTestCase() 
{
    close_mstp_log();
    std::cout << "LogSyncTest: Mstp Log close." << std::endl;
}
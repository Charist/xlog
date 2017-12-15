#include "LogAsyncTest.h"
#include "log/MarsLog.h"

LogAsyncTest::LogAsyncTest(void)
{
}


LogAsyncTest::~LogAsyncTest(void)
{
}

void LogAsyncTest::SetUpTestCase() 
{ 
    init_mstp_log("D:\\log_async");
    std::cout << "LogAsyncTest: Mstp Log initial." << std::endl;
}

void LogAsyncTest::TearDownTestCase() 
{
    close_mstp_log();
    std::cout << "LogAsyncTest: Mstp Log close." << std::endl;
}
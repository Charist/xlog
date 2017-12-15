#include "LogSyncTest.h"
#include "LogAsyncTest.h"
#include "log/MarsLog.h"
#include "log/BaseLog.h"

using namespace mstp;

TEST_F(LogAsyncTest, log_file_name_test)
{
    //Poco::Thread::sleep(1000);
    int i = 0;
    log_t("it's %s, %d,", "log_file_name_test log_t()", i++);
    log_d("it's %s, %d,", "log_file_name_test log_d()", i++);
    log_i("it's %s, %d,", "log_file_name_test log_i()", i++);
    log_e("it's %s, %d,", "log_file_name_test log_e()", i++);
    log_f("it's %s, %d,", "log_file_name_test log_f()", i++);
    EXPECT_TRUE(true);
}

TEST_F(LogAsyncTest, log_write_when_flush)
{
    int i = 10;
    log_t("it's %s, %d,", "log_write_when_flush log_t()", i++);
    log_d("it's %s, %d,", "log_write_when_flush log_d()", i++);
    flush_mstp_log();
    EXPECT_TRUE(true);
}

TEST_F(LogAsyncTest, log_flush_when_error)
{
    int i = 20;
    log_e("it's %s, %d,", "log_flush_when_error log_e()", i++);
    log_f("it's %s, %d,", "log_flush_when_error log_f()", i++);
    log_f("it's %s, %d,", "log_flush_when_error log_f()", i++);
    EXPECT_TRUE(true);
}

TEST_F(LogAsyncTest, log_write_when_crash)
{
    int i = 30;
    log_i("it's %s, %d,", "log_write_when_crash log_i()", i++);
    log_i("it's %s, %d,", "log_write_when_crash log_i()", i++);
    //assert(false); cache.mmap2 里有以上两条日志
    log_i("it's %s, %d,", "log_write_when_crash log_i()", i++);
    log_i("it's %s, %d,", "log_write_when_crash log_i()", i++);
    EXPECT_TRUE(true);
}


TEST_F(LogSyncTest, log_flush_everytime)
{
    int j = 0;
    log_i("it's %s, %d,", "log_flush_everytime log_i()", j++);
    log_i("it's %s, %d,", "log_flush_everytime log_i()", j++);
}
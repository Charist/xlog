#include <Poco/Thread.h>
#include <Poco/DateTime.h>
#include <sys/timeb.h>
#include "LogAsyncTest.h"
#include "LogSyncTest.h"
#include "log/MarsLog.h"


using namespace mstp;

const int THREAD_NUM = 2;

class WriteLogRunnable : public Poco::Runnable
{
public:
    WriteLogRunnable(int index = 0) : m_index(index) {}

    void setIndex(int index) { m_index = index; }
protected:
    virtual void run()
    {
        Poco::DateTime t;
        const int LENGTH = 10000;
        for (size_t i = m_index; i < m_index + LENGTH; i++)
        {
            log_i("it's %s, %d", "WriteLogRunnable", i);
            //mlog_info("mlog_tag", "it's %s, %d", "WriteLogRunnable", i);
        }
        Poco::DateTime t_end;
        printf("-----tid:%d: %d.\n", Poco::Thread::currentTid(), (t_end.timestamp() - t.timestamp())/1000);
    }
    int m_index;
};

/*
TEST_F(LogAsyncTest, muliti_thread_async_write_log)
{
    Poco::Thread threads[THREAD_NUM];
    WriteLogRunnable run1[THREAD_NUM];
    Poco::DateTime t;

    for (int i = 0; i < THREAD_NUM; i++)
    {
        run1[i].setIndex(i * 10000);
        threads[i].start(run1[i]);//传入对象而不是对象指针  
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        threads[i].join();
    }
  
    Poco::DateTime t_end;
    printf("muliti_thread_async_write_log time consume:%d \n", (t_end.timestamp() - t.timestamp()) / 1000);
    log_i("muliti_thread_async_write_log time consume:%d", (t_end.timestamp() - t.timestamp()) / 1000);
    EXPECT_TRUE(true);
}
*/

TEST_F(LogSyncTest, muliti_thread_sync_write_log)
{
    Poco::Thread threads[THREAD_NUM];
    WriteLogRunnable run1[THREAD_NUM];

    Poco::DateTime t;
    for (int i = 0; i < THREAD_NUM; i++)
    {
        run1[i].setIndex(i * 10000);
        threads[i].start(run1[i]);//传入对象而不是对象指针  
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        threads[i].join();
    }
    Poco::DateTime t_end;
    printf("muliti_thread_sync_write_log time consume:%d \n", (t_end.timestamp() - t.timestamp())/1000);
    
    EXPECT_TRUE(true);
}
#pragma once
#include "gtest/gtest.h"

class LogSyncTest : public testing::Test
{
public:
    LogSyncTest(void);
    ~LogSyncTest(void);

protected:
    static void SetUpTestCase() ;
    static void TearDownTestCase();

};


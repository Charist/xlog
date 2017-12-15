#pragma once
#include "gtest/gtest.h"

class LogAsyncTest : public testing::Test
{
public:
    LogAsyncTest(void);
    ~LogAsyncTest(void);

protected:
    static void SetUpTestCase() ;
    static void TearDownTestCase();

};


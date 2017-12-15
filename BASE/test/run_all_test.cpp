#include "gtest/gtest.h"
#include "gmock/gmock.h"

int Foo(int a, int b)
{
    if (a == 0 || b == 0)
    {
        throw "don't do that";
    }
    int c = a % b;
    if (c == 0)
        return b;
    return Foo(b, c);
}

TEST(FooTest, HandleNoneZeroInput)
{
    EXPECT_EQ(2, Foo(4, 10));
    EXPECT_EQ(6, Foo(30, 18));
}

class BaseGtestEnvironment: public testing::Environment
{
public:
    virtual void SetUp()
    {
        std::cout << "BaseGtestEnvironment SetUP" << std::endl;
    }

    virtual void TearDown()
    {
        std::cout << "BaseGtestEnvironment TearDown" << std::endl;
    }
};

int main(int argc, char* argv[])
{
    testing::AddGlobalTestEnvironment(new BaseGtestEnvironment);

    testing::InitGoogleTest(&argc, argv);
	testing::InitGoogleMock(&argc, argv);
    int rc = RUN_ALL_TESTS();

	getchar();
    return rc;
}

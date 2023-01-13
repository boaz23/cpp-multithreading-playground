#include "pch.h"
#include <thread>
#include "../Cpp-Multithreading-Playground/Semaphore_Binary.cpp"

class SemaphoreBinaryBasicTest : public ::testing::Test
{
protected:
    Semaphore_Binary s;

    SemaphoreBinaryBasicTest() : s{}
    {}
};

TEST_F(SemaphoreBinaryBasicTest, BasicUpDown) {
    s.down();
    s.up();
}

TEST(SemaphoreBinaryTests, ExecutionOrder1)
{
    for (int i = 0; i < 30; ++i)
    {
        Semaphore_Binary s{ false };
        int n{ 5 }, no{ n }, nm{ n + 1 };
        std::thread t1
        {
            [&s, &n, &nm]
            {
                nm = n;
                s.up();
            }
        };
        std::thread t2
        {
            [&s, &n]
            {
                s.down();
                n--;
            }
        };

        t1.join();
        t2.join();
        EXPECT_EQ(no - 1, n);
        EXPECT_EQ(no, nm);
    }
}

//TEST(SemaphoreBinaryTests, ExecutionOrder2)
//{
//    Semaphore_Binary s1{true}, s2{false};
//    int n{ 5 }, result{ 0 };
//    std::thread t_adv
//    {
//        [&s1, &s2, &n]
//        {
//            while (n > 0)
//            {
//                s1.down();
//                n--;
//                s2.up();
//            }
//            s1.down();
//        }
//    };
//    std::thread t_adder
//    {
//        [&s1, &s2, &n, &result]
//        {
//            if (n == 0)
//            {
//                s1.up();
//                return;
//            }
//
//            while (n >= 0)
//            {
//                s2.down();
//                result += 2*n + 1;
//                s1.up();
//            }
//        }
//    };
//
//    t_adv.join();
//    t_adder.join();
//    EXPECT_EQ(n*n, result);
//}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
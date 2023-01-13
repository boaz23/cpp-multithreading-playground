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

TEST_F(SemaphoreBinaryBasicTest, BasicUpDown1) {
    s.down();
    s.up();
}

TEST_F(SemaphoreBinaryBasicTest, BasicUpDown2)
{
    s.down();
    s.up();
    s.down();
}

TEST(SemaphoreBinaryTests, ExecutionOrder1)
{
    for (int i = 0; i < 30; ++i)
    {
        Semaphore_Binary s{ false };
        int n{ 5 }, no{ n }, nm{ n + 1 };
        std::thread t1{[&s, &n, &nm]()
        {
            nm = n;
            s.up();
        }};
        std::thread t2{[&s, &n]()
        {
            s.down();
            n--;
        }};

        t1.join();
        t2.join();
        EXPECT_EQ(no - 1, n);
        EXPECT_EQ(no, nm);
    }
}

TEST(SemaphoreBinaryTests, ExecutionOrder2)
{
    auto f = [](int n)
    {
        Semaphore_Binary s1{ true }, s2{ false };
        int result{ 0 }, no{ n };
        std::thread t_adv{ [&s1, &s2, &n]
        {
            while (n >= 0)
            {
                s1.down();
                n--;
                s2.up();
            }
            s1.down();
        } };
        std::thread t_adder{ [&s1, &s2, &n, &result]
        {
            while (true)
            {
                s2.down();
                if (n < 0)
                {
                    s1.up();
                    break;
                }
                result += 2*n + 1;
                s1.up();
            }
        } };

        t_adder.join();
        t_adv.join();
        EXPECT_EQ(no*no, result);
    };

    f(0);
    f(1);
    f(5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int exitCode = RUN_ALL_TESTS();
    //std::cout << "Press any key to exit . . . ";
    //std::cin.ignore();
    return exitCode;
}
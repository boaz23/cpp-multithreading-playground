#include "pch.h"
#include <thread>
#include "../Cpp-Multithreading-Playground/Semaphore.cpp"

class SemaphoreBinaryBasicTest : public ::testing::Test
{
protected:
    Semaphore<1> s;

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
        Semaphore<1> s{ false };
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
        for (int i = 0; i < 30; ++i)
        {
            Semaphore<1> s1{ true }, s2{ false };
            int result{ 0 };
            int k = n;
            std::thread t_adv{ [&s1, &s2, &k]
            {
                while (k >= 0)
                {
                    s1.down();
                    k--;
                    s2.up();
                }
                s1.down();
            } };
            std::thread t_adder{ [&s1, &s2, &k, &result]
            {
                while (true)
                {
                    s2.down();
                    if (k < 0)
                    {
                        s1.up();
                        break;
                    }
                    result += 2*k + 1;
                    s1.up();
                }
            } };

            t_adder.join();
            t_adv.join();
            EXPECT_EQ(n*n, result);
        }
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
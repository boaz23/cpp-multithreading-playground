#include "pch.h"
#include <thread>
#include "QueueBlockingArray.h"
#include "Semaphore.cpp"

namespace ProducerConsumerTests
{
TEST(MultipleNormal, Basic1)
{
    const static constexpr int value = 3;

    for (int i = 0; i < 50; ++i)
    {
        Semaphore<1> s{ 0 };
        QueueBlockingArray<int, 2> q{};
        int n1{}, n2{};

        std::thread p1{ [&q, &s]
        {
            q.insert(value);
            s.down();
            q.insert(0);
        } };
        std::thread c1{ [&q, &s, &n1]
        {
            q.consume(n1);
            s.up();
        } };
        std::thread c2{ [&q, &s, &n2]
        {
            q.consume(n2);
            s.up();
        } };

        p1.join();
        c1.join();
        c2.join();
        if (!((n1 == 0 && n2 == value) || (n1 == value && n2 == 0)))
        {
            FAIL();
        }
    }
}
}

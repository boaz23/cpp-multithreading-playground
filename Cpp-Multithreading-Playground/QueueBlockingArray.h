#pragma once

#include <mutex>
#include "QueueArray.h"
#include "Semaphore.h"

template <typename T, std::size_t N>
class QueueBlockingArray
{
protected:
    QueueArray<T, N> queue;
    std::mutex m;
    Semaphore<N> s_insert;
    Semaphore<N> s_consume;

public:
    QueueBlockingArray() : queue{}, m{}, s_insert{}, s_consume{ 0 }
    {}

    void insert(const T &item)
    {
        s_insert.down();
        {
            std::lock_guard<std::mutex> lock{ m };
            queue.enqueue(item);
        }
        s_consume.up();
    }

    void consume(T& result)
    {
        s_consume.down();
        {
            std::lock_guard<std::mutex> lock{ m };
            queue.dequeue(result);
        }
        s_insert.up();
    }
};

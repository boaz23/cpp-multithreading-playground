#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore_Binary
{
protected:
    std::mutex m;
    std::condition_variable cond;
    bool isUsed;

public:
    Semaphore_Binary() : m{}, cond{}, isUsed{ false }
    {}
    Semaphore_Binary(bool initialValue) : m{}, cond{}, isUsed{ !initialValue }
    {}

    Semaphore_Binary(const Semaphore_Binary &) = delete;
    Semaphore_Binary &operator=(const Semaphore_Binary &) = delete;

    void down();
    void up();
};

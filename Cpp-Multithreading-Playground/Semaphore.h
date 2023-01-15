#pragma once

#include <mutex>
#include <condition_variable>

template <size_t _N>
class Semaphore
{
protected:
    std::mutex m;
    std::condition_variable cond;
    size_t free;
    bool isUsed;

public:
    const static constexpr size_t N = _N;

    Semaphore() : Semaphore{N}
    {
    }
    Semaphore(size_t initialValue) : m{}, cond{}, free{ initialValue }
    {
    }

    Semaphore(const Semaphore&) = delete;
    Semaphore& operator=(const Semaphore&) = delete;

    void down();
    void up();
};

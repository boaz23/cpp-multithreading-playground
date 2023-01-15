#include "Semaphore.h"

template<size_t N>
void Semaphore<N>::down()
{
    std::unique_lock<std::mutex> lock{ m };
    while (free == 0)
    {
        cond.wait(lock);
    }
    free--;
}

template<size_t N>
void Semaphore<N>::up()
{
    std::lock_guard<std::mutex> lock{ m };
    if (free < N)
    {
        free++;
        cond.notify_one();
    }
}

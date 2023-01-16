#include "Barrier_ProducerConsumer.h"

template <size_t N>
void Barrier_ProducerConsumer<N>::consumer_wait()
{
    std::unique_lock<std::mutex> lock{ m };
    ++count;
    s.up();
    do
    {
        cond.wait(lock);
    }
    // TODO: use atomic for the non-strict variant.
    // Q: Does that mean we need 2 counter fields? The strict version does not need atomic and release/consume sematics.
    while (count < N);
}

template <size_t N>
void Barrier_ProducerConsumer<N>::producer_wait()
{
    // TODO: use atomic in the non-strict variant to make sure this memory operation is both atomic and visible to other threads (release/consume semantics)
    while (count < N)
    {
        s.down();
    }
    {
        std::lock_guard<std::mutex> lock{ m };
    }
    cond.notify_all();
}

template <size_t N>
void Barrier_ProducerConsumer<N>::producer_wait_strict()
{
    if (count == N)
    {
        return;
    }

    std::unique_lock<std::mutex> lock{ m, std::defer_lock };
    while (true)
    {
        s.down();
        lock.lock();
        if (++count == N)
        {
            break;
        }
        else
        {
            lock.unlock();
        }
    }
    cond.notify_all();
}

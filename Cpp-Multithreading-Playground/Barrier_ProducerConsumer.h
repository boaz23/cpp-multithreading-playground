#pragma once

#include "Semaphore.h"

/// <summary>
/// A barrier for the producer-consumers pattern (1 producer, N consumers).
/// It ensures that the producer and consumers wait until all consumers finish processing the item.
/// </summary>
/// <typeparam name="_N">The amount of consumers</typeparam>
template <size_t _N>
class Barrier_ProducerConsumer
{
public:
    const static constexpr size_t N = _N;

protected:
    Semaphore<N> s;
    std::mutex m;
    std::condition_variable cond;
    size_t count;

public:
    Barrier_ProducerConsumer() : s{ 0 }, m{}, cond{}, count{ 0 }
    {}

    Barrier_ProducerConsumer(const Barrier_ProducerConsumer &) = delete;
    Barrier_ProducerConsumer &operator=(const Barrier_ProducerConsumer &) = delete;

    void consumer_wait();
    void producer_wait();

    /// <summary>
    /// Like `producer_wait`, but ensures that no consumer will spuriously escape before the notification is issued.
    /// </summary>
    void producer_wait_strict();
};

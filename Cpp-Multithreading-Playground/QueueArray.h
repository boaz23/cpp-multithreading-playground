#pragma once

#include <array>
#include <optional>

template <size_t N>
static size_t indices_cycle_add(size_t n1, size_t n2)
{
    return (n1 + n2) % N;
}

template <size_t N>
static size_t indices_cycle_next(size_t i)
{
    return (i + 1) % N;
}

template <typename T, std::size_t _N>
class QueueArray
{
public:
    const static constexpr size_t N = _N;

protected:
    std::array<T, N> buffer;
    size_t head, size;

public:
    QueueArray() : buffer{}, head{}, size{} {}

    bool isEmpty() const
    {
        return size == 0;
    }

    bool isFull() const
    {
        return size == N;
    }

    void enqueue(const T& item)
    {
        buffer[indices_cycle_add<N>(head, size)] = item;
        ++size;
    }

    void dequeue(T& result)
    {
        result = buffer[head];
        head = indices_cycle_next<N>(head);
        --size;
    }
};

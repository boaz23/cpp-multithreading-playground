#pragma once

#include "Monitor.h"

class Semaphore_Binary
{
protected:
    using monitor_type = Monitor<std::mutex>;

    monitor_type monitor;
    bool isUsed;

public:
    Semaphore_Binary() : monitor{}, isUsed{ false }
    {}

    Semaphore_Binary(const Semaphore_Binary &) = delete;
    Semaphore_Binary &operator=(const Semaphore_Binary &) = delete;

    void down();
    void up();
};

#include "Semaphore_Binary.h"

void Semaphore_Binary::down()
{
    std::lock_guard<monitor_type> lock{ monitor };
    while (isUsed)
    {
        monitor.wait();
    }
    isUsed = true;
}

void Semaphore_Binary::up()
{
    std::lock_guard<monitor_type> lock{ monitor };
    if (isUsed)
    {
        isUsed = false;
        monitor.notify_one();
    }
}

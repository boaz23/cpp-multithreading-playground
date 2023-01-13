#include "Semaphore_Binary.h"

void Semaphore_Binary::down()
{
    std::unique_lock<std::mutex> lock{ m };
    while (isUsed)
    {
        cond.wait(lock);
    }
    isUsed = true;
}

void Semaphore_Binary::up()
{
    std::lock_guard<std::mutex> lock{ m };
    if (isUsed)
    {
        isUsed = false;
        cond.notify_one();
    }
}

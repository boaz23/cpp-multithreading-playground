#pragma once

#include <mutex>
#include <condition_variable>
#include <chrono>

// I'm aware there is a more robust way to implement this class with templates.
// However I don't wish to get into the weaves of templates implementations right now as it is not the point.
template <typename Lock>
class Monitor
{
protected:
    Lock m;
    std::condition_variable_any conditionVariable;

public:
    Monitor() : m{}, conditionVariable{}
    {}

    Monitor(const Monitor &) = delete;
    Monitor &operator=(const Monitor &) = delete;

    using lock_type = Lock;

    void lock()
    {
        m.lock();
    }

    void try_lock()
    {
        m.try_lock();
    }

    void unlock()
    {
        m.unlock();
    }

    void notify_one() noexcept
    {
        conditionVariable.notify_one();
    }

    void notify_all() noexcept
    {
        conditionVariable.notify_all();
    }

    void wait() noexcept
    {
        conditionVariable.wait(m);
    }

    template <class _Predicate>
    void wait(_Predicate pred) noexcept(noexcept(static_cast<bool>(pred())))
    {
        conditionVariable.wait(m, pred);
    }

    template <class _Clock, class _Duration>
    std::cv_status wait_until(const std::chrono::time_point<_Clock, _Duration> &_Abs_time)
    {
        return conditionVariable.wait_until(m, _Abs_time);
    }

    template <class _Clock, class _Duration, class _Predicate>
    bool wait_until(const std::chrono::time_point<_Clock, _Duration> &_Abs_time, _Predicate _Pred)
    {
        return conditionVariable.wait_for(m, _Abs_time, _Pred);
    }

    template <class _Rep, class _Period>
    std::cv_status wait_for(const std::chrono::duration<_Rep, _Period> &_Rel_time)
    {
        return conditionVariable.wait_for(m, _Rel_time);
    }

    template <class _Rep, class _Period, class _Predicate>
    bool wait_for(const std::chrono::duration<_Rep, _Period> &_Rel_time, _Predicate _Pred)
    {
        return conditionVariable.wait_for(m, _Rel_time, _Pred);
    }

    std::cv_status wait_until(const xtime *const _Abs_time)
    {
        return conditionVariable.wait_until(m, _Abs_time);
    }

    template <class _Predicate>
    bool wait_until(const xtime *const _Abs_time, _Predicate _Pred)
    {
        return conditionVariable.wait_until(m, _Abs_time, _Pred);
    }

    typename Lock::native_handle_type native_handle_lock()
    {
        return m.native_handle();
    }

    std::condition_variable::native_handle_type native_handle_condition_variable()
    {
        return conditionVariable.native_handle();
    }
};


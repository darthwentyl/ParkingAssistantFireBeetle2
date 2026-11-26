#ifndef __HELPERS_MUTEX_H__
#define __HELPERS_MUTEX_H__

#include "FreeRTOS.h"

namespace mw { namespace helpers {

class Mutex {
public:
    Mutex();
    ~Mutex() = default;

    Mutex(const Mutex&) = delete;
    Mutex& operator = (const Mutex&) = delete;
    Mutex(Mutex&&) = delete;
    Mutex& operator = (Mutex&&) = delete;

    void lock();
    void unlock();

private:
    SemaphoreHandle_t mutex;
};

class MutexGuard {
public:
    MutexGuard(Mutex& mutex_);
    ~MutexGuard();

    MutexGuard(const MutexGuard&) = delete;
    MutexGuard& operator = (const MutexGuard&) = delete;
    MutexGuard(MutexGuard&&) = delete;
    MutexGuard& operator = (MutexGuard&&) = delete;

private:
    Mutex& mutex;
};

} } // mw::helpers

#endif // __HELEPERS_MUTEX_H__
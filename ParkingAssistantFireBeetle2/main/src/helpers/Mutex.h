#ifndef __HELPERS_MUTEX_H__
#define __HELPERS_MUTEX_H__

#include "FreeRTOS.h"

namespace mw { namespace helpers {

class Mutex {
public:
    Mutex();

    void lock();
    void unlock();

    void lock_isr();
    void unlock_isr();
private:
    portMUX_TYPE mutex;
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

class MutexGuardISR {
public:
    MutexGuardISR(Mutex& mutex_);
    ~MutexGuardISR();

    MutexGuardISR(const MutexGuardISR&) = delete;
    MutexGuardISR& operator = (const MutexGuardISR&) = delete;
    MutexGuardISR(MutexGuardISR&&) = delete;
    MutexGuardISR& operator = (MutexGuardISR&&) = delete;

private:
    Mutex& mutex;
};

} } // mw::helpers

#endif // __HELEPERS_MUTEX_H__
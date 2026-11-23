#include "Mutex.h"

namespace mw {


Mutex::Mutex() :
    mutex(portMUX_INITIALIZER_UNLOCKED)
{}

void Mutex::lock() {
    portENTER_CRITICAL(&mutex);
}

void Mutex::unlock() {
    portEXIT_CRITICAL(&mutex);
}

void Mutex::lock_isr() {
    portENTER_CRITICAL_ISR(&mutex);
}

void Mutex::unlock_isr() {
    portEXIT_CRITICAL_ISR(&mutex);
}

MutexGuard::MutexGuard(Mutex& mutex_) :
    mutex{mutex_}
{
    mutex.lock();
}

MutexGuard::~MutexGuard() {
    mutex.unlock();
}

MutexGuardISR::MutexGuardISR(Mutex& mutex_) :
    mutex{mutex_}
{
    mutex.lock_isr();
}

MutexGuardISR::~MutexGuardISR() {
    mutex.unlock_isr();
}

} // mw
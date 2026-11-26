#include "src/helpers/Mutex.h"

namespace mw { namespace helpers {

Mutex::Mutex()
    : mutex{xSemaphoreCreateMutex()}
{}

void Mutex::lock() {
    if (mutex == nullptr) {
        mutex = xSemaphoreCreateMutex();
    }
    xSemaphoreTake(mutex, portMAX_DELAY) == pdTRUE;
}

void Mutex::unlock() {
    if (mutex != nullptr) {
        xSemaphoreGive(mutex);
    }
}

MutexGuard::MutexGuard(Mutex& mutex_)
    : mutex{mutex_}
{
    mutex.lock();
}

MutexGuard::~MutexGuard() {
    mutex.unlock();
}

} } // mw::helpers
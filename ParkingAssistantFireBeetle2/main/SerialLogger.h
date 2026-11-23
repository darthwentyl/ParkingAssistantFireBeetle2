#pragma once

#include "Mutex.h"

namespace mw {

class SerialLogger {
public:
    static SerialLogger& log();

    ~SerialLogger() = default;
    SerialLogger(const SerialLogger&) = delete;
    SerialLogger& operator = (const SerialLogger&) = delete;
    SerialLogger(SerialLogger&&) = delete;
    SerialLogger& operator = (SerialLogger&&) = delete;

    void printf(const char* format, ...);

private:
    SerialLogger();

    Mutex mutex;
};

} // mw
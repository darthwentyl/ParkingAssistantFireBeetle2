#include <Arduino.h>

#include <stdio.h>
#include <stdarg.h>

#include "src/helpers/SerialLogger.h"

namespace mw { namespace helpers {

SerialLogger::SerialLogger() {
    Serial.begin(115200);
}

SerialLogger& SerialLogger::instance() {
    static SerialLogger instance;
    return instance;
}

void SerialLogger::printf(const char* format, ...) {
    MutexGuard guard{mutex};

    char buffer[1024];

    va_list args;
    va_start(args, format);
    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (n >= 0) {
        Serial.print(buffer);
    }
}

} } // mw::helpers
#ifndef __HELPERS_SERIALLOGGER_H__
#define __HELPERS_SERIALLOGGER_H__

#include "src/helpers/Mutex.h"

#define DEBUG 1

#if DEBUG
#   define DBG(format, ...) \
        do { \
            mw::helpers::SerialLogger::instance().printf( \
                "%s:%d [DBG] " format, \
                __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__); \
        } while(false)
#else
#   define DBG(format, ...)
#endif

#define ERR(format, ...) \
    do { \
        mw::helpers::SerialLogger::instance().printf( \
            "%s:%d [ERR] " format, \
            __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } while(false)

namespace mw { namespace helpers {

class SerialLogger {
public:
    static SerialLogger& instance();

    ~SerialLogger() = default;
    SerialLogger(const SerialLogger&) = delete;
    SerialLogger& operator = (const SerialLogger&) = delete;
    SerialLogger(SerialLogger&&) = delete;
    SerialLogger& operator = (SerialLogger&&) = delete;

    void begin();
    void printf(const char* format, ...);
private:
    SerialLogger();

    Mutex mutex;
};

} } // mw::helpers

#endif // __HELPERS_SERIALLOGGER_H__
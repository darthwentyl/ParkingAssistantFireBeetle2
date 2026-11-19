#pragma once

#include <string>
#include "MsgBase.h"

namespace mw {

class ScreenMsg {
public:
    ScreenMsg(const uint16_t color, const uint8_t line, const std::string& msg);
    ScreenMsg();
    ~ScreenMsg();

    MsgBase serialize();
    void deserialize(const MsgBase& msg);

    uint16_t getColor() const;
    uint16_t getLine() const;
    const char* getMsg() const;

private:
    uint16_t color;
    uint16_t length;
    uint8_t line;
    std::string msg;
};

} // mw
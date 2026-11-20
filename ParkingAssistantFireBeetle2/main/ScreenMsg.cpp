#include <Arduino.h>
#include "ScreenMsg.h"
#include <cstring>

namespace mw {

ScreenMsg::ScreenMsg(const uint16_t color, const uint8_t line, const std::string& msg)
    : color{color}
    , length{msg.length()}
    , line{line}
    , msg{msg}
{
    Serial.printf("%s:%u\n", __FUNCTION__, __LINE__);
}

ScreenMsg::ScreenMsg() : ScreenMsg{0, 0, std::string{}}
{
    Serial.printf("%s:%u\n", __FUNCTION__, __LINE__);
}

ScreenMsg::~ScreenMsg()
{
    Serial.printf("%s:%u\n", __FUNCTION__, __LINE__);
}

MsgBase ScreenMsg::serialize() {
    const std::size_t buffSize = sizeof(color) + sizeof(length) + sizeof(line) + length;
    uint8_t* buff = new uint8_t[buffSize];
    std::size_t offset = 0;
    std::memcpy(buff + offset, &color, sizeof(color));
    offset += sizeof(color);
    std::memcpy(buff + offset, &length, sizeof(length));
    offset += sizeof(length);
    std::memcpy(buff + offset, &line, sizeof(line));
    offset += sizeof(line);
    std::memcpy(buff + offset, msg.data(), length);

    return MsgBase{MsgId::SCREEN_MSG, buff};
}

void ScreenMsg::deserialize(const MsgBase& msg) {
    const uint8_t* buff = static_cast<const uint8_t*>(msg.getPayload());

    size_t offset = 0;
    std::memcpy(&this->color, buff + offset, sizeof(color));
    offset += sizeof(color);
    std::memcpy(&this->length, buff + offset, sizeof(length));
    offset += sizeof(length);
    std::memcpy(&this->line, buff + offset, sizeof(line));
    offset += sizeof(line);
    this->msg = std::string(reinterpret_cast<const char*>(buff + offset), length);

    delete [] buff;
}

uint16_t ScreenMsg::getColor() const {
    return color;
}

uint16_t ScreenMsg::getLine() const {
    return line;
}

const char* ScreenMsg::getMsg() const {
    return msg.c_str();
}

} // mw
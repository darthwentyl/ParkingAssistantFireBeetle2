#pragma once

#include <cstring>
#include <type_traits>

#include "FreeRTOS.h"

namespace mw {

enum class MsgId : uint8_t{
    EMPTY = 0,
    SCREEN_MSG = 1
};

struct MsgHeader {
    MsgId id = MsgId::EMPTY;
};

template<class MSG_T, MsgId ID>
struct MsgBase : MsgHeader {
    MsgBase() { id = ID; }
};

struct ScreenMsg : MsgBase<ScreenMsg, MsgId::SCREEN_MSG> {
    static constexpr std::size_t MAX_SCREEN_LINE_LEN = 12;

    uint16_t color = 0;
    uint8_t line = 0;
    char text[MAX_SCREEN_LINE_LEN] = {0};

    void setText(const char* str) {
        if (str) {
            std::strncpy(text, str, MAX_SCREEN_LINE_LEN - 1);
            text[MAX_SCREEN_LINE_LEN - 1] = '\0';
        }
    }
};

static_assert(std::is_trivially_copyable_v<ScreenMsg>, "Message must be trivially copyable!");

union AnyMessage {
    MsgHeader header;
    ScreenMsg screen;

    AnyMessage() : header{} {}
};

} // mw
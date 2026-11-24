#ifndef __MESSAGES_SCREENTEXTMSG_H__
#define __MESSAGES_SCREENTEXTMSG_H__

#include <cstring>
#include <type_traits>

#include "src/messages/Message.h"

namespace mw { namespace messages {

struct ScreenTextMsg : MsgBase<ScreenTextMsg, MsgId::SCREEN_TEXT_MSG> {
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

static_assert(std::is_trivially_copyable_v<ScreenTextMsg>, "Message must be trivially copyable!");

} } // mw::messages

#endif // __MESSAGES_SCREENTEXTMSG_H__
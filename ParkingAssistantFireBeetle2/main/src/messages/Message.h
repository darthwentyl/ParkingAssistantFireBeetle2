#ifndef __MESSAGES_MESSAGE_H__
#define __MESSAGES_MESSAGE_H__

#include "FreeRTOS.h"

namespace mw { namespace messages {

enum class MsgId : uint8_t{
    EMPTY = 0,
    SCREEN_TEXT_MSG = 1
};

struct MsgHeader {
    MsgId id = MsgId::EMPTY;
};

template<class MSG_T, MsgId ID>
struct MsgBase : MsgHeader {
    MsgBase() { id = ID; }
};

} } // mw::messages

#endif // __MESSAGES_MESSAGE_H__
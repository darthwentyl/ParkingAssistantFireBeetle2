#ifndef __MESSAGES_ANYMESSAGE_H__
#define __MESSAGES_ANYMESSAGE_H__

#include "src/messages/ScreenTextMsg.h"

namespace mw { namespace messages {

union AnyMessage {
    MsgHeader header;
    ScreenTextMsg screenText;

    AnyMessage() : header{} {}
};

} } // mw::messages

#endif // __MESSAGES_ANYMESSAGE_H__
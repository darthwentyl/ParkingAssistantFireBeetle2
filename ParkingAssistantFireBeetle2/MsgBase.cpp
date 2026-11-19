#include <Arduino.h>

#include "MsgBase.h"

namespace mw {

MsgBase::MsgBase(const MsgId id, void* payload)
    : id{id}
    , payload{payload}
{
    Serial.printf("%s:%u, payload: %p\n", __FUNCTION__, __LINE__, payload);
}

MsgBase::MsgBase() : MsgBase{MsgId::EMPTY, nullptr}
{
    Serial.printf("%s:%u\n", __FUNCTION__, __LINE__);
}

MsgBase::~MsgBase() {
    Serial.printf("%s:%u, payload: %p\n", __FUNCTION__, __LINE__, payload);
}

MsgId MsgBase::getMsgId() const {
    return id;
}

void* MsgBase::getPayload() const {
    return payload;
}

} // mw
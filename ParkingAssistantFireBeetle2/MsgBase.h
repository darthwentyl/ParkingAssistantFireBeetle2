#pragma once

#include <memory>

namespace mw {

enum class MsgId {
    EMPTY = 0,
    SCREEN_MSG = 1
};

class MsgBase {
public:
    MsgBase(const MsgId id, void* payload);
    MsgBase();
    ~MsgBase();

    MsgId getMsgId() const;
    void* getPayload() const;

private:
    MsgId id;
    void* payload;
};

} // mw
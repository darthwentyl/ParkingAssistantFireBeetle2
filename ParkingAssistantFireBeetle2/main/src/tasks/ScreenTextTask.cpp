#include <Arduino.h>

#include "src/tasks/ScreenTextTask.h"
#include "src/components/ScreenText.h"
#include "src/messages/AnyMessage.h"
#include "src/helpers/SerialLogger.h"

namespace mw { namespace tasks {

using namespace mw::messages;
using namespace mw::helpers;
using namespace mw::components;

void ScreenTextTask::loop() {
    DBG();

    ScreenText screen{};
    while(true) {
        AnyMessage received;
        if (xQueueReceive(address(), &received, portMAX_DELAY) == pdPASS) {
            switch (received.header.id) {
                case MsgId::SCREEN_TEXT_MSG:
                    screen.display(
                        received.screenText.text,
                        received.screenText.line,
                        received.screenText.color
                    );
                    break;
                default:
                    ERR("wrong id: %u", __FUNCTION__, static_cast<uint32_t>(received.header.id));
            }
        }
    }
}

} } // mw::tasks
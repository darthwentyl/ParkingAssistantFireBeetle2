#include <Arduino.h>

#include "src/tasks/ScreenTextTask.h"

#include "src/messages/AnyMessage.h"

#include "src/helpers/SerialLogger.h"

namespace mw { namespace tasks {

using namespace mw::messages;
using namespace mw::helpers;

void ScreenTextTask::loop() {
    DBG("");
    QueueHandle_t myAddress = getTasksManager().getAddress(taskName());
    if (myAddress == nullptr) {
        return;
    }
    DBG("Address created");

    while(true) {
        AnyMessage received;
        if (xQueueReceive(myAddress, &received, portMAX_DELAY) == pdPASS) {
            switch (received.header.id) {
                case MsgId::SCREEN_TEXT_MSG:
                    DBG("color: %u", received.screenText.color);
                    DBG("line: %u", received.screenText.line);
                    DBG("text: %s", received.screenText.text);
                    break;
                default:
                    ERR("wrong id: %u", __FUNCTION__, static_cast<uint32_t>(received.header.id));
            }
        }
    }
}

} } // mw::tasks
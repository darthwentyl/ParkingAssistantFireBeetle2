#include <Arduino.h>

#include "SerialLogger.h"
#include "ScreenTask.h"
#include "Messages.h"

namespace mw {

void ScreenTask::loop() {
    SerialLogger::log().printf("ScreenTask::%s:%d\n", __FUNCTION__, __LINE__);
    QueueHandle_t myAddress = getQueueManager().getAddress(taskName());
    if (myAddress == nullptr) {
        return;
    }
    SerialLogger::log().printf("%s:%d\n", __FUNCTION__, __LINE__);

    while(true) {
        AnyMessage received;
        SerialLogger::log().printf("%s:%d\n", __FUNCTION__, __LINE__);
        if (xQueueReceive(myAddress, &received, portMAX_DELAY) == pdPASS) {
            switch (received.header.id) {
                case MsgId::SCREEN_MSG:
                    SerialLogger::log().printf("color: %u\n", received.screen.color);
                    SerialLogger::log().printf("line: %u\n", received.screen.line);
                    SerialLogger::log().printf("text: %s\n", received.screen.text);
                    break;
                default:
                    SerialLogger::log().printf("ScreenTask::%s wrong id: %u\n", __FUNCTION__, static_cast<uint8_t>(received.header.id));
            }
        }
    }
}

} // mw
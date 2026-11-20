#include <Arduino.h>

#include "ScreenTask.h"
#include "ScreenMsg.h"

namespace mw {

void ScreenTask::loop() {
    Serial.printf("%s:%u begin\n", __FUNCTION__, __LINE__);
    QueueHandle_t queue = xQueueCreate(1, sizeof(MsgBase));
    registerQueue(queue);
    Serial.printf("%s:%u created\n", __FUNCTION__, __LINE__);

    while(true) {
        // Serial.printf("%s:%u begin\n", __FUNCTION__, __LINE__);
        MsgBase msg;
        if (xQueueReceive(queue, &msg, portMAX_DELAY) == pdPASS) {
            ScreenMsg screenData;
            screenData.deserialize(msg);
            Serial.printf("%s:%u color: %u\n", __FUNCTION__, __LINE__, screenData.getColor());
            Serial.printf("%s:%u line: %u\n", __FUNCTION__, __LINE__, screenData.getLine());
            Serial.printf("%s:%u msg: %s\n", __FUNCTION__, __LINE__, screenData.getMsg());
        }
        // Serial.printf("%s:%u end\n", __FUNCTION__, __LINE__);
    }
    Serial.printf("%s:%u END\n", __FUNCTION__, __LINE__);
}

} // mw
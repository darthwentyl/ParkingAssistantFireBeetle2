#include "TaskCreator.h"
#include "TaskQueueManager.h"

#include "ScreenTask.h"
#include "ScreenMsg.h"

using namespace mw;

static TaskQueueManager taskQueueManager;
static TaskCreator<ScreenTask> screenTask{"ScreenTask", taskQueueManager};

volatile std::size_t counter = 0;

void setup() {
    Serial.begin(115200);
    Serial.printf("%s begin\n", __FUNCTION__);

    screenTask.create(2048, 1, nullptr);

    Serial.printf("%s end\n", __FUNCTION__);
}

void loop() {
    Serial.printf("%s main begin\n", __FUNCTION__);
    ScreenMsg msg{counter, 10, std::string{"short"}};
    MsgBase base = msg.serialize();
    Serial.printf("%s main: addr: %p\n", __FUNCTION__, taskQueueManager.getAddress("ScreenTask"));
    if (taskQueueManager.getAddress("ScreenTask") != nullptr) {
        xQueueSend(
            taskQueueManager.getAddress("ScreenTask"),
            &base,
            pdMS_TO_TICKS(100));
    }
    delay(3600);
    ++counter;
    Serial.printf("%s main end\n", __FUNCTION__);
}
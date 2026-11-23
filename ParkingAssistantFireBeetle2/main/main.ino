#include "TaskCreator.h"
#include "TaskQueueManager.h"

#include "Messages.h"
#include "ScreenTask.h"
#include "SerialLogger.h"

using namespace mw;

static TaskQueueManager taskQueueManager;
static TaskCreator<ScreenTask> screenTask{"ScreenTask", taskQueueManager};

volatile std::size_t counter = 0;

void setup() {
    screenTask.create(4096, 1, nullptr);
}

void loop() {
    delay(1000);
    SerialLogger::log().printf("%s:%u\n", __FUNCTION__, __LINE__);
    AnyMessage msg;
    msg.screen = ScreenMsg{};
    msg.screen.color = counter + 1;
    msg.screen.line = counter + 2;
    msg.screen.setText("ABCD");

    if (taskQueueManager.getAddress("ScreenTask") != nullptr) {

        xQueueSend(
            taskQueueManager.getAddress("ScreenTask"),
            &msg,
            pdMS_TO_TICKS(100));
    }

    ++counter;
}
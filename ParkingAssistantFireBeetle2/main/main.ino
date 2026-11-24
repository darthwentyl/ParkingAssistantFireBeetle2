#include "DFRobot_GDL.h"

#include "src/tasks/TaskCreator.h"
#include "src/tasks/TasksManager.h"
#include "src/tasks/ScreenTextTask.h"
#include "src/tasks/TaskNameDef.h"
#include "src/messages/AnyMessage.h"
#include "src/helpers/SerialLogger.h"

using namespace mw;
using namespace mw::tasks;
using namespace mw::messages;
using namespace mw::helpers;

static TasksManager tasksManager;
static TaskCreator<ScreenTextTask> screenTextTask{SCREEN_TEXT_TASK_NAME, tasksManager};

volatile std::size_t counter = 0;

void setup() {
    screenTextTask.create(4096, 1, nullptr);
}

void loop() {
    static uint16_t colors [] = {
        COLOR_RGB565_YELLOW,
        COLOR_RGB565_GREEN,
        COLOR_RGB565_RED
    };

    delay(1000);
    DBG("counter: %d", counter);
    AnyMessage msg;
    msg.screenText = ScreenTextMsg{};
    msg.screenText.color = colors[counter % 3];
    msg.screenText.line = counter % 4;

    char screenBuff[ScreenTextMsg::MAX_SCREEN_LINE_LEN];
    snprintf(screenBuff, sizeof(screenBuff), "C: %zu", counter);
    msg.screenText.setText(screenBuff);

    if (tasksManager.getAddress(SCREEN_TEXT_TASK_NAME) != nullptr) {
        xQueueSend(
            tasksManager.getAddress(SCREEN_TEXT_TASK_NAME),
            &msg,
            pdMS_TO_TICKS(100));
    }

    ++counter;
}
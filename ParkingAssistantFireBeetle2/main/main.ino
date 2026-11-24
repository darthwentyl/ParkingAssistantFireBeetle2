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
    delay(1000);
    DBG("counter: %d", counter);
    AnyMessage msg;
    msg.screenText = ScreenTextMsg{};
    msg.screenText.color = counter + 1;
    msg.screenText.line = counter + 2;
    msg.screenText.setText("ABCD");

    if (tasksManager.getAddress(SCREEN_TEXT_TASK_NAME) != nullptr) {
        xQueueSend(
            tasksManager.getAddress(SCREEN_TEXT_TASK_NAME),
            &msg,
            pdMS_TO_TICKS(100));
    }

    ++counter;
}
#include "src/tasks/TaskCreator.h"
#include "src/tasks/TasksManager.h"
#include "src/tasks/ScreenTextTask.h"
#include "src/tasks/CameraTask.h"
#include "src/tasks/TaskNameDef.h"
#include "src/messages/AnyMessage.h"
#include "src/helpers/SerialLogger.h"

#include "DFRobot_GDL.h"

using namespace mw::tasks;
using namespace mw::messages;
using namespace mw::helpers;

static TasksManager tasksManager;
static TaskCreator<ScreenTextTask> screenTextTask{SCREEN_TEXT_TASK_NAME, tasksManager};
static TaskCreator<CameraTask> cameraTask{CAMERA_TASK_NAME, tasksManager};

volatile std::size_t counter = 0;

void setup() {
    SerialLogger::instance().begin();
    screenTextTask.create(4096, 1, nullptr);
    cameraTask.create(4096, 1, nullptr);
}

void loop() {
    delay(1000);
    AnyMessage msg;
    msg.screenText = ScreenTextMsg{};
    msg.screenText.color = COLOR_RGB565_YELLOW;
    msg.screenText.line = 1;

    char text[ScreenTextMsg::MAX_SCREEN_LINE_LEN];
    snprintf(text, sizeof(text), "C: %zu", ++counter);
    msg.screenText.setText(text);

    const QueueHandle_t screenAddr = tasksManager.getAddress(SCREEN_TEXT_TASK_NAME);
    if (screenAddr != nullptr) {
        xQueueSend(
            screenAddr,
            &msg,
            pdMS_TO_TICKS(100));
    }
}
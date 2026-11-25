#include "src/tasks/CameraTask.h"
#include "src/tasks/TaskNameDef.h"
#include "src/components/Camera.h"
#include "src/messages/AnyMessage.h"
#include "src/helpers/SerialLogger.h"

#include "DFRobot_GDL.h"

namespace mw { namespace tasks {

using namespace mw::components;
using namespace mw::messages;
using namespace mw::helpers;

void CameraTask::loop() {
    DBG();

    Camera camera;
    if (!camera.init()) {
        ERR("Cannot initialize camera");
        return;
    }

    while(true) {
        const camera_fb_t* frame = camera.getFrame();
        sendInfoToScreen(frame);
        camera.releaseFrame();
    }
}

void CameraTask::sendInfoToScreen(const camera_fb_t* frame) {
    AnyMessage msg;
    msg.screenText = ScreenTextMsg{};
    msg.screenText.color = COLOR_RGB565_YELLOW;
    msg.screenText.line = 0;

    char text[ScreenTextMsg::MAX_SCREEN_LINE_LEN];
    snprintf(text, sizeof(text), "FL: %zu", frame->len);
    msg.screenText.setText(text);

    const QueueHandle_t screenAddr = getTasksManager().getAddress(SCREEN_TEXT_TASK_NAME);
    if (screenAddr != nullptr) {
        xQueueSend(
            screenAddr,
            &msg,
            pdMS_TO_TICKS(100));
    }
}

} } // mw::tasks
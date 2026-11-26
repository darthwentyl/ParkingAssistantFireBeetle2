#include "src/tasks/CameraTask.h"
#include "src/tasks/TaskNameDef.h"
#include "src/components/Camera.h"
#include "src/components/WifiAP.h"
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
    DBG("Camera wifi AP starting");

    WifiAP wifiAP{8090};
    if (!wifiAP.open()) {
        ERR("Cannot start listening");
        return;
    }
    DBG("Camera listening on port 8090");

    while(true) {
        sendStatusToScreen("C: Waiting", COLOR_RGB565_SKYBLUE);
        if (!wifiAP.accept()) {
            continue;
        }
        sendStatusToScreen("C: Accepted", COLOR_RGB565_GREEN);
        while(true) {
            const camera_fb_t* frame = camera.getFrame();
            uint32_t len = static_cast<uint32_t>(frame->len);
            uint8_t header[4] = {
                static_cast<uint8_t>(len >> 24),
                static_cast<uint8_t>(len >> 16),
                static_cast<uint8_t>(len >> 8),
                static_cast<uint8_t>(len)
            };
            if (!(wifiAP.send(header, sizeof(header)) && wifiAP.send(frame->buf, frame->len))) {
                camera.releaseFrame();
                break;
            }
            camera.releaseFrame();
        }
    }
}

void CameraTask::sendStatusToScreen(const char* text, const uint16_t color) {
    AnyMessage msg;
    msg.screenText = ScreenTextMsg{};
    msg.screenText.color = color;
    msg.screenText.line = 0;
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
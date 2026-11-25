#include "src/tasks/CameraTask.h"
#include "src/messages/AnyMessage.h"
#include "src/helpers/SerialLogger.h"

namespace mw { namespace tasks {

using namespace mw::messages;
using namespace mw::helpers;

void CameraTask::loop() {
    DBG();

    while(true) {
        AnyMessage received;
        if (xQueueReceive(address(), &received, portMAX_DELAY) == pdPASS) {
            switch (received.header.id) {
            default:
                ERR("wrong id: %u", static_cast<uint32_t>(received.header.id));
            }
        }
    }
}

} } // mw::tasks
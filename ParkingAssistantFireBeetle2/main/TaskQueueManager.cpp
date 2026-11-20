#include "TaskQueueManager.h"

namespace mw {

void TaskQueueManager::registerQueue(const std::string& name, QueueHandle_t address) {
    tasksQueue[name] = address;
}

QueueHandle_t TaskQueueManager::getAddress(const std::string& name) const {
    auto handler = tasksQueue.find(name);
    if (handler != tasksQueue.cend()) {
        return handler->second;
    }
    return nullptr;
}


} // mw
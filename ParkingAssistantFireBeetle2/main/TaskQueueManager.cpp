#include "TaskQueueManager.h"

#include "SerialLogger.h"

namespace mw {

void TaskQueueManager::registerQueue(const std::string& name, QueueHandle_t address) {
    MutexGuard guard{mutex};
    SerialLogger::log().printf("%s:%d name: %s\n", __FUNCTION__, __LINE__, name.c_str());
    tasksQueue[name] = address;
}

QueueHandle_t TaskQueueManager::getAddress(const std::string& name) const {
    MutexGuard guard{mutex};
    SerialLogger::log().printf("%s:%d name: %s\n", __FUNCTION__, __LINE__, name.c_str());
    auto handler = tasksQueue.find(name);
    if (handler != tasksQueue.cend()) {
        return handler->second;
    }
    return nullptr;
}


} // mw
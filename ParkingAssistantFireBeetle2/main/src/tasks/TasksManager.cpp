#include "src/tasks/TasksManager.h"
#include "src/helpers/SerialLogger.h"

namespace mw { namespace tasks {

using namespace mw::helpers;

void TasksManager::registerAddress(const std::string& name, QueueHandle_t address) {
    MutexGuard guard{mutex};
    if (addresses.find(name) == addresses.cend()) {
        addresses[name] = address;
        DBG("task %s registered", name.c_str());
    } else {
        ERR("task %s has registered", name.c_str());
    }

}

QueueHandle_t TasksManager::getAddress(const std::string& name) const {
    MutexGuard guard{mutex};
    auto address = addresses.find(name);
    if (address != addresses.cend()) {
        return address->second;
    } else {
        ERR("task %s not found", name.c_str());
        return nullptr;
    }

}

} } // mw::tasks
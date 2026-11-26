#include "src/tasks/TasksManager.h"
#include "src/tasks/TaskNameDef.h"
#include "src/helpers/SerialLogger.h"

#include <cstring>

namespace mw { namespace tasks {

using namespace mw::helpers;

TasksManager::TasksManager()
    : mutex{}
    , tasks {
        { SCREEN_TEXT_TASK_NAME, nullptr },
        { CAMERA_TASK_NAME, nullptr }
    }
{}


void TasksManager::registerAddress(const char* name, QueueHandle_t address) {
    MutexGuard guard{mutex};
    constexpr size_t size = 2;
    for (size_t i = 0; i < size; i++) {
        if (strcmp(tasks[i].name, name) == 0) {
            if (tasks[i].address == nullptr) {
                tasks[i].address = address;
            }
            break;
        }
    }
}

QueueHandle_t TasksManager::getAddress(const char* name) const {
    MutexGuard guard{mutex};
    constexpr size_t size = 2;
    for (size_t i = 0; i < size; i++) {
        if (strcmp(tasks[i].name, name) == 0) {
            return tasks[i].address;
        }
    }
    return nullptr;
}

} } // mw::tasks
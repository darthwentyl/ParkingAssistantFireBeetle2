#ifndef __TASKS_TASKSMANAGER_H__
#define __TASKS_TASKSMANAGER_H__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <unordered_map>
#include <string>

#include "src/helpers/Mutex.h"

namespace mw { namespace tasks {

class TasksManager {
public:
    TasksManager() = default;
    ~TasksManager() = default;

    TasksManager(const TasksManager&) = delete;
    TasksManager& operator = (const TasksManager&) = delete;
    TasksManager(TasksManager&&) = delete;
    TasksManager& operator = (TasksManager&&) = delete;

    void registerAddress(const std::string& name, QueueHandle_t address);
    QueueHandle_t getAddress(const std::string& name) const;

private:
    mutable helpers::Mutex mutex;
    std::unordered_map<std::string, QueueHandle_t> addresses;
};

} } // mw::tasks

#endif // __TASKS_TASKSMANAGER_H__
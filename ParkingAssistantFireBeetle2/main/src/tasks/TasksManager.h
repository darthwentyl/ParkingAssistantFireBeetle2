#ifndef __TASKS_TASKSMANAGER_H__
#define __TASKS_TASKSMANAGER_H__

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "src/helpers/Mutex.h"

namespace mw { namespace tasks {

class TasksManager {
public:
    TasksManager();
    ~TasksManager() = default;

    TasksManager(const TasksManager&) = delete;
    TasksManager& operator = (const TasksManager&) = delete;
    TasksManager(TasksManager&&) = delete;
    TasksManager& operator = (TasksManager&&) = delete;

    void registerAddress(const char* name, QueueHandle_t address);
    QueueHandle_t getAddress(const char* name) const;

private:
    struct TaskItem {
        const char* name;
        QueueHandle_t address = nullptr;
    };

    mutable helpers::Mutex mutex;
    TaskItem tasks[2];

};

} } // mw::tasks

#endif // __TASKS_TASKSMANAGER_H__
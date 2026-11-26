#ifndef __TASKS_TASKCREATOR_H__
#define __TASKS_TASKCREATOR_H__

#include "src/tasks/Task.h"
#include "src/helpers/SerialLogger.h"

namespace mw { namespace tasks {

template<class TASK_T>
class TaskCreator {
public:
    TaskCreator(const char* const name, TasksManager& tasksManager);
    ~TaskCreator() = default;

    TaskCreator(const TaskCreator&) = delete;
    TaskCreator& operator = (const TaskCreator&) = delete;
    TaskCreator(TaskCreator&&) = delete;
    TaskCreator& operator = (TaskCreator&&) = delete;

    bool create(
        const configSTACK_DEPTH_TYPE uxStackDepth,
        const UBaseType_t uxPriority,
        TaskHandle_t* pxCreatedTask);

    static void run(void* arg);

private:
    Task<TASK_T> task;
};

template<class TASK_T>
TaskCreator<TASK_T>::TaskCreator(const char* const name, TasksManager& tasksManager)
    : task{name, tasksManager}
{}

template<class TASK_T>
bool TaskCreator<TASK_T>::create(
    const configSTACK_DEPTH_TYPE uxStackDepth,
    const UBaseType_t uxPriority,
    TaskHandle_t* pxCreatedTask) {

    return xTaskCreate(
        TaskCreator<TASK_T>::run,
        task.taskName(),
        uxStackDepth,
        this,
        uxPriority,
        pxCreatedTask) == pdPASS;
}

template<class TASK_T>
void TaskCreator<TASK_T>::run(void* arg) {
    auto* task = static_cast<Task<TASK_T>*>(arg);
    task->loop();
    vTaskDelete(nullptr);
}

} } // mw::tasks

#endif // __TASKS_TASKCREATOR_H__
#ifndef __TASKS_TASK_H__
#define __TASKS_TASK_H__

#include "src/tasks/TasksManager.h"
#include "src/messages/AnyMessage.h"

namespace mw { namespace tasks {

template<class TASK_T>
class Task {
public:
    Task(const char* const name, TasksManager& tasksManager);
    ~Task() = default;

    Task(const Task&) = delete;
    Task& operator = (const Task&) = delete;
    Task(Task&&) = delete;
    Task& operator = (Task&&) = delete;

    void loop();
    const char* const taskName() const;

protected:
    TasksManager& getTasksManager() const;

private:
    TASK_T& self();

    TasksManager& tasksManager;
    const char* const name;
};

template<class TASK_T>
Task<TASK_T>::Task(const char* const name, TasksManager& tasksManager)
    : name{name}
    , tasksManager{tasksManager}
{}

template<class TASK_T>
void Task<TASK_T>::loop() {
    tasksManager.registerAddress(name, xQueueCreate(5, sizeof(messages::AnyMessage)));
    self().loop();
    vTaskDelete(nullptr);
}

template<class TASK_T>
const char* const Task<TASK_T>::taskName() const {
    return name;
}

template<class TASK_T>
TasksManager& Task<TASK_T>::getTasksManager() const {
    return tasksManager;
}

template<class TASK_T>
TASK_T& Task<TASK_T>::self() {
    return static_cast<TASK_T&>(*this);
}

} } // mw::tasks

#endif // __TASKS_TASK_H__
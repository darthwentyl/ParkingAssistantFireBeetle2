#pragma once

#include "TaskQueueManager.h"
#include "Messages.h"

namespace mw {

template<class SELF_T>
class Task {
public:
    Task(const char* const name, TaskQueueManager& taskQueueManager)
        : name{name}
        , taskQueueManager{taskQueueManager}
    {}
    ~Task() = default;

    Task(const Task&) = delete;
    Task& operator = (const Task&) = delete;
    Task(Task&&) = delete;
    Task& operator = (Task&&) = delete;

    void loop() {
        taskQueueManager.registerQueue(name, xQueueCreate(10, sizeof(AnyMessage)));
        self().loop();
        vTaskDelete(nullptr);
    }

    const char* const taskName() {
        return name;
    }

protected:
    TaskQueueManager& getQueueManager() {
        return taskQueueManager;
    }

private:
    SELF_T& self() {
        return static_cast<SELF_T&>(*this);
    }

    TaskQueueManager& taskQueueManager;
    const char* const name;
};

} // mw
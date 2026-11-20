#pragma once

#include "TaskQueueManager.h"

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

    const char* const taskName() {
        return name;
    }

    void loop() {
        self().loop();
    }

protected:
    void registerQueue(QueueHandle_t address) {
        taskQueueManager.registerQueue(name, address);
    }

private:
    SELF_T& self() {
        return static_cast<SELF_T&>(*this);
    }

    TaskQueueManager& taskQueueManager;
    const char* const name;
};

} // mw
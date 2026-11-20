#pragma once

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <unordered_map>
#include <string>

namespace mw {

class TaskQueueManager {
public:
    TaskQueueManager() = default;
    ~TaskQueueManager() = default;

    TaskQueueManager(const TaskQueueManager&) = delete;
    TaskQueueManager& operator = (const TaskQueueManager&) = delete;
    TaskQueueManager(TaskQueueManager&&) = delete;
    TaskQueueManager& operator = (TaskQueueManager&&) = delete;

    void registerQueue(const std::string& name, QueueHandle_t address);
    QueueHandle_t getAddress(const std::string& name) const;

private:
    std::unordered_map<std::string, QueueHandle_t> tasksQueue;
};

} // mw
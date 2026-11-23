#pragma once

#include "Task.h"

namespace mw {

class ScreenTask : public Task<ScreenTask> {
public:
    ~ScreenTask() = default;

    ScreenTask(const ScreenTask&) = delete;
    ScreenTask& operator = (const ScreenTask&) = delete;
    ScreenTask(ScreenTask&&) = delete;
    ScreenTask& operator = (ScreenTask&&) = delete;

    void loop();
private:

};

} // mw
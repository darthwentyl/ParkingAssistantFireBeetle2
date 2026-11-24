#ifndef __TASKS_SCREENTEXTTASK_H__
#define __TASKS_SCREENTEXTTASK_H__

#include "src/tasks/Task.h"

namespace mw { namespace tasks {

class ScreenTextTask : public Task<ScreenTextTask> {
public:
    ~ScreenTextTask() = default;

    ScreenTextTask(const ScreenTextTask&) = delete;
    ScreenTextTask& operator = (const ScreenTextTask&) = delete;
    ScreenTextTask(ScreenTextTask&&) = delete;
    ScreenTextTask& operator = (ScreenTextTask&&) = delete;

    void loop();
};

} } // mw::tasks

#endif // __TASKS_SCREENTEXTTASK_H__
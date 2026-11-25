#ifndef __TASKS_CAMERATASK_H__
#define __TASKS_CAMERATASK_H__

#include "src/tasks/Task.h"

namespace mw { namespace tasks {

class CameraTask : public Task<CameraTask> {
public:
    ~CameraTask() = default;

    CameraTask(const CameraTask&) = delete;
    CameraTask& operator = (const CameraTask&) = delete;
    CameraTask(CameraTask&&) = delete;
    CameraTask& operator = (CameraTask&&) = delete;

    void loop();
};

} } // mw::tasks

#endif // __TASKS_CAMERATASK_H__
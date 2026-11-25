#ifndef __COMPONENTS_CAMERA_H__
#define __COMPONENTS_CAMERA_H__

#include <DFRobot_AXP313A.h>
#include <esp_camera.h>

namespace mw { namespace components {

class Camera {
public:
    Camera();
    ~Camera();

    Camera(const Camera&) = delete;
    Camera& operator = (const Camera&) = delete;
    Camera(Camera&&) = delete;
    Camera& operator = (Camera&&) = delete;

    bool init();
    const camera_fb_t* getFrame();
    void releaseFrame();

private:
    camera_fb_t* frame;
    DFRobot_AXP313A axp;
};

} } // mw::components

#endif // __COMPONENTS_CAMERA_H__
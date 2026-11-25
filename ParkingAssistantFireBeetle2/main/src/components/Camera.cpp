#include "src/components/Camera.h"
#include "src/helpers/SerialLogger.h"

#include "src/externals/camera_index.h"
#include "src/externals/board_config.h"
#include "src/externals/camera_pins.h"

namespace mw { namespace components {

Camera::Camera()
    : frame{nullptr}
{}

Camera::~Camera() {
    releaseFrame();
}

bool Camera::init() {
    while (axp.begin() != 0) {
        ERR("axp init failure. Wait 100ms");
        delay(100);
    }
    axp.enableCameraPower(axp.eOV2640);

    camera_config_t config{};
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.frame_size = FRAMESIZE_SVGA;
    config.pixel_format = PIXFORMAT_JPEG;  // for streaming
    //config.pixel_format = PIXFORMAT_RGB565; // for face detection/recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
    //                      for larger pre-allocated frame buffer.
    if (config.pixel_format == PIXFORMAT_JPEG) {
        if (psramFound()) {
            config.jpeg_quality = 10;
            config.fb_count = 2;
            config.grab_mode = CAMERA_GRAB_LATEST;
        } else {
            config.fb_location = CAMERA_FB_IN_DRAM;
        }
    } else {
        // Best option for face detection/recognition
        config.frame_size = FRAMESIZE_240X240;
        config.fb_count = 2;
    }

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ERR("Camera init failed with error 0x%x", err);
        return false;
    }

    // set sensor
    sensor_t *s = esp_camera_sensor_get();
    if (s == nullptr) {
        ERR("Cannot get camera sensor");
        return false;
    }
    s->set_brightness(s, 1);   // try 0, then 1 if the image is too dark
    s->set_contrast(s, 1);     // try 0 or 1
    s->set_saturation(s, 0);   // neutral color

    return true;
}

const camera_fb_t* Camera::getFrame() {
    if (frame != nullptr) {
        DBG("Last frame doesn't released, return last frame");
        return frame;

    }
    frame = esp_camera_fb_get();
    if (frame == nullptr) {
        ERR("Cannt get frame buff");
    }

    return frame;
}

void Camera::releaseFrame() {
    if (frame == nullptr) {
        DBG("Frame has already released");
        return;
    }
    esp_camera_fb_return(frame);
    frame = nullptr;
}

} } // mw::components
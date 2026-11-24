#ifndef __COMPONENTS_SCREENTEXT_H__
#define __COMPONENTS_SCREENTEXT_H__

#include "DFRobot_GDL.h"
#include "src/helpers/Mutex.h"

namespace mw { namespace components {

class ScreenText {
public:
    ScreenText(const ScreenText&) = delete;
    ScreenText& operator = (const ScreenText&) = delete;
    ScreenText(ScreenText&&) = delete;
    ScreenText& operator = (ScreenText&&) = delete;
    ~ScreenText() = default;

    static ScreenText& get();

    void display(const char* msg, const uint8_t line, const uint16_t color);

private:
    ScreenText();

    DFRobot_ST7735_80x160_HW_SPI screen;
    helpers::Mutex mutex;
};

} } // mw::components

#endif // __COMPONENTS_SCREENTEXT_H__
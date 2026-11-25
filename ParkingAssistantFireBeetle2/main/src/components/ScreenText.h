#ifndef __COMPONENTS_SCREENTEXT_H__
#define __COMPONENTS_SCREENTEXT_H__

#include "DFRobot_GDL.h"

namespace mw { namespace components {

class ScreenText {
public:
    ScreenText();
    ~ScreenText() = default;

    ScreenText(const ScreenText&) = delete;
    ScreenText& operator = (const ScreenText&) = delete;
    ScreenText(ScreenText&&) = delete;
    ScreenText& operator = (ScreenText&&) = delete;

    void display(const char* msg, const uint8_t line, const uint16_t color);

private:
    DFRobot_ST7735_80x160_HW_SPI screen;
};

} } // mw::components

#endif // __COMPONENTS_SCREENTEXT_H__
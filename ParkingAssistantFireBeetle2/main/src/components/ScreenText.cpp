#include "src/components/ScreenText.h"

namespace mw { namespace components {

using namespace mw::helpers;

constexpr const uint8_t TFT_DC = D2;
constexpr const uint8_t TFT_CS = D6;
constexpr const uint8_t TFT_RST = D3;

ScreenText::ScreenText()
    : screen{ TFT_DC, TFT_CS, TFT_RST }
{
    screen.begin();
    screen.setTextSize(1);
    screen.fillScreen(COLOR_RGB565_BLACK);
    screen.setFont(&FreeMono12pt7b);
}

ScreenText& ScreenText::get() {
    static ScreenText instance;
    return instance;
}

void ScreenText::display(const char* msg, const uint8_t line, const uint16_t color) {
    MutexGuard guard{mutex};
    const uint8_t fontPos = 19 * (line + 1);
    const uint8_t rectPos = 5 + (line * 19);

    screen.setCursor(0, fontPos);
    screen.fillRect(0, rectPos, 160, 19, COLOR_RGB565_BLACK);
    screen.setTextColor(color);
    screen.print(msg);
}

} } // mw::components
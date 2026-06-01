#ifndef INVIEW_HPP
#define INVIEW_HPP

#include <gui_generated/in_screen/InViewBase.hpp>
#include <gui/in_screen/InPresenter.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/Unicode.hpp>

extern "C" {
#include "ui_variables.h"
}

class InView : public InViewBase
{
public:
    enum IOMode { MODE_IN = 0, MODE_OUT = 1, MODE_GPIO = 2 };
    static IOMode currentMode;

    static const int ITEM_COUNT = 4;
    static const uint16_t LABEL_BUF_SIZE = 12;

    // 5 available colors
    static const uint32_t COLOR_GREEN  = 0x337F5C;
    static const uint32_t COLOR_RED    = 0xD03B1E;
    static const uint32_t COLOR_GRAY   = 0x3D3C38;
    static const uint32_t COLOR_ORANGE = 0xFAB62E;
    static const uint32_t COLOR_BLUE   = 0x0B84B8;

    InView();
    virtual ~InView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void applyConfig();
protected:
    touchgfx::Unicode::UnicodeChar labelBuf[ITEM_COUNT][LABEL_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar titleBuf[LABEL_BUF_SIZE];
};

#endif // INVIEW_HPP

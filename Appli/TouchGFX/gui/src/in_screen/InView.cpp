#include <gui/in_screen/InView.hpp>

InView::IOMode InView::currentMode = InView::MODE_IN;

static const char* inLabels[4]   = { "Analog 1", "Analog 2", "Analog 3", "USB" };
static const uint32_t inColors[4] = { InView::COLOR_GREEN, InView::COLOR_ORANGE, InView::COLOR_GRAY, InView::COLOR_GREEN };

static const char* outLabels[4]  = { "Analog 1", "Analog 2", "Analog 3", "Analog 4" };
static const uint32_t outColors[4] = { InView::COLOR_GREEN, InView::COLOR_RED, InView::COLOR_GREEN, InView::COLOR_GREEN };

static const char* gpioLabels[4] = { "Pin 1", "Pin 2", "Pin 3", "Pin 4" };
static const uint32_t gpioColors[4] = { InView::COLOR_BLUE, InView::COLOR_BLUE, InView::COLOR_BLUE, InView::COLOR_BLUE };

InView::InView()
{
}

void InView::setupScreen()
{
    InViewBase::setupScreen();
    applyConfig();
}

void InView::tearDownScreen()
{
    InViewBase::tearDownScreen();
}

void InView::applyConfig()
{
    const char** labels;
    const uint32_t* colors;

    switch (currentMode)
    {
    case MODE_OUT:
        labels = outLabels;
        colors = outColors;
        break;
    case MODE_GPIO:
        labels = gpioLabels;
        colors = gpioColors;
        break;
    case MODE_IN:
    default:
        labels = inLabels;
        colors = inColors;
        break;
    }

    // Set labels
    touchgfx::Unicode::strncpy(labelBuf[0], labels[0], LABEL_BUF_SIZE);
    touchgfx::Unicode::strncpy(labelBuf[1], labels[1], LABEL_BUF_SIZE);
    touchgfx::Unicode::strncpy(labelBuf[2], labels[2], LABEL_BUF_SIZE);
    touchgfx::Unicode::strncpy(labelBuf[3], labels[3], LABEL_BUF_SIZE);

    textArea1.setWildcard(labelBuf[0]);
    textArea2.setWildcard(labelBuf[1]);
    textArea3.setWildcard(labelBuf[2]);
    textArea4.setWildcard(labelBuf[3]);
    textArea1.invalidate();
    textArea2.invalidate();
    textArea3.invalidate();
    textArea4.invalidate();

    // Set circle colors
    uint8_t r, g, b;

    r = (colors[0] >> 16) & 0xFF; g = (colors[0] >> 8) & 0xFF; b = colors[0] & 0xFF;
    circle1Painter.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    circle1.invalidate();

    r = (colors[1] >> 16) & 0xFF; g = (colors[1] >> 8) & 0xFF; b = colors[1] & 0xFF;
    circle2Painter.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    circle2.invalidate();

    r = (colors[2] >> 16) & 0xFF; g = (colors[2] >> 8) & 0xFF; b = colors[2] & 0xFF;
    circle3Painter.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    circle3.invalidate();

    r = (colors[3] >> 16) & 0xFF; g = (colors[3] >> 8) & 0xFF; b = colors[3] & 0xFF;
    circle4Painter.setColor(touchgfx::Color::getColorFromRGB(r, g, b));
    circle4.invalidate();
}

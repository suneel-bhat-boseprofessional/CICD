#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>

Screen1View::Screen1View()
    : currentColorState(0)
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    // Ensure button is touchable even with alpha=0
    imageChangeBtn.setTouchable(true);
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}


void Screen1View::changeScreenColor()
{
    // Cycle through colors: Red -> Blue -> Green -> White -> Black -> Transparent
    switch(currentColorState)
    {
        case 0: // Red
            colorImage.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
            colorImage.setAlpha(255);
            break;

        case 1: // Blue
            colorImage.setColor(touchgfx::Color::getColorFromRGB(0, 0, 255));
            colorImage.setAlpha(255);
            break;

        case 2: // Green
            colorImage.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
            colorImage.setAlpha(255);
            break;

        case 3: // White
            colorImage.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
            colorImage.setAlpha(255);
            break;

        case 4: // Black
            colorImage.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
            colorImage.setAlpha(255);
            break;

        case 5: // Transparent (0 intensity)
            colorImage.setAlpha(0);
            break;

        default:
            break;
    }

    // Invalidate to trigger redraw
    colorImage.invalidate();

    // Move to next color state
    currentColorState++;
    if(currentColorState > 5)
    {
        currentColorState = 0;
    }
}

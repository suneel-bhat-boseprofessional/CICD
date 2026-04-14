#include <gui/brightness_screen/BrightnessView.hpp>

BrightnessView::BrightnessView()
{

}

void BrightnessView::setupScreen()
{
    BrightnessViewBase::setupScreen();
    slider1.setValue(presenter->getBrightness());
    slider1.invalidate();
}

void BrightnessView::tearDownScreen()
{
    BrightnessViewBase::tearDownScreen();
}

void BrightnessView::sliderUpdate(int value)
{
    presenter->setBrightness(value);
}

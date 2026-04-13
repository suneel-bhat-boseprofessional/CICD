#ifndef BRIGHTNESSVIEW_HPP
#define BRIGHTNESSVIEW_HPP

#include <gui_generated/brightness_screen/BrightnessViewBase.hpp>
#include <gui/brightness_screen/BrightnessPresenter.hpp>

class BrightnessView : public BrightnessViewBase
{
public:
    BrightnessView();
    virtual ~BrightnessView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BRIGHTNESSVIEW_HPP

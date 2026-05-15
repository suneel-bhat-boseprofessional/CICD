#ifndef GPIOVIEW_HPP
#define GPIOVIEW_HPP

#include <gui_generated/gpio_screen/GPIOViewBase.hpp>
#include <gui/gpio_screen/GPIOPresenter.hpp>

class GPIOView : public GPIOViewBase
{
public:
    GPIOView();
    virtual ~GPIOView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // GPIOVIEW_HPP

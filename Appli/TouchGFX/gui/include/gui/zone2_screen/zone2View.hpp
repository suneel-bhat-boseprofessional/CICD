#ifndef ZONE2VIEW_HPP
#define ZONE2VIEW_HPP

#include <gui_generated/zone2_screen/zone2ViewBase.hpp>
#include <gui/zone2_screen/zone2Presenter.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/widgets/AbstractButton.hpp>

class CustomSlider : public touchgfx::Slider
{
public:
    void setFillerWidth(int width)
    {
        backgroundSelectedViewPort.setWidth(width);
        backgroundSelectedViewPort.invalidate();
    }

    int getIndicatorX() const
    {
        return indicator.getX();
    }

    int getIndicatorWidth() const
    {
        return indicator.getWidth();
    }
};

class zone2View : public zone2ViewBase
{
public:
    zone2View();
    virtual ~zone2View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    void volumeChanged(int value);
    void zoneUpdated();

protected:
    touchgfx::Callback<zone2View, const touchgfx::Slider&, int> sliderCallback;
    void sliderValueChanged(const touchgfx::Slider& slider, int value);
    void updateSliderFill(int value);

    // ✅ REQUIRED (missing earlier)
    touchgfx::Callback<zone2View, const touchgfx::AbstractButton&> volumeBtnCallback;
    void volumeBtnClicked(const touchgfx::AbstractButton& src);

    int lastVolume;
    bool suppressGainTx;

    touchgfx::Unicode::UnicodeChar volumeBuffer[8];
    touchgfx::Unicode::UnicodeChar zoneNameBuffer[32];
};

#endif

#include <gui/zone2_screen/zone2View.hpp>
#include <gui/model/Model.hpp>

zone2View::zone2View() :
    sliderCallback(this, &zone2View::sliderValueChanged)
{
}

void zone2View::setupScreen()
{
    zone2ViewBase::setupScreen();

    int zone   = presenter->getSelectedZone();
    int volume = presenter->getZoneVolume(zone);

    slider1.setValueRange(0, 100);
    slider1.setNewValueCallback(sliderCallback);
    slider1.setValue(volume);

    updateSliderFill(volume);

    Unicode::snprintf(volumeBuffer, 8, "%d", volume);
    textArea2.setWildcard(volumeBuffer);
    textArea2.invalidate();

    const char* name = modelInstance->getZoneName(zone);
    if (name != 0 && name[0] != '\0')
    {
        Unicode::fromUTF8((const uint8_t*)name, zoneNameBuffer, 32);
    }
    else
    {
        Unicode::snprintf(zoneNameBuffer, 32, "Zone %d", zone + 1);
    }
    textArea3.setWildcard(zoneNameBuffer);
    textArea3.invalidate();
}

void zone2View::tearDownScreen()
{
    zone2ViewBase::tearDownScreen();
}

void zone2View::sliderValueChanged(const touchgfx::Slider& slider, int value)
{
    volumeChanged(value);
}

void zone2View::volumeChanged(int value)
{
    int zone = presenter->getSelectedZone();
    presenter->setZoneVolume(zone, value);

    updateSliderFill(value);

    Unicode::snprintf(volumeBuffer, 8, "%d", value);
    textArea2.invalidate();
}

void zone2View::updateSliderFill(int value)
{
    CustomSlider& cs = static_cast<CustomSlider&>(slider1);
    int fillerWidth = cs.getIndicatorX() + (cs.getIndicatorWidth() / 2);

    cs.setFillerWidth(fillerWidth);
}

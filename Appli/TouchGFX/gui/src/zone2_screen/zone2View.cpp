#include <gui/zone2_screen/zone2View.hpp>
#include <gui/model/Model.hpp>

zone2View::zone2View() :
    sliderCallback(this, &zone2View::sliderValueChanged)
{
}

void zone2View::setupScreen()
{
    zone2ViewBase::setupScreen();

    int zone = presenter->getSelectedZone();
    int volume = presenter->getZoneVolume(zone);

    // Wire slider callback
    slider1.setNewValueCallback(sliderCallback);

    // Set slider to saved volume
    slider1.setValue(volume);

    // Show current volume in textArea2
    Unicode::snprintf(volumeBuffer, 8, "%d", volume);
    textArea2.setWildcard(volumeBuffer);
    textArea2.invalidate();

    // Show selected zone name in textArea3
    const char* name = modelInstance->getZoneName(zone);
    if(name != 0 && name[0] != '\0')
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

    // Update live display in textArea2
    Unicode::snprintf(volumeBuffer, 8, "%d", value);
    textArea2.invalidate();
}

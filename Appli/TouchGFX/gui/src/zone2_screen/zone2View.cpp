#include <gui/zone2_screen/zone2View.hpp>

zone2View::zone2View()
{

}

void zone2View::setupScreen()
{
    zone2ViewBase::setupScreen();

    int zone = presenter->getSelectedZone();
    int volume = presenter->getZoneVolume(zone);

    slider1.setValue(volume);
}

void zone2View::tearDownScreen()
{
    zone2ViewBase::tearDownScreen();
}

void zone2View::volumeChanged(int value)
{
    int zone = presenter->getSelectedZone();
    presenter->setZoneVolume(zone, value);
}

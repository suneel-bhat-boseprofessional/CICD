#include <gui/zone2_screen/zone2Presenter.hpp>
#include <gui/zone2_screen/zone2View.hpp>
#include <gui/model/Model.hpp>

zone2Presenter::zone2Presenter(zone2View& v)
    : view(v)
{
}

void zone2Presenter::activate()
{
}

void zone2Presenter::deactivate()
{
}

int zone2Presenter::getSelectedZone()
{
    return model->getSelectedZone();
}

int zone2Presenter::getZoneVolume(int index)
{
    return model->getZoneVolume(index);
}

void zone2Presenter::setZoneVolume(int index, int value)
{
    model->setZoneVolume(index, value);
}

void zone2Presenter::zoneNamesUpdated()
{
    view.zoneUpdated();
}

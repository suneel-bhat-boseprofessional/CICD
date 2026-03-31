#include <gui/zone_screen/zonePresenter.hpp>
#include <gui/zone_screen/zoneView.hpp>
#include <gui/model/Model.hpp>

zonePresenter::zonePresenter(zoneView& v)
    : view(v)
{
}

void zonePresenter::activate()
{
}

void zonePresenter::deactivate()
{
}

void zonePresenter::zoneNamesUpdated()
{
    view.zoneNamesUpdated();
}

void zonePresenter::setSelectedZone(int index)
{
    model->setSelectedZone(index);
}

#include <gui/zone_screen/zonePresenter.hpp>
#include <gui/zone_screen/zoneView.hpp>
#include <gui/model/Model.hpp>

zonePresenter::zonePresenter(zoneView& v)
    : view(v)
{
}

void zonePresenter::activate()
{
    // CRITICAL: without bind(), modelListener is null and tick() never
    // notifies the view — this was the root cause of the stale GUI.
    model->bind(this);
}

void zonePresenter::deactivate()
{
    // Detach so tick() doesn't call a dead presenter after screen exit
    model->bind(0);
}

void zonePresenter::zoneNamesUpdated()
{
    view.zoneNamesUpdated();
}

void zonePresenter::setSelectedZone(int index)
{
    model->setSelectedZone(index);
}

int zonePresenter::getZoneCount() const
{
    return model->getZoneCount();
}

void zonePresenter::notifyGoToLaunch()
{
    view.goToLaunchScreen();
}

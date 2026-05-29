#include <gui/metering_screen/MeteringPresenter.hpp>
#include <gui/metering_screen/MeteringView.hpp>
#include <gui/model/Model.hpp>
#include "../../../Core/Inc/protocol.h"

MeteringPresenter::MeteringPresenter(MeteringView& v)
    : view(v)
{
}

void MeteringPresenter::activate()
{
    // STEP 1: bind first — tick() can now notify this presenter
    model->bind(this);

    // STEP 2: give the view the model pointer so containers can read names
    view.setModelPtr(model);

    // STEP 3: now push the current zone count into the scroll list
    view.updateSourceConfig(model->getZoneCount());

    // STEP 4: request fresh data from MCU
    Protocol_SendAction("MeterInfo");
}

void MeteringPresenter::deactivate()
{
    model->bind(0);
}

void MeteringPresenter::notifySourceConfigChanged()
{
    view.setModelPtr(model);
    view.updateSourceConfig(model->getZoneCount());
}

void MeteringPresenter::zoneNamesUpdated()
{
    view.setModelPtr(model);
    view.updateSourceConfig(model->getZoneCount());
}

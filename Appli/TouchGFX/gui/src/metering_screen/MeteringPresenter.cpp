#include <gui/metering_screen/MeteringView.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>

// Request action via protocol
#include "../../../Core/Inc/protocol.h"


MeteringPresenter::MeteringPresenter(MeteringView& v)
    : view(v)
{

}

void MeteringPresenter::activate()
{
    Protocol_SendAction("MeterInfo");

}

void MeteringPresenter::deactivate()
{

}

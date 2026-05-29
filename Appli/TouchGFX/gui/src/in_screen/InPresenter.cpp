#include <gui/in_screen/InView.hpp>
#include <gui/in_screen/InPresenter.hpp>

// Send input/output/gpio info request when this screen activates
#include "../../../Core/Inc/protocol.h"

InPresenter::InPresenter(InView& v)
    : view(v)
{

}

void InPresenter::activate()
{
    using namespace touchgfx;
    switch (InView::currentMode)
    {
    case InView::MODE_IN:
        Protocol_SendAction("inputInfo");
        break;
    case InView::MODE_OUT:
        Protocol_SendAction("outputInfo");
        break;
    case InView::MODE_GPIO:
        Protocol_SendAction("gpioInfo");
        break;
    default:
        break;
    }

}

void InPresenter::deactivate()
{

}

void InPresenter::notifyIOColorsChanged()
{
    view.applyConfig();
}

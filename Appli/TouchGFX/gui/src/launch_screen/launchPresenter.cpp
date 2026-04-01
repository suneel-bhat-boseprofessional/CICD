#include <gui/launch_screen/launchView.hpp>
#include <gui/launch_screen/launchPresenter.hpp>

launchPresenter::launchPresenter(launchView& v)
    : view(v)
{

}

void launchPresenter::activate()
{

}

void launchPresenter::deactivate()
{

}

void launchPresenter::notifyReadyReceived()
{
    view.goToHomeScreen();
}

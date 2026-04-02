#include <gui/launch_screen/launchView.hpp>

launchView::launchView()
{

}

void launchView::setupScreen()
{
    launchViewBase::setupScreen();
}

void launchView::tearDownScreen()
{
    launchViewBase::tearDownScreen();
}

void launchView::handleTickEvent()
{
    // Override: do NOT call launchViewBase::handleTickEvent()
    // to disable the auto-transition to home after 180 ticks.
    // Navigation is driven by the "ready" UART message instead.
}

void launchView::goToHomeScreen()
{
    application().gotohomeScreenNoTransition();
}

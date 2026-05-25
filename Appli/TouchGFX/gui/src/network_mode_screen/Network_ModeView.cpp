#include <gui/network_mode_screen/Network_ModeView.hpp>

bool Network_ModeView::dhcpSelected = false;

Network_ModeView::Network_ModeView()
{
}

void Network_ModeView::setupScreen()
{
    Network_ModeViewBase::setupScreen();
}

void Network_ModeView::tearDownScreen()
{
    Network_ModeViewBase::tearDownScreen();
}

void Network_ModeView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        // image2 = DHCP option
        if (x >= image2.getX() && x < image2.getX() + (int16_t)image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + (int16_t)image2.getHeight())
        {
            dhcpSelected = true;
            return;
        }

        // image3 = Static option
        if (x >= image3.getX() && x < image3.getX() + (int16_t)image3.getWidth() &&
            y >= image3.getY() && y < image3.getY() + (int16_t)image3.getHeight())
        {
            dhcpSelected = false;
            return;
        }
    }

    Network_ModeViewBase::handleClickEvent(event);
}

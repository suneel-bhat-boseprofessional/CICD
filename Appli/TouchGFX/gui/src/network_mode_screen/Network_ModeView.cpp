#include <gui/network_mode_screen/Network_ModeView.hpp>
#include <gui/network_config_screen/Network_ConfigView.hpp>

bool Network_ModeView::dhcpSelected[2] = { true, true };

Network_ModeView::Network_ModeView()
{
}

void Network_ModeView::setupScreen()
{
    Network_ModeViewBase::setupScreen();

    int src = static_cast<int>(Network_ConfigView::configSource);

    // Reflect current selection for active interface
    if (dhcpSelected[src])
    {
        image2.setVisible(true);
        image3.setVisible(false);
    }
    else
    {
        image2.setVisible(false);
        image3.setVisible(true);
    }
    image2.invalidate();
    image3.invalidate();
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
        int src = static_cast<int>(Network_ConfigView::configSource);

        // image2 = DHCP option
        if (x >= image2.getX() && x < image2.getX() + (int16_t)image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + (int16_t)image2.getHeight())
        {
            dhcpSelected[src] = true;
            image2.setVisible(true);
            image3.setVisible(false);
            image2.invalidate();
            image3.invalidate();
            return;
        }

        // image3 = Static option
        if (x >= image3.getX() && x < image3.getX() + (int16_t)image3.getWidth() &&
            y >= image3.getY() && y < image3.getY() + (int16_t)image3.getHeight())
        {
            dhcpSelected[src] = false;
            image2.setVisible(false);
            image3.setVisible(true);
            image2.invalidate();
            image3.invalidate();
            return;
        }
    }

    Network_ModeViewBase::handleClickEvent(event);
}

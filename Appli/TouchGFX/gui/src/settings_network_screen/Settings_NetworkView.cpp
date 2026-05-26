#include <gui/settings_network_screen/Settings_NetworkView.hpp>
#include <gui/network_config_screen/Network_ConfigView.hpp>

Settings_NetworkView::Settings_NetworkView()
{

}

void Settings_NetworkView::setupScreen()
{
    Settings_NetworkViewBase::setupScreen();
    image1.setVisible(true);
    image2.setVisible(false);
    image1.invalidate();
    image2.invalidate();
}

void Settings_NetworkView::tearDownScreen()
{
    Settings_NetworkViewBase::tearDownScreen();
}

void Settings_NetworkView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        // Ethernet settings area (textArea2 region)
        if (x >= textArea2.getX() && x < textArea2.getX() + textArea2.getWidth() &&
            y >= image1.getY() && y < image1.getY() + image1.getHeight())
        {
            image1.setVisible(true);
            image2.setVisible(false);
            image1.invalidate();
            image2.invalidate();
            Network_ConfigView::configSource = Network_ConfigView::SOURCE_ETHERNET;
            application().gotoNetwork_ConfigScreenNoTransition();
            return;
        }

        // WiFi settings area (textArea1 region)
        if (x >= textArea1.getX() && x < textArea1.getX() + textArea1.getWidth() &&
            y >= image2.getY() && y < image2.getY() + image2.getHeight())
        {
            image2.setVisible(true);
            image1.setVisible(false);
            image1.invalidate();
            image2.invalidate();
            Network_ConfigView::configSource = Network_ConfigView::SOURCE_WIFI;
            application().gotoNetwork_ConfigScreenNoTransition();
            return;
        }
    }
    Settings_NetworkViewBase::handleClickEvent(event);
}

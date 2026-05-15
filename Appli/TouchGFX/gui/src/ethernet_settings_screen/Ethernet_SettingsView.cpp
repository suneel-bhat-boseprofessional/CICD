#include <gui/ethernet_settings_screen/Ethernet_SettingsView.hpp>

int Ethernet_SettingsView::savedSelection = 0;

Ethernet_SettingsView::Ethernet_SettingsView()
{
}

void Ethernet_SettingsView::setupScreen()
{
    Ethernet_SettingsViewBase::setupScreen();
    if (savedSelection == 0 || savedSelection == 1)
    {
        image1.setVisible(true);
        image2.setVisible(false);
    }
    else
    {
        image1.setVisible(false);
        image2.setVisible(true);
    }
    image1.invalidate();
    image2.invalidate();
}

void Ethernet_SettingsView::tearDownScreen()
{
    Ethernet_SettingsViewBase::tearDownScreen();
}

void Ethernet_SettingsView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        // image1 click → Network_Config
        if (x >= image1.getX() && x < image1.getX() + (int16_t)image1.getWidth() &&
            y >= image1.getY() && y < image1.getY() + (int16_t)image1.getHeight())
        {
            savedSelection = 1;
            application().gotoNetwork_ConfigScreenNoTransition();
            return;
        }

        // image2 click → Network_Config
        if (x >= image2.getX() && x < image2.getX() + (int16_t)image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + (int16_t)image2.getHeight())
        {
            savedSelection = 2;
            application().gotoNetwork_ConfigScreenNoTransition();
            return;
        }
    }

    Ethernet_SettingsViewBase::handleClickEvent(event);
}

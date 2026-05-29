#ifndef ETHERNET_SETTINGSVIEW_HPP
#define ETHERNET_SETTINGSVIEW_HPP

#include <gui_generated/ethernet_settings_screen/Ethernet_SettingsViewBase.hpp>
#include <gui/ethernet_settings_screen/Ethernet_SettingsPresenter.hpp>
#include <touchgfx/hal/HAL.hpp>

class Ethernet_SettingsView : public Ethernet_SettingsViewBase
{
public:
    Ethernet_SettingsView();
    virtual ~Ethernet_SettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    static int savedSelection; // 0=none, 1=image1 selected, 2=image2 selected
protected:
};

#endif // ETHERNET_SETTINGSVIEW_HPP

#ifndef SETTINGS_NETWORKVIEW_HPP
#define SETTINGS_NETWORKVIEW_HPP

#include <gui_generated/settings_network_screen/Settings_NetworkViewBase.hpp>
#include <gui/settings_network_screen/Settings_NetworkPresenter.hpp>

class Settings_NetworkView : public Settings_NetworkViewBase
{
public:
    Settings_NetworkView();
    virtual ~Settings_NetworkView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
protected:
};

#endif // SETTINGS_NETWORKVIEW_HPP

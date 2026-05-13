#ifndef BT_SETTINGSVIEW_HPP
#define BT_SETTINGSVIEW_HPP

#include <gui_generated/bt_settings_screen/BT_SettingsViewBase.hpp>
#include <gui/bt_settings_screen/BT_SettingsPresenter.hpp>

class BT_SettingsView : public BT_SettingsViewBase
{
public:
    BT_SettingsView();
    virtual ~BT_SettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // BT_SETTINGSVIEW_HPP

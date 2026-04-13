#ifndef SETTINGSVIEW_HPP
#define SETTINGSVIEW_HPP

#include <gui_generated/settings_screen/SettingsViewBase.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <touchgfx/Callback.hpp>

class SettingsView : public SettingsViewBase
{
public:
    SettingsView();
    virtual ~SettingsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer4& item, int16_t itemIndex);

protected:
    touchgfx::Callback<SettingsView, int16_t> itemSelectedCallback;
    void itemSelected(int16_t itemIndex);
};

#endif // SETTINGSVIEW_HPP

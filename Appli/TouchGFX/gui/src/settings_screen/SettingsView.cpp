#include <gui/settings_screen/SettingsView.hpp>

SettingsView::SettingsView() :
    itemSelectedCallback(this, &SettingsView::itemSelected)
{

}

void SettingsView::setupScreen()
{
    SettingsViewBase::setupScreen();
    scrollList1.setItemSelectedCallback(itemSelectedCallback);
}

void SettingsView::tearDownScreen()
{
    SettingsViewBase::tearDownScreen();
}

void SettingsView::scrollList1UpdateItem(CustomContainer4& item, int16_t itemIndex)
{
    item.setSettingItem(itemIndex);
}

void SettingsView::itemSelected(int16_t itemIndex)
{
    if (itemIndex == 0) // "System Information" item
    {
        application().gotoSystem_InformationScreenNoTransition();
    }
    else if (itemIndex == 1) // "Network" item
    {
        application().gotoSettings_NetworkScreenNoTransition();
    }
    else if (itemIndex == 2) // "Display" item
    {
        application().gotoBrightnessScreenNoTransition();
    }
}

#ifndef BT_DEVICESVIEW_HPP
#define BT_DEVICESVIEW_HPP

#include <gui_generated/bt_devices_screen/BT_DevicesViewBase.hpp>
#include <gui/bt_devices_screen/BT_DevicesPresenter.hpp>

class BT_DevicesView : public BT_DevicesViewBase
{
public:
    BT_DevicesView();
    virtual ~BT_DevicesView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
protected:
    static const uint16_t TEXTAREA2_SIZE = 30;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];
    bool popupVisible;
};

#endif // BT_DEVICESVIEW_HPP

#ifndef BLUETOOTH_2VIEW_HPP
#define BLUETOOTH_2VIEW_HPP

#include <gui_generated/bluetooth_2_screen/Bluetooth_2ViewBase.hpp>
#include <gui/bluetooth_2_screen/Bluetooth_2Presenter.hpp>

class Bluetooth_2View : public Bluetooth_2ViewBase
{
public:
    Bluetooth_2View();
    virtual ~Bluetooth_2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
protected:
    void updateBluetoothWidgetsAlpha();
};

#endif // BLUETOOTH_2VIEW_HPP

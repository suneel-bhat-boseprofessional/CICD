#ifndef NETWORK_MODEVIEW_HPP
#define NETWORK_MODEVIEW_HPP

#include <gui_generated/network_mode_screen/Network_ModeViewBase.hpp>
#include <gui/network_mode_screen/Network_ModePresenter.hpp>

class Network_ModeView : public Network_ModeViewBase
{
public:
    Network_ModeView();
    virtual ~Network_ModeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);

    static bool dhcpSelected[2]; // [0]=Ethernet, [1]=WiFi
protected:
};

#endif // NETWORK_MODEVIEW_HPP

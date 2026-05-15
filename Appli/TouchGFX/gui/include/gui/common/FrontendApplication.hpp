#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent()
    {
        model.tick();
        FrontendApplicationBase::handleTickEvent();
    }

    void gotoSettingsScreenNoTransition();
    void gotoBrightnessScreenNoTransition();
    void gotoMeteringScreenNoTransition();
    void gotoSystem_InformationScreenNoTransition();
    void gotoBluetooth_2ScreenNoTransition();
    void gotoStudio_GoldScreenNoTransition();
    void gotoBT_DevicesScreenNoTransition();
    void gotoBT_SettingsScreenNoTransition();
    void gotoSettings_NetworkScreenNoTransition();
    void gotoInoutScreenNoTransition();
    void gotoGPIOScreenNoTransition();
    void gotoInScreenNoTransition();
    void gotoOutScreenNoTransition();
    void gotoNotificationsScreenNoTransition();
    void gotoEthernet_SettingsScreenNoTransition();
    void gotoNetwork_ConfigScreenNoTransition();

private:
    void gotoSettingsScreenNoTransitionImpl();
    void gotoBrightnessScreenNoTransitionImpl();
    void gotoMeteringScreenNoTransitionImpl();
    void gotoSystem_InformationScreenNoTransitionImpl();
    void gotoBluetooth_2ScreenNoTransitionImpl();
    void gotoStudio_GoldScreenNoTransitionImpl();
    void gotoBT_DevicesScreenNoTransitionImpl();
    void gotoBT_SettingsScreenNoTransitionImpl();
    void gotoSettings_NetworkScreenNoTransitionImpl();
    void gotoInoutScreenNoTransitionImpl();
    void gotoGPIOScreenNoTransitionImpl();
    void gotoInScreenNoTransitionImpl();
    void gotoOutScreenNoTransitionImpl();
    void gotoNotificationsScreenNoTransitionImpl();
    void gotoEthernet_SettingsScreenNoTransitionImpl();
    void gotoNetwork_ConfigScreenNoTransitionImpl();

    touchgfx::Callback<FrontendApplication> settingsTransitionCb;
    touchgfx::Callback<FrontendApplication> brightnessTransitionCb;
    touchgfx::Callback<FrontendApplication> meteringTransitionCb;
    touchgfx::Callback<FrontendApplication> sysInfoTransitionCb;
    touchgfx::Callback<FrontendApplication> bluetooth2TransitionCb;
    touchgfx::Callback<FrontendApplication> studioGoldTransitionCb;
    touchgfx::Callback<FrontendApplication> btDevicesTransitionCb;
    touchgfx::Callback<FrontendApplication> btSettingsTransitionCb;
    touchgfx::Callback<FrontendApplication> settingsNetworkTransitionCb;
    touchgfx::Callback<FrontendApplication> inoutTransitionCb;
    touchgfx::Callback<FrontendApplication> gpioTransitionCb;
    touchgfx::Callback<FrontendApplication> inTransitionCb;
    touchgfx::Callback<FrontendApplication> outTransitionCb;
    touchgfx::Callback<FrontendApplication> notificationsTransitionCb;
    touchgfx::Callback<FrontendApplication> ethernetSettingsTransitionCb;
    touchgfx::Callback<FrontendApplication> networkConfigTransitionCb;
};

#endif // FRONTENDAPPLICATION_HPP

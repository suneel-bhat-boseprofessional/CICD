#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <gui/brightness_screen/BrightnessView.hpp>
#include <gui/brightness_screen/BrightnessPresenter.hpp>
#include <gui/metering_screen/MeteringView.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>
#include <gui/studio_gold_screen/Studio_GoldView.hpp>
#include <gui/studio_gold_screen/Studio_GoldPresenter.hpp>
#include <gui/bluetooth_2_screen/Bluetooth_2View.hpp>
#include <gui/bluetooth_2_screen/Bluetooth_2Presenter.hpp>
#include <gui/bt_devices_screen/BT_DevicesView.hpp>
#include <gui/bt_devices_screen/BT_DevicesPresenter.hpp>
#include <gui/bt_settings_screen/BT_SettingsView.hpp>
#include <gui/bt_settings_screen/BT_SettingsPresenter.hpp>
#include <gui/settings_network_screen/Settings_NetworkView.hpp>
#include <gui/settings_network_screen/Settings_NetworkPresenter.hpp>
#include <gui/inout_screen/InoutView.hpp>
#include <gui/inout_screen/InoutPresenter.hpp>
#include <gui/gpio_screen/GPIOView.hpp>
#include <gui/gpio_screen/GPIOPresenter.hpp>
#include <gui/in_screen/InView.hpp>
#include <gui/in_screen/InPresenter.hpp>
#include <gui/out_screen/OutView.hpp>
#include <gui/out_screen/OutPresenter.hpp>
#include <gui/notifications_screen/NotificationsView.hpp>
#include <gui/notifications_screen/NotificationsPresenter.hpp>
#include <gui/ethernet_settings_screen/Ethernet_SettingsView.hpp>
#include <gui/ethernet_settings_screen/Ethernet_SettingsPresenter.hpp>
#include <gui/network_config_screen/Network_ConfigView.hpp>
#include <gui/network_config_screen/Network_ConfigPresenter.hpp>
#include <gui/network_mode_screen/Network_ModeView.hpp>
#include <gui/network_mode_screen/Network_ModePresenter.hpp>
#include <gui/ip_adress_screen/IP_AdressView.hpp>
#include <gui/ip_adress_screen/IP_AdressPresenter.hpp>
#include <gui/device_information_screen/Device_InformationView.hpp>
#include <gui/device_information_screen/Device_InformationPresenter.hpp>

FrontendApplication::FrontendApplication(Model& m, FrontendHeap& heap)
    : FrontendApplicationBase(m, heap)
{

}

void FrontendApplication::gotoSettingsScreenNoTransition()
{
    settingsTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoSettingsScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &settingsTransitionCb;
}

void FrontendApplication::gotoSettingsScreenNoTransitionImpl()
{
    touchgfx::makeTransition<SettingsView, SettingsPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoBrightnessScreenNoTransition()
{
    brightnessTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoBrightnessScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &brightnessTransitionCb;
}

void FrontendApplication::gotoBrightnessScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BrightnessView, BrightnessPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoMeteringScreenNoTransition()
{
    meteringTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoMeteringScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &meteringTransitionCb;
}

void FrontendApplication::gotoMeteringScreenNoTransitionImpl()
{
    touchgfx::makeTransition<MeteringView, MeteringPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSystem_InformationScreenNoTransition()
{
    // Screen removed from Designer - no-op
}

void FrontendApplication::gotoSystem_InformationScreenNoTransitionImpl()
{
    // Screen removed from Designer - no-op
}

void FrontendApplication::gotoBluetooth_2ScreenNoTransition()
{
    bluetooth2TransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoBluetooth_2ScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &bluetooth2TransitionCb;
}

void FrontendApplication::gotoBluetooth_2ScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Bluetooth_2View, Bluetooth_2Presenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoStudio_GoldScreenNoTransition()
{
    studioGoldTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoStudio_GoldScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &studioGoldTransitionCb;
}

void FrontendApplication::gotoStudio_GoldScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Studio_GoldView, Studio_GoldPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoBT_DevicesScreenNoTransition()
{
    btDevicesTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoBT_DevicesScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &btDevicesTransitionCb;
}

void FrontendApplication::gotoBT_DevicesScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BT_DevicesView, BT_DevicesPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoBT_SettingsScreenNoTransition()
{
    btSettingsTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoBT_SettingsScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &btSettingsTransitionCb;
}

void FrontendApplication::gotoBT_SettingsScreenNoTransitionImpl()
{
    touchgfx::makeTransition<BT_SettingsView, BT_SettingsPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoSettings_NetworkScreenNoTransition()
{
    settingsNetworkTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoSettings_NetworkScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &settingsNetworkTransitionCb;
}

void FrontendApplication::gotoSettings_NetworkScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Settings_NetworkView, Settings_NetworkPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoInoutScreenNoTransition()
{
    inoutTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoInoutScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &inoutTransitionCb;
}

void FrontendApplication::gotoInoutScreenNoTransitionImpl()
{
    touchgfx::makeTransition<InoutView, InoutPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoGPIOScreenNoTransition()
{
    gpioTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoGPIOScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &gpioTransitionCb;
}

void FrontendApplication::gotoGPIOScreenNoTransitionImpl()
{
    touchgfx::makeTransition<GPIOView, GPIOPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoInScreenNoTransition()
{
    inTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoInScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &inTransitionCb;
}

void FrontendApplication::gotoInScreenNoTransitionImpl()
{
    touchgfx::makeTransition<InView, InPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoOutScreenNoTransition()
{
    outTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoOutScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &outTransitionCb;
}

void FrontendApplication::gotoOutScreenNoTransitionImpl()
{
    touchgfx::makeTransition<OutView, OutPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoNotificationsScreenNoTransition()
{
    notificationsTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoNotificationsScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &notificationsTransitionCb;
}

void FrontendApplication::gotoNotificationsScreenNoTransitionImpl()
{
    touchgfx::makeTransition<NotificationsView, NotificationsPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoEthernet_SettingsScreenNoTransition()
{
    ethernetSettingsTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoEthernet_SettingsScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &ethernetSettingsTransitionCb;
}

void FrontendApplication::gotoEthernet_SettingsScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Ethernet_SettingsView, Ethernet_SettingsPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoNetwork_ConfigScreenNoTransition()
{
    networkConfigTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoNetwork_ConfigScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &networkConfigTransitionCb;
}

void FrontendApplication::gotoNetwork_ConfigScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Network_ConfigView, Network_ConfigPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoNetwork_Mode_ScreenNoTransition()
{
    networkModeTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoNetwork_Mode_ScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &networkModeTransitionCb;
}

void FrontendApplication::gotoNetwork_Mode_ScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Network_ModeView, Network_ModePresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoIP_AdressScreenNoTransition()
{
    ipAdressTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoIP_AdressScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &ipAdressTransitionCb;
}

void FrontendApplication::gotoIP_AdressScreenNoTransitionImpl()
{
    touchgfx::makeTransition<IP_AdressView, IP_AdressPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

void FrontendApplication::gotoDevice_InformationScreenNoTransition()
{
    deviceInfoTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoDevice_InformationScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &deviceInfoTransitionCb;
}

void FrontendApplication::gotoDevice_InformationScreenNoTransitionImpl()
{
    touchgfx::makeTransition<Device_InformationView, Device_InformationPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
}

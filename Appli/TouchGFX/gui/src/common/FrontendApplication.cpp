#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <gui/brightness_screen/BrightnessView.hpp>
#include <gui/brightness_screen/BrightnessPresenter.hpp>
#include <gui/metering_screen/MeteringView.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>
#include <gui/system_information_screen/System_InformationView.hpp>
#include <gui/system_information_screen/System_InformationPresenter.hpp>
#include <gui/studio_gold_screen/Studio_GoldView.hpp>
#include <gui/studio_gold_screen/Studio_GoldPresenter.hpp>
#include <gui/bluetooth_2_screen/Bluetooth_2View.hpp>
#include <gui/bluetooth_2_screen/Bluetooth_2Presenter.hpp>
#include <gui/bt_devices_screen/BT_DevicesView.hpp>
#include <gui/bt_devices_screen/BT_DevicesPresenter.hpp>

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
    sysInfoTransitionCb = touchgfx::Callback<FrontendApplication>(this, &FrontendApplication::gotoSystem_InformationScreenNoTransitionImpl);
    pendingScreenTransitionCallback = &sysInfoTransitionCb;
}

void FrontendApplication::gotoSystem_InformationScreenNoTransitionImpl()
{
    touchgfx::makeTransition<System_InformationView, System_InformationPresenter, touchgfx::NoTransition, Model>(&currentScreen, &currentPresenter, frontendHeap, &currentTransition, &model);
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

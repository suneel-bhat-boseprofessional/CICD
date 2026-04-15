#include <gui/common/FrontendApplication.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/transitions/NoTransition.hpp>
#include <gui/settings_screen/SettingsView.hpp>
#include <gui/settings_screen/SettingsPresenter.hpp>
#include <gui/brightness_screen/BrightnessView.hpp>
#include <gui/brightness_screen/BrightnessPresenter.hpp>
#include <gui/metering_screen/MeteringView.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>

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

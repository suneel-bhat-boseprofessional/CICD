#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <gui_generated/common/FrontendApplicationBase.hpp>
#include "buildflags.h"

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

    virtual void changeToStartScreen()
    {
#if GGEC_MODE
        gotoScreen1ScreenNoTransition();
#else
        gotolaunchScreenNoTransition();
#endif
    }

    void gotoSettingsScreenNoTransition();
    void gotoBrightnessScreenNoTransition();
    void gotoMeteringScreenNoTransition();
    void gotoSystem_InformationScreenNoTransition();

private:
    void gotoSettingsScreenNoTransitionImpl();
    void gotoBrightnessScreenNoTransitionImpl();
    void gotoMeteringScreenNoTransitionImpl();
    void gotoSystem_InformationScreenNoTransitionImpl();

    touchgfx::Callback<FrontendApplication> settingsTransitionCb;
    touchgfx::Callback<FrontendApplication> brightnessTransitionCb;
    touchgfx::Callback<FrontendApplication> meteringTransitionCb;
    touchgfx::Callback<FrontendApplication> sysInfoTransitionCb;
};

#endif // FRONTENDAPPLICATION_HPP

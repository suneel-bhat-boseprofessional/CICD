#ifndef FACTORY_RESETVIEW_HPP
#define FACTORY_RESETVIEW_HPP

#include <gui_generated/factory_reset_screen/Factory_ResetViewBase.hpp>
#include <gui/factory_reset_screen/Factory_ResetPresenter.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/widgets/AbstractButton.hpp>

class Factory_ResetView : public Factory_ResetViewBase
{
public:
    Factory_ResetView();
    virtual ~Factory_ResetView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

protected:
    bool resetting;
    int progressValue;
    touchgfx::Unicode::UnicodeChar percentBuf[8];

    touchgfx::Callback<Factory_ResetView, const touchgfx::AbstractButton&> buttonCallback;
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
};

#endif // FACTORY_RESETVIEW_HPP

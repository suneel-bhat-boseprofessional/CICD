#include <gui/factory_reset_screen/Factory_ResetView.hpp>
#include <touchgfx/Color.hpp>

Factory_ResetView::Factory_ResetView() :
    resetting(false),
    progressValue(0),
    buttonCallback(this, &Factory_ResetView::buttonCallbackHandler)
{
    percentBuf[0] = 0;
}

void Factory_ResetView::setupScreen()
{
    Factory_ResetViewBase::setupScreen();

    // Initially hide the progress bar and percentage text
    lineProgress1.setVisible(false);
    textArea4.setVisible(false);

    // Set up button1 click callback
    button1.setAction(buttonCallback);
}

void Factory_ResetView::tearDownScreen()
{
    Factory_ResetViewBase::tearDownScreen();
}

void Factory_ResetView::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src != &button1 || resetting)
        return;

    resetting = true;
    progressValue = 0;

    // Hide everything except flexButton1 and image1
    textArea1.setVisible(false);
    button1.setVisible(false);
    textArea2.setVisible(false);
    textArea3.setVisible(false);

    // Show progress bar and percentage
    lineProgress1.setVisible(true);
    lineProgress1.setValue(0);
    textArea4.setVisible(true);

    // Update percentage text
    touchgfx::Unicode::snprintf(percentBuf, 8, "%d", progressValue);
    textArea4.setWildcard(percentBuf);

    // Invalidate all
    textArea1.invalidate();
    button1.invalidate();
    textArea2.invalidate();
    textArea3.invalidate();
    lineProgress1.invalidate();
    textArea4.invalidate();
}

void Factory_ResetView::handleTickEvent()
{
    if (!resetting)
        return;

    progressValue++;
    if (progressValue > 100)
    {
        // Done - go back to settings
        resetting = false;
        application().gotoSettingsScreenNoTransition();
        return;
    }

    lineProgress1.setValue(progressValue);
    lineProgress1.invalidate();

    touchgfx::Unicode::snprintf(percentBuf, 8, "%d", progressValue);
    textArea4.setWildcard(percentBuf);
    textArea4.invalidate();
}

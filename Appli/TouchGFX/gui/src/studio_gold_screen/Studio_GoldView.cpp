#include <gui/studio_gold_screen/Studio_GoldView.hpp>
#include <stdlib.h>

Studio_GoldView::Studio_GoldView() :
    flexButtonCallback(this, &Studio_GoldView::flexButtonClicked)
{

}

void Studio_GoldView::setupScreen()
{
    Studio_GoldViewBase::setupScreen();
    flexButton1.setAction(flexButtonCallback);

    touchgfx::Unicode::snprintf(buf1, BUF_SIZE, "%d", rand() % 100);
    touchgfx::Unicode::snprintf(buf3, BUF_SIZE, "%d", rand() % 100);
    touchgfx::Unicode::snprintf(buf4, BUF_SIZE, "%d", rand() % 100);
    touchgfx::Unicode::snprintf(buf5, BUF_SIZE, "%d", rand() % 100);
    touchgfx::Unicode::snprintf(buf6, BUF_SIZE, "%d", rand() % 100);
    touchgfx::Unicode::snprintf(buf7, BUF_SIZE, "%d", rand() % 100);

    textArea1.setWildcard(buf1);
    textArea3.setWildcard(buf3);
    textArea4.setWildcard(buf4);
    textArea5.setWildcard(buf5);
    textArea6.setWildcard(buf6);
    textArea7.setWildcard(buf7);

    textArea1.invalidate();
    textArea3.invalidate();
    textArea4.invalidate();
    textArea5.invalidate();
    textArea6.invalidate();
    textArea7.invalidate();
}

void Studio_GoldView::tearDownScreen()
{
    Studio_GoldViewBase::tearDownScreen();
}

void Studio_GoldView::flexButtonClicked(const touchgfx::AbstractButtonContainer& src)
{
    application().gotoBluetooth_2ScreenNoTransition();
}

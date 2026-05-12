#include <gui/bt_devices_screen/BT_DevicesView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Unicode.hpp>

BT_DevicesView::BT_DevicesView()
{

}

void BT_DevicesView::setupScreen()
{
    BT_DevicesViewBase::setupScreen();
    touchgfx::Unicode::strncpy(textArea2Buffer, "Namith's Iphone", TEXTAREA2_SIZE);
    textArea2.setWildcard(textArea2Buffer);
    textArea2.invalidate();
}

void BT_DevicesView::tearDownScreen()
{
    BT_DevicesViewBase::tearDownScreen();
}

#include <gui/bluetooth_2_screen/Bluetooth_2View.hpp>

Bluetooth_2View::Bluetooth_2View()
{

}

void Bluetooth_2View::setupScreen()
{
    Bluetooth_2ViewBase::setupScreen();
    updateBluetoothWidgetsAlpha();
}

void Bluetooth_2View::tearDownScreen()
{
    Bluetooth_2ViewBase::tearDownScreen();
}

void Bluetooth_2View::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        if (image2.isTouchable() &&
            x >= image2.getX() && x < image2.getX() + image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + image2.getHeight())
        {
            application().gotoStudio_GoldScreenNoTransition();
            return;
        }

        if (x >= image4.getX() && x < image4.getX() + image4.getWidth() &&
            y >= image4.getY() && y < image4.getY() + image4.getHeight())
        {
            touchgfx::Rect area(image4.getX(), image4.getY(), image4.getWidth(), image4.getHeight());
            image4.setVisible(!image4.isVisible());
            invalidateRect(area);
            updateBluetoothWidgetsAlpha();
            return;
        }

        if (image5.isTouchable() &&
            x >= image5.getX() && x < image5.getX() + image5.getWidth() &&
            y >= image5.getY() && y < image5.getY() + image5.getHeight())
        {
            application().gotoBT_DevicesScreenNoTransition();
            return;
        }
    }
    Bluetooth_2ViewBase::handleClickEvent(event);
}

void Bluetooth_2View::updateBluetoothWidgetsAlpha()
{
    bool btOn = image4.isVisible();
    uint8_t alpha = btOn ? 255 : 70;
    image8.setAlpha(alpha);
    image9.setAlpha(alpha);
    image10.setAlpha(alpha);
    textArea1.setAlpha(alpha);
    textArea2.setAlpha(alpha);
    textArea3.setAlpha(alpha);
    image2.setTouchable(btOn);
    image5.setTouchable(btOn);
    image8.setTouchable(btOn);
    image9.setTouchable(btOn);
    image10.setTouchable(btOn);
    textArea1.setTouchable(btOn);
    textArea2.setTouchable(btOn);
    textArea3.setTouchable(btOn);
    image8.invalidate();
    image9.invalidate();
    image10.invalidate();
    textArea1.invalidate();
    textArea2.invalidate();
    textArea3.invalidate();
}

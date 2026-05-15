#include <gui/bt_devices_screen/BT_DevicesView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Unicode.hpp>

BT_DevicesView::BT_DevicesView()
{
    popupVisible = false;
}

void BT_DevicesView::setupScreen()
{
    BT_DevicesViewBase::setupScreen();
    touchgfx::Unicode::strncpy(textArea2Buffer, "Namith's Iphone", TEXTAREA2_SIZE);
    textArea2.setWildcard(textArea2Buffer);
    textArea2.invalidate();

    // Hide popup elements initially
    image6.setVisible(false);
    button1.setVisible(false);
    button2.setVisible(false);
    image6.invalidate();
    button1.invalidate();
    button2.invalidate();
}

void BT_DevicesView::tearDownScreen()
{
    BT_DevicesViewBase::tearDownScreen();
}

void BT_DevicesView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        if (popupVisible)
        {
            // If popup is visible, check button clicks to close it
            if (x >= button1.getX() && x < button1.getX() + button1.getWidth() &&
                y >= button1.getY() && y < button1.getY() + button1.getHeight())
            {
                image6.setVisible(false);
                button1.setVisible(false);
                button2.setVisible(false);
                image6.invalidate();
                button1.invalidate();
                button2.invalidate();
                popupVisible = false;
                return;
            }

            if (x >= button2.getX() && x < button2.getX() + button2.getWidth() &&
                y >= button2.getY() && y < button2.getY() + button2.getHeight())
            {
                image6.setVisible(false);
                button1.setVisible(false);
                button2.setVisible(false);
                image6.invalidate();
                button1.invalidate();
                button2.invalidate();
                popupVisible = false;
                return;
            }
            return; // Block other touches while popup is open
        }

        // Show popup when image3 is clicked
        if (x >= image3.getX() && x < image3.getX() + image3.getWidth() &&
            y >= image3.getY() && y < image3.getY() + image3.getHeight())
        {
            image6.setVisible(true);
            button1.setVisible(true);
            button2.setVisible(true);
            image6.invalidate();
            button1.invalidate();
            button2.invalidate();
            popupVisible = true;
            return;
        }
    }
    BT_DevicesViewBase::handleClickEvent(event);
}

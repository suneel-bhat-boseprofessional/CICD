#include <gui/bt_settings_screen/BT_SettingsView.hpp>

int BT_SettingsView::savedSelection = 0;

BT_SettingsView::BT_SettingsView()
{
    popupVisible = false;
    popup2Visible = false;
}

void BT_SettingsView::setupScreen()
{
    BT_SettingsViewBase::setupScreen();
    if (savedSelection == 0)
    {
        image1.setVisible(true);
        image2.setVisible(false);
    }
    else
    {
        image1.setVisible(false);
        image2.setVisible(true);
    }
    image1.invalidate();
    image2.invalidate();

    // Hide popup1 widgets (image2 popup)
    image4.setVisible(false);
    textArea4.setVisible(false);
    button1.setVisible(false);
    button2.setVisible(false);
    textArea8.setVisible(false);
    textArea9.setVisible(false);
    image4.invalidate();
    textArea4.invalidate();
    button1.invalidate();
    button2.invalidate();
    popupVisible = false;

    // Hide popup2 widgets (image1 popup)
    textArea5.setVisible(false);
    textArea6.setVisible(false);
    textArea7.setVisible(false);
    button3.setVisible(false);
    button4.setVisible(false);
    textArea5.invalidate();
    textArea6.invalidate();
    textArea7.invalidate();
    button3.invalidate();
    button4.invalidate();
    popup2Visible = false;
}

void BT_SettingsView::tearDownScreen()
{
    BT_SettingsViewBase::tearDownScreen();
}

void BT_SettingsView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        if (popupVisible)
        {
            // Close popup1 on button1 or button2 click
            if (x >= button1.getX() && x < button1.getX() + button1.getWidth() &&
                y >= button1.getY() && y < button1.getY() + button1.getHeight())
            {
                image4.setVisible(false);
                textArea4.setVisible(false);
                button1.setVisible(false);
                button2.setVisible(false);
                textArea8.setVisible(false);
                textArea9.setVisible(false);
                image4.invalidate();
                textArea4.invalidate();
                button1.invalidate();
                button2.invalidate();
                popupVisible = false;
                return;
            }

            if (x >= button2.getX() && x < button2.getX() + button2.getWidth() &&
                y >= button2.getY() && y < button2.getY() + button2.getHeight())
            {
                image4.setVisible(false);
                textArea4.setVisible(false);
                button1.setVisible(false);
                button2.setVisible(false);
                textArea8.setVisible(false);
                textArea9.setVisible(false);
                image4.invalidate();
                textArea4.invalidate();
                button1.invalidate();
                button2.invalidate();
                popupVisible = false;
                return;
            }
            return; // Block other touches while popup is open
        }

        if (popup2Visible)
        {
            // Close popup2 on button3 or button4 click
            if (x >= button3.getX() && x < button3.getX() + button3.getWidth() &&
                y >= button3.getY() && y < button3.getY() + button3.getHeight())
            {
                image4.setVisible(false);
                textArea5.setVisible(false);
                textArea6.setVisible(false);
                textArea7.setVisible(false);
                button3.setVisible(false);
                button4.setVisible(false);
                image4.invalidate();
                textArea5.invalidate();
                textArea6.invalidate();
                textArea7.invalidate();
                button3.invalidate();
                button4.invalidate();
                popup2Visible = false;
                return;
            }

            if (x >= button4.getX() && x < button4.getX() + button4.getWidth() &&
                y >= button4.getY() && y < button4.getY() + button4.getHeight())
            {
                image4.setVisible(false);
                textArea5.setVisible(false);
                textArea6.setVisible(false);
                textArea7.setVisible(false);
                button3.setVisible(false);
                button4.setVisible(false);
                image4.invalidate();
                textArea5.invalidate();
                textArea6.invalidate();
                textArea7.invalidate();
                button3.invalidate();
                button4.invalidate();
                popup2Visible = false;
                return;
            }
            return; // Block other touches while popup2 is open
        }

        // Automatic Pairing area (image1 region) -> show popup2
        if (x >= image1.getX() && x < image1.getX() + image1.getWidth() &&
            y >= image1.getY() && y < image1.getY() + image1.getHeight())
        {
            savedSelection = 0;
            image1.setVisible(true);
            image2.setVisible(false);
            image1.invalidate();
            image2.invalidate();

            image4.setVisible(true);
            textArea5.setVisible(true);
            textArea6.setVisible(true);
            textArea7.setVisible(true);
            button3.setVisible(true);
            button4.setVisible(true);
            image4.invalidate();
            textArea5.invalidate();
            textArea6.invalidate();
            textArea7.invalidate();
            button3.invalidate();
            button4.invalidate();
            popup2Visible = true;
            return;
        }

        // Forget All area (image2 region) -> show popup
        if (x >= image2.getX() && x < image2.getX() + image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + image2.getHeight())
        {
            savedSelection = 1;
            image2.setVisible(true);
            image1.setVisible(false);
            image1.invalidate();
            image2.invalidate();

            image4.setVisible(true);
            textArea4.setVisible(true);
            button1.setVisible(true);
            button2.setVisible(true);
            textArea8.setVisible(true);
            textArea9.setVisible(true);
            image4.invalidate();
            textArea4.invalidate();
            button1.invalidate();
            button2.invalidate();
            textArea8.invalidate();
            textArea9.invalidate();
            popupVisible = true;
            return;
        }
    }
    BT_SettingsViewBase::handleClickEvent(event);
}

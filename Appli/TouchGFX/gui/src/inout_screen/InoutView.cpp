#include <gui/inout_screen/InoutView.hpp>

InoutView::InoutView()
{

}

void InoutView::setupScreen()
{
    InoutViewBase::setupScreen();
}

void InoutView::tearDownScreen()
{
    InoutViewBase::tearDownScreen();
}

void InoutView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        if (x >= image1.getX() && x < image1.getX() + image1.getWidth() &&
            y >= image1.getY() && y < image1.getY() + image1.getHeight())
        {
            application().gotoGPIOScreenNoTransition();
            return;
        }

        if (x >= image2.getX() && x < image2.getX() + image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + image2.getHeight())
        {
            application().gotoInScreenNoTransition();
            return;
        }

        if (x >= image3.getX() && x < image3.getX() + image3.getWidth() &&
            y >= image3.getY() && y < image3.getY() + image3.getHeight())
        {
            application().gotoOutScreenNoTransition();
            return;
        }
    }
    InoutViewBase::handleClickEvent(event);
}

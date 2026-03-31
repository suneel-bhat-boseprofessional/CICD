#include <gui/home_screen/homeView.hpp>

homeView::homeView() :
    itemSelectedCallback(this, &homeView::itemSelected),
    scrollOccurred(false)
{
}

void homeView::setupScreen()
{
    homeViewBase::setupScreen();
    scrollOccurred = false;
}

void homeView::tearDownScreen()
{
    homeViewBase::tearDownScreen();
}

void homeView::scrollList1UpdateItem(CustomContainer1& item, int16_t itemIndex)
{
    item.setListElements(itemIndex);
    item.setAction(itemSelectedCallback);
}

void homeView::itemSelected(int index)
{
    if(scrollOccurred)
    {
        scrollOccurred = false;
        return;
    }

    if(index == 0)
    {
        application().gotozoneScreenNoTransition();
    }
}

void homeView::handleDragEvent(const touchgfx::DragEvent& event)
{
    scrollOccurred = true;
    scrollList1.handleDragEvent(event);
}

void homeView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    scrollOccurred = true;
    scrollList1.handleGestureEvent(event);
}

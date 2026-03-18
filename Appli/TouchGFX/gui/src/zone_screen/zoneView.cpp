#include <gui/zone_screen/zoneView.hpp>
#include <gui/model/Model.hpp>

zoneView::zoneView() :
    zoneSelectedCallback(this, &zoneView::zoneSelected),
    scrollOccurred(false)
{
}

void zoneView::setupScreen()
{
    zoneViewBase::setupScreen();
    scrollOccurred = false;

    int containers = (zoneCount + 3) / 4;

    scrollList1.setNumberOfItems(containers);
    scrollList1.initialize();

    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1.itemChanged(i);
    }

    scrollList1.invalidate();
}

void zoneView::tearDownScreen()
{
    zoneViewBase::tearDownScreen();
}

void zoneView::scrollList1UpdateItem(CustomContainer2& item, int16_t itemIndex)
{
    item.setListElements(itemIndex);
    item.setAction(zoneSelectedCallback);
}

void zoneView::zoneSelected(int index)
{
    if(scrollOccurred)
    {
        scrollOccurred = false;
        return;
    }

    presenter->setSelectedZone(index);
    application().gotozone2ScreenNoTransition();
}

void zoneView::zoneNamesUpdated()
{
    int containers = (zoneCount + 3) / 4;
    scrollList1.setNumberOfItems(containers);
    scrollList1.initialize();

    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1.itemChanged(i);
    }

    scrollList1.invalidate();
}

void zoneView::handleDragEvent(const touchgfx::DragEvent& event)
{
    scrollOccurred = true;
    scrollList1.handleDragEvent(event);
}

void zoneView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    scrollOccurred = true;
    scrollList1.handleGestureEvent(event);
}

#include <gui/zone_screen/zoneView.hpp>
#include <gui/model/Model.hpp>

zoneView::zoneView() :
    zoneSelectedCallback(this, &zoneView::zoneSelected),
    scrollOccurred(false),
    scrollPerformanceMode(false),
    scrollSettleTicks(0)
{
}

void zoneView::setupScreen()
{
    zoneViewBase::setupScreen();
    scrollOccurred = false;
    scrollPerformanceMode = false;
    scrollSettleTicks = 0;
    scrollList1.setSwipeAcceleration(5);
    scrollList1.setDragAcceleration(4);
    scrollList1.setOvershootPercentage(20);

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
    scrollList1.setSwipeAcceleration(5);
    scrollList1.setDragAcceleration(4);
    scrollList1.setOvershootPercentage(20);

    int containers = (zoneCount + 3) / 4;
    scrollList1.setNumberOfItems(containers);
    scrollList1.initialize();

    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1.itemChanged(i);
    }

    scrollList1.invalidate();
}

void zoneView::setScrollPerformanceMode(bool enabled)
{
    if(scrollPerformanceMode == enabled)
    {
        return;
    }

    scrollPerformanceMode = enabled;

    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1ListItems[i].setReducedRenderingMode(enabled);
    }
}

void zoneView::handleTickEvent()
{
    if(scrollPerformanceMode && scrollSettleTicks > 0)
    {
        scrollSettleTicks--;
        if(scrollSettleTicks == 0)
        {
            setScrollPerformanceMode(false);
        }
    }

    zoneViewBase::handleTickEvent();
}

void zoneView::handleDragEvent(const touchgfx::DragEvent& event)
{
    scrollOccurred = true;
    if(scrollPerformanceMode)
    {
        setScrollPerformanceMode(false);
    }
    scrollSettleTicks = 0;

    scrollList1.handleDragEvent(event);
}

void zoneView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    scrollOccurred = true;

    if(scrollPerformanceMode)
    {
        setScrollPerformanceMode(false);
    }
    scrollSettleTicks = 0;

    scrollList1.handleGestureEvent(event);
}

void zoneView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if(event.getType() == touchgfx::ClickEvent::RELEASED && scrollOccurred)
    {
        setScrollPerformanceMode(true);
        scrollSettleTicks = 6;
    }

    zoneViewBase::handleClickEvent(event);
}

void zoneView::goToLaunchScreen()
{
    application().gotoScreen1ScreenNoTransition();
}

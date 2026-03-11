#include <gui/zone_screen/zoneView.hpp>

zoneView::zoneView() :
    zoneSelectedCallback(this, &zoneView::zoneSelected)
{
}

void zoneView::setupScreen()
{
    zoneViewBase::setupScreen();

    scrollList1.setNumberOfItems(4);

    scrollList1.setItemSelectedCallback(zoneSelectedCallback);
}

void zoneView::tearDownScreen()
{
    zoneViewBase::tearDownScreen();
}

void zoneView::scrollList1UpdateItem(CustomContainer2& item, int16_t itemIndex)
{
    item.setListElements(itemIndex);
}

void zoneView::zoneNamesUpdated()
{
    // Force visible list items to refresh immediately on the current screen.
    for (int i = 0; i < 4; i++)
    {
        scrollList1.itemChanged(i);
    }
    scrollList1.initialize();
    scrollList1.invalidate();
}

void zoneView::zoneSelected(int16_t index)
{
    presenter->setSelectedZone(index);
    application().gotozone2ScreenNoTransition();
}

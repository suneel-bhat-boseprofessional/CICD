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

void zoneView::zoneSelected(int16_t index)
{
    presenter->setSelectedZone(index);
    application().gotozone2ScreenNoTransition();
}

#include <gui/zone_screen/zoneView.hpp>

extern int zoneCount;

zoneView::zoneView() :
    zoneSelectedCallback(this, &zoneView::zoneSelected)
{
}

void zoneView::setupScreen()
{
    zoneViewBase::setupScreen();

    int containers = (zoneCount + 3) / 4;

    scrollList1.setNumberOfItems(containers);

    scrollList1.invalidate();

    scrollList1.setPosition(scrollList1.getX(),
                            scrollList1.getY(),
                            scrollList1.getWidth(),
                            scrollList1.getHeight());

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

void zoneView::zoneNamesUpdated()
{
    scrollList1.invalidate();
}

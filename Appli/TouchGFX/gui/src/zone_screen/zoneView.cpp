#include <gui/zone_screen/zoneView.hpp>
#include <gui/model/Model.hpp>

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
    presenter->setSelectedZone(index);
    application().gotozone2ScreenNoTransition();
}

void zoneView::zoneNamesUpdated()
{
    scrollList1.invalidate();
}

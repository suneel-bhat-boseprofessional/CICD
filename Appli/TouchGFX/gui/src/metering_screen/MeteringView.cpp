#include <gui/metering_screen/MeteringView.hpp>
#include <gui/containers/CustomContainer5.hpp>

MeteringView::MeteringView()
    : currentSourceCount(0),
      modelPtr(nullptr)
{
}

void MeteringView::setupScreen()
{
    MeteringViewBase::setupScreen();

    // Initialize all drawables first — this calls CustomContainer5::initialize()
    // which registers each one as a timer widget for VU animation.
    for (int16_t i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
        scrollList1ListItems[i].initialize();

    // Set 1 item minimum so the list is not empty before presenter updates it.
    // Presenter::activate() calls updateSourceConfig() with the real count
    // immediately after setupScreen() returns.
    scrollList1.setNumberOfItems(1);
    scrollList1.invalidate();
}

void MeteringView::tearDownScreen()
{
    MeteringViewBase::tearDownScreen();
}

void MeteringView::updateSourceConfig(int totalZones)
{
    currentSourceCount = totalZones;

    int totalItems = (totalZones + 3) / 4;
    if (totalItems < 1) totalItems = 1;

    scrollList1.setNumberOfItems(totalItems);

    // Force every visible drawable to refresh with the new zone data
    for (int16_t i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
        scrollList1.itemChanged(i);

    scrollList1.invalidate();
}

void MeteringView::scrollList1UpdateItem(CustomContainer5& item, int16_t itemIndex)
{
    item.setListElements(itemIndex, currentSourceCount, modelPtr);
}

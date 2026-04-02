#include <gui/source_select_screen/Source_SelectView.hpp>

extern "C" void Protocol_SendSetSource(int zone, int index);

Source_SelectView::Source_SelectView() :
    itemSelectedCb(this, &Source_SelectView::itemSelectedHandler)
{
}

void Source_SelectView::setupScreen()
{
    Source_SelectViewBase::setupScreen();

    int count = presenter->getSourceCount();
    if (count < 1) count = 1;
    scrollList1.setNumberOfItems(count);
    scrollList1.setItemSelectedCallback(itemSelectedCb);

    // Keep selected source in view when entering this screen.
    int selected = presenter->getSelectedSource();
    if (selected >= 0 && selected < count)
    {
        scrollList1.animateToItem(selected, 0);
    }

    scrollList1.invalidate();
}

void Source_SelectView::tearDownScreen()
{
    Source_SelectViewBase::tearDownScreen();
}

void Source_SelectView::scrollList1UpdateItem(CustomContainer3& item, int16_t itemIndex)
{
    const char* name = presenter->getSourceName(itemIndex);
    item.setSourceName(name);
    item.setItemIndex(itemIndex);
    item.setSelected(itemIndex == presenter->getSelectedSource());
}

void Source_SelectView::sourcesUpdated()
{
    int count = presenter->getSourceCount();
    if (count < 1) count = 1;
    scrollList1.setNumberOfItems(count);

    int selected = presenter->getSelectedSource();
    if (selected >= 0 && selected < count)
    {
        scrollList1.animateToItem(selected, 0);
    }

    scrollList1.invalidate();
}

void Source_SelectView::itemSelectedHandler(int16_t itemIndex)
{
    int zone = presenter->getSelectedZone();
    presenter->setSelectedSource(itemIndex);
    Protocol_SendSetSource(zone, itemIndex);

    // Force immediate highlight update for currently visible rows.
    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        bool selected = (scrollList1ListItems[i].getItemIndex() == itemIndex);
        scrollList1ListItems[i].setSelected(selected);
        scrollList1.itemChanged(i);
    }

    // Keep tapped selection centered/visible.
    scrollList1.animateToItem(itemIndex, 6);

    scrollList1.invalidate();
}

void Source_SelectView::goToLaunchScreen()
{
    application().gotolaunchScreenNoTransition();
}

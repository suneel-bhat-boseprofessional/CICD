#include <gui/source_select_screen/Source_SelectView.hpp>

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
    scrollList1.invalidate();
}

void Source_SelectView::itemSelectedHandler(int16_t itemIndex)
{
    presenter->setSelectedSource(itemIndex);
    application().gotozone2ScreenNoTransition();
}

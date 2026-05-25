#include <gui/device_information_screen/Device_InformationView.hpp>
#include <touchgfx/containers/scrollers/ScrollBase.hpp>

int32_t Device_InformationView::savedScrollOffset = 0;

// Trick: derive from ScrollList to expose protected getOffset/setOffset via
// pointer-to-member-function. Once formed in the derived class scope, the
// pointer can be invoked on any ScrollList instance.
namespace {
struct ScrollListAccess : public touchgfx::ScrollList
{
    static int32_t (touchgfx::ScrollBase::* const getOffsetMemPtr)() const;
    static void (touchgfx::ScrollBase::* const setOffsetMemPtr)(int32_t);
};
int32_t (touchgfx::ScrollBase::* const ScrollListAccess::getOffsetMemPtr)() const =
    &ScrollListAccess::getOffset;
void (touchgfx::ScrollBase::* const ScrollListAccess::setOffsetMemPtr)(int32_t) =
    &ScrollListAccess::setOffset;
}

Device_InformationView::Device_InformationView()
    : pendingScrollRestore(false)
{
}

void Device_InformationView::setupScreen()
{
    Device_InformationViewBase::setupScreen();
    scrollList1.setNumberOfItems(2);
    pendingScrollRestore = (savedScrollOffset != 0);
}

void Device_InformationView::tearDownScreen()
{
    savedScrollOffset = (scrollList1.*ScrollListAccess::getOffsetMemPtr)();
    Device_InformationViewBase::tearDownScreen();
}

void Device_InformationView::handleTickEvent()
{
    if (pendingScrollRestore)
    {
        pendingScrollRestore = false;
        (scrollList1.*ScrollListAccess::setOffsetMemPtr)(savedScrollOffset);
        scrollList1.invalidate();
    }
    Device_InformationViewBase::handleTickEvent();
}

void Device_InformationView::scrollList1UpdateItem(CustomContainer6& item, int16_t itemIndex)
{
    if (itemIndex >= 1)
    {
        item.hideContent();
    }
    else
    {
        item.showContent();
    }
    item.invalidate();
}

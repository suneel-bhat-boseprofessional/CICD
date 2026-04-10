#include <gui/home_screen/homeView.hpp>

const int homeView::PAGE_SIZES[2] = { 4, 3 };
const int homeView::PAGE_OFFSETS[2] = { 0, 4 };

homeView::homeView() :
    itemSelectedCallback(this, &homeView::itemSelected),
    currentPage(0)
{
}

void homeView::setupScreen()
{
    homeViewBase::setupScreen();
    currentPage = 0;
    goToPage(0);
}

void homeView::tearDownScreen()
{
    homeViewBase::tearDownScreen();
}

void homeView::scrollList1UpdateItem(CustomContainer1& item, int16_t itemIndex)
{
    // Map local page index to global item index
    int globalIndex = PAGE_OFFSETS[currentPage] + itemIndex;
    item.setListElements(globalIndex);
    item.setAction(itemSelectedCallback);
}

void homeView::itemSelected(int index)
{
    // index is global item index from setListElements
    if(index == 0)
    {
        application().gotozoneScreenNoTransition();
    }
    else if(index == 3)
    {
        application().gotoSettingsScreenNoTransition();
    }
}

void homeView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        // Check if left arrow (image1) was tapped
        if (x >= image1.getX() && x < image1.getX() + image1.getWidth() &&
            y >= image1.getY() && y < image1.getY() + image1.getHeight())
        {
            if (currentPage > 0)
            {
                goToPage(currentPage - 1);
            }
            return;
        }

        // Check if right arrow (image2) was tapped
        if (x >= image2.getX() && x < image2.getX() + image2.getWidth() &&
            y >= image2.getY() && y < image2.getY() + image2.getHeight())
        {
            if (currentPage < TOTAL_PAGES - 1)
            {
                goToPage(currentPage + 1);
            }
            return;
        }
    }

    // Pass through to base for scroll list item clicks
    homeViewBase::handleClickEvent(event);
}

void homeView::handleDragEvent(const touchgfx::DragEvent& event)
{
    // Block free drag to prevent mid-page stops.
    // Swipe gesture still fires via handleGestureEvent.
}

void homeView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    // Convert swipe into page flip
    if (event.getType() == touchgfx::GestureEvent::SWIPE_HORIZONTAL)
    {
        if (event.getVelocity() < 0 && currentPage < TOTAL_PAGES - 1)
        {
            goToPage(currentPage + 1); // swipe left = next page
        }
        else if (event.getVelocity() > 0 && currentPage > 0)
        {
            goToPage(currentPage - 1); // swipe right = prev page
        }
    }
}

void homeView::goToPage(int page)
{
    currentPage = page;
    scrollList1.setNumberOfItems(PAGE_SIZES[page]);
    scrollList1.initialize();
    for (int i = 0; i < scrollList1ListItems.getNumberOfDrawables(); i++)
    {
        scrollList1ListItems[i].initialize();
    }
    scrollList1.invalidate();
    updateArrows();
}

void homeView::updateArrows()
{
    // Grey out inactive arrows (alpha 60), full opacity for active (alpha 255)
    if (currentPage <= 0)
    {
        image1.setAlpha(60);
    }
    else
    {
        image1.setAlpha(255);
    }
    image1.invalidate();

    if (currentPage >= TOTAL_PAGES - 1)
    {
        image2.setAlpha(60);
    }
    else
    {
        image2.setAlpha(255);
    }
    image2.invalidate();
}

void homeView::goToLaunchScreen()
{
    application().gotolaunchScreenNoTransition();
}

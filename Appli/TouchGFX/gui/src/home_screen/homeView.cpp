#include <gui/home_screen/homeView.hpp>

const int homeView::PAGE_SIZES[2] = { 4, 3 };
const int homeView::PAGE_OFFSETS[2] = { 0, 4 };
int homeView::savedPage = 0;

homeView::homeView() :
    itemSelectedCallback(this, &homeView::itemSelected),
    currentPage(0),
    suppressNavigation(false),
    animating(false),
    animFrame(0),
    animDirection(0),
    targetPage(0)
{
}

void homeView::setupScreen()
{
    homeViewBase::setupScreen();
    currentPage = savedPage;
    goToPage(savedPage);
}

void homeView::tearDownScreen()
{
    savedPage = currentPage;
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
    if (suppressNavigation)
    {
        suppressNavigation = false;
        return;
    }

    // index is global item index from setListElements
    if(index == 0)
    {
        application().gotozoneScreenNoTransition();
    }
    else if(index == 1)
    {
        application().gotoInoutScreenNoTransition();
    }
    else if(index == 2)
    {
        application().gotoMeteringScreenNoTransition();
    }
    else if(index == 3)
    {
        application().gotoSettingsScreenNoTransition();
    }
    else if(index == 4)
    {
        application().gotoSetupScreenNoTransition();
    }
    else if(index == 5)
    {
        application().gotoNotificationsScreenNoTransition();
    }
    else if(index == 6)
    {
        application().gotoBluetooth_2ScreenNoTransition();
    }
}

void homeView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if (event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        suppressNavigation = false;
    }

    if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        int16_t x = event.getX();
        int16_t y = event.getY();

        // Check if left arrow area (flexButton1) was tapped
        if (x >= flexButton1.getX() && x < flexButton1.getX() + flexButton1.getWidth() &&
            y >= flexButton1.getY() && y < flexButton1.getY() + flexButton1.getHeight())
        {
            if (currentPage > 0 && !animating)
            {
                animateToPage(currentPage - 1);
            }
            return;
        }

        // Check if right arrow area (flexButton2) was tapped
        if (x >= flexButton2.getX() && x < flexButton2.getX() + flexButton2.getWidth() &&
            y >= flexButton2.getY() && y < flexButton2.getY() + flexButton2.getHeight())
        {
            if (currentPage < TOTAL_PAGES - 1 && !animating)
            {
                animateToPage(currentPage + 1);
            }
            return;
        }
    }

    // Pass through to base for scroll list item clicks
    homeViewBase::handleClickEvent(event);
}

void homeView::handleDragEvent(const touchgfx::DragEvent& event)
{
    // Forward to base so containers can detect drag and suppress accidental clicks.
    // ScrollList free-scroll is blocked by the gesture handler doing page flips instead.
    homeViewBase::handleDragEvent(event);
}

void homeView::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    // Convert swipe into page flip with animation
    if (event.getType() == touchgfx::GestureEvent::SWIPE_HORIZONTAL && !animating)
    {
        suppressNavigation = true;

        if (event.getVelocity() < 0 && currentPage < TOTAL_PAGES - 1)
        {
            animateToPage(currentPage + 1);
        }
        else if (event.getVelocity() > 0 && currentPage > 0)
        {
            animateToPage(currentPage - 1);
        }
    }
}

void homeView::animateToPage(int page)
{
    targetPage = page;
    animDirection = (page > currentPage) ? -1 : 1; // next=-1 (slide left), prev=+1 (slide right)
    animFrame = 0;
    animating = true;
}

void homeView::handleTickEvent()
{
    if (!animating)
        return;

    animFrame++;

    // Ease-out: fast start, slow finish
    float t = (float)animFrame / (float)ANIM_FRAMES;
    float eased = 1.0f - (1.0f - t) * (1.0f - t); // quadratic ease-out
    int16_t offset = (int16_t)(eased * SLIDE_WIDTH);

    // Slide old page out
    scrollList1.moveTo(LIST_X + (animDirection * offset), scrollList1.getY());
    scrollList1.invalidate();

    if (animFrame >= ANIM_FRAMES)
    {
        // Animation done — swap to new page
        animating = false;
        goToPage(targetPage);
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
    scrollList1.moveTo(LIST_X, scrollList1.getY());
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

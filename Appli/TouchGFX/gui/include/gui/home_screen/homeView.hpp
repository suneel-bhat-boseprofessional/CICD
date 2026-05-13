#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include <gui_generated/home_screen/homeViewBase.hpp>
#include <gui/home_screen/homePresenter.hpp>
#include <gui/containers/CustomContainer1.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/events/DragEvent.hpp>
#include <touchgfx/events/GestureEvent.hpp>
#include <touchgfx/events/ClickEvent.hpp>

class homeView : public homeViewBase
{
public:
    homeView();
    virtual ~homeView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer1& item, int16_t itemIndex);

    void itemSelected(int index);
    void goToLaunchScreen();

    virtual void handleTickEvent();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);

private:
    touchgfx::Callback<homeView, int> itemSelectedCallback;
    int currentPage;
    bool suppressNavigation;

    static const int PAGE_SIZES[2];
    static const int PAGE_OFFSETS[2];
    static const int TOTAL_ITEMS = 7;
    static const int TOTAL_PAGES = 2;
    static int savedPage;

    // Slide animation
    static const int16_t LIST_X = 25;
    static const int16_t SLIDE_WIDTH = 430;
    static const int ANIM_FRAMES = 10; // ~0.17s at 60fps
    bool animating;
    int animFrame;
    int animDirection; // -1 = slide left (next page), +1 = slide right (prev page)
    int targetPage;

    void goToPage(int page);
    void animateToPage(int page);
    void updateArrows();
};

#endif

#ifndef CUSTOMCONTAINER2_HPP
#define CUSTOMCONTAINER2_HPP

#include <gui_generated/containers/CustomContainer2Base.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/events/ClickEvent.hpp>

using namespace touchgfx;

class CustomContainer2 : public CustomContainer2Base
{
public:
    CustomContainer2();
    virtual ~CustomContainer2()
    {
        stopScrollTimer();
    }

    void setListElements(int item);
    void setAction(GenericCallback<int>& callback);
    void handleButtonPress(const touchgfx::AbstractButton& src);
    void refreshVolumes();
    void setReducedRenderingMode(bool enabled);

    virtual void handleTickEvent();
    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);

protected:
    int  itemIndex;
    GenericCallback<int>* action;
    bool isDragging;
    bool suppressNextClick;
    bool reducedRenderingMode;
    Unicode::UnicodeChar zoneName[4][20];
    Unicode::UnicodeChar volumeText[4][8];

    touchgfx::Callback<CustomContainer2,
        const touchgfx::AbstractButton&> myButtonCallback;

    // Marquee auto-scroll for zone names
    static const int NUM_SLOTS = 4;
    static const uint16_t SCROLL_PAUSE_TICKS = 90;
    static const uint8_t  SCROLL_TICK_DIVIDER = 2;
    static const int16_t  TEXT_GAP = 30;
    static const int16_t  VIEWPORT_HEIGHT = 22;

    static const int16_t VIEWPORT_WIDTHS[NUM_SLOTS];

    touchgfx::Container textClip[NUM_SLOTS];
    touchgfx::TextAreaWithOneWildcard textCopy[NUM_SLOTS];
    Unicode::UnicodeChar textCopyBuffer[NUM_SLOTS][20];

    bool scrollNeeded;
    bool slotScrolling[NUM_SLOTS];
    int16_t scrollOffset[NUM_SLOTS];
    int16_t loopWidth[NUM_SLOTS];
    uint16_t scrollPauseCount[NUM_SLOTS];
    uint8_t scrollTickDiv[NUM_SLOTS];
    enum ScrollState { PAUSE, SCROLLING };
    ScrollState scrollState[NUM_SLOTS];

    void startScrollTimer();
    void stopScrollTimer();
    void setupSlotScroll(int slot, touchgfx::TextAreaWithOneWildcard& textArea);
};

#endif

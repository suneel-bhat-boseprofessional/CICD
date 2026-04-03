#ifndef CUSTOMCONTAINER1_HPP
#define CUSTOMCONTAINER1_HPP

#include <gui_generated/containers/CustomContainer1Base.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class CustomContainer1 : public CustomContainer1Base
{
public:
    CustomContainer1();
    virtual ~CustomContainer1()
    {
        stopScrollTimer();
    }

    void setListElements(int item);
    void setAction(touchgfx::GenericCallback<int>& callback);

    virtual void function1();
    virtual void handleTickEvent();
    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);

private:
    int itemIndex;
    touchgfx::GenericCallback<int>* action;
    bool isDragging;
    bool suppressNextClick;

    touchgfx::Unicode::UnicodeChar textArea1Buffer[20];
    touchgfx::Unicode::UnicodeChar textCopyBuffer[20];

    // Our own button callback to replace the base class one
    touchgfx::Callback<CustomContainer1, const touchgfx::AbstractButton&> myButtonCallback;
    void myButtonCallbackHandler(const touchgfx::AbstractButton& src);

    // Marquee auto-scroll
    touchgfx::Container textClip;
    touchgfx::TextAreaWithOneWildcard textCopy;
    bool scrollNeeded;
    int16_t scrollOffset;
    int16_t loopWidth;
    uint16_t scrollPauseCount;
    uint8_t scrollTickDiv;
    enum ScrollState { PAUSE, SCROLLING };
    ScrollState scrollState;

    void startScrollTimer();
    void stopScrollTimer();

    static const uint16_t SCROLL_PAUSE_TICKS = 90;
    static const uint8_t SCROLL_TICK_DIVIDER = 2;
    static const int16_t TEXT_GAP = 30;
    static const int16_t VIEWPORT_WIDTH = 83;
    static const int16_t VIEWPORT_HEIGHT = 22;
};

#endif

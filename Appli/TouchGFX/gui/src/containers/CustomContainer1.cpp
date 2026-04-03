#include <gui/containers/CustomContainer1.hpp>
#include <images/BitmapDatabase.hpp>

CustomContainer1::CustomContainer1() :
    itemIndex(-1),
    action(0),
    isDragging(false),
    suppressNextClick(false),
    myButtonCallback(this, &CustomContainer1::myButtonCallbackHandler),
    scrollNeeded(false),
    scrollOffset(0),
    loopWidth(0),
    scrollPauseCount(0),
    scrollTickDiv(0),
    scrollState(PAUSE)
{
    button2.setAction(myButtonCallback);

    // Move textArea1 into a clipping container
    remove(textArea1);
    textClip.setPosition(textArea1.getX(), textArea1.getY(), VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
    textArea1.setXY(0, 0);
    textClip.add(textArea1);

    // Create a second copy for seamless looping
    textCopy.setColor(textArea1.getColor());
    textCopy.setLinespacing(0);
    textCopy.setTypedText(textArea1.getTypedText());
    textCopyBuffer[0] = 0;
    textCopy.setWildcard(textCopyBuffer);
    textCopy.setVisible(false);
    textClip.add(textCopy);

    add(textClip);
}

void CustomContainer1::setListElements(int item)
{
    itemIndex = item;

    static const char* names[] =
    {
        "ZONE",
        "IN/OUT",
        "METER",
        "SETTINGS",
        "BLUETOOTH",
        "NOTIFICATIONS",
        "SETUP"
    };

    switch(item)
    {
        case 0:
            image2.setBitmap(Bitmap(BITMAP_ZONE_ID));
            break;

        case 1:
            image2.setBitmap(Bitmap(BITMAP_INOUT_IMAGE_ID));
            break;

        case 2:
            image2.setBitmap(Bitmap(BITMAP_METERS_IMAGE_ID));
            break;

        case 3:
            image2.setBitmap(Bitmap(BITMAP_SETTINGS_IMAGE_ID));
            break;

        case 4:
            image2.setBitmap(Bitmap(BITMAP_BLUETOOTH_IMAGE_ID));
            break;

        case 5:
            image2.setBitmap(Bitmap(BITMAP_NOTIFICATIONS_IMAGE_ID));
            break;

        case 6:
            image2.setBitmap(Bitmap(BITMAP_SETUP_IMAGE_ID));
            break;
    }

    stopScrollTimer();

    Unicode::fromUTF8((const uint8_t*)names[item], textArea1Buffer, 20);
    textArea1.setWildcard(textArea1Buffer);

    // Measure single text width
    textArea1.setWidth(300);
    textArea1.resizeToCurrentText();
    int16_t singleWidth = textArea1.getWidth();

    // Reset position
    textArea1.setXY(0, 0);
    textArea1.setWidth(VIEWPORT_WIDTH);
    textArea1.setHeight(VIEWPORT_HEIGHT);
    textCopy.setVisible(false);
    scrollOffset = 0;

    if (singleWidth > VIEWPORT_WIDTH)
    {
        // Make textArea1 wide enough to show full text
        textArea1.setWidth(singleWidth + 4);

        // Set up the second copy at (singleWidth + gap) for seamless loop
        loopWidth = singleWidth + TEXT_GAP;
        Unicode::strncpy(textCopyBuffer, textArea1Buffer, 20);
        textCopy.setWildcard(textCopyBuffer);
        textCopy.setPosition(loopWidth, 0, singleWidth + 4, VIEWPORT_HEIGHT);
        textCopy.setVisible(true);

        scrollPauseCount = 0;
        scrollTickDiv = 0;
        scrollState = PAUSE;
        startScrollTimer();
    }

    button2.setTouchable(true);
    image2.invalidate();
    textClip.invalidate();
    invalidate();
}

void CustomContainer1::handleTickEvent()
{
    if (!scrollNeeded)
        return;

    switch (scrollState)
    {
        case PAUSE:
            if (++scrollPauseCount >= SCROLL_PAUSE_TICKS)
            {
                scrollState = SCROLLING;
                scrollPauseCount = 0;
                scrollTickDiv = 0;
            }
            break;

        case SCROLLING:
            if (++scrollTickDiv >= SCROLL_TICK_DIVIDER)
            {
                scrollTickDiv = 0;
                scrollOffset++;

                // Seamless loop: when scrolled by one full cycle, reset
                if (scrollOffset >= loopWidth)
                {
                    scrollOffset = 0;
                }

                textArea1.moveTo(-scrollOffset, 0);
                textCopy.moveTo(loopWidth - scrollOffset, 0);
                textClip.invalidate();
            }
            break;
    }
}

void CustomContainer1::startScrollTimer()
{
    scrollNeeded = true;
    touchgfx::Application::getInstance()->registerTimerWidget(this);
}

void CustomContainer1::stopScrollTimer()
{
    if (scrollNeeded)
    {
        touchgfx::Application::getInstance()->unregisterTimerWidget(this);
        scrollNeeded = false;
    }
}

void CustomContainer1::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer1::myButtonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if(suppressNextClick)
    {
        suppressNextClick = false;
        return;
    }

    if(!isDragging)
    {
        function1();
    }
}

void CustomContainer1::function1()
{
    if(action && action->isValid())
    {
        action->execute(itemIndex);
    }
}

void CustomContainer1::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if(event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        isDragging = false;
    }
    else if(event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        button2.setTouchable(true);
    }

    CustomContainer1Base::handleClickEvent(event);
}

void CustomContainer1::handleDragEvent(const touchgfx::DragEvent& event)
{
    if(!isDragging)
    {
        isDragging = true;
        suppressNextClick = true;
        button2.setTouchable(false);
    }

    if(parent)
    {
        parent->handleDragEvent(event);
    }
}

void CustomContainer1::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    if(parent)
    {
        parent->handleGestureEvent(event);
    }
}

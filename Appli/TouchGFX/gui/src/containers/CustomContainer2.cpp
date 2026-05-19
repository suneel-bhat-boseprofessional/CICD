#include <gui/containers/CustomContainer2.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Unicode.hpp>

// Viewport widths matching generated textArea1-4 widths: 87, 83, 89, 81
const int16_t CustomContainer2::VIEWPORT_WIDTHS[NUM_SLOTS] = { 87, 83, 89, 81 };

CustomContainer2::CustomContainer2() :
    itemIndex(-1),
    action(0),
    isDragging(false),
    suppressNextClick(false),
    reducedRenderingMode(false),
    myButtonCallback(this, &CustomContainer2::handleButtonPress),
    scrollNeeded(false)
{
    touchgfx::TextAreaWithOneWildcard* textAreas[NUM_SLOTS] = { &textArea1, &textArea2, &textArea3, &textArea4 };

    for (int i = 0; i < NUM_SLOTS; i++)
    {
        slotScrolling[i] = false;
        scrollOffset[i] = 0;
        loopWidth[i] = 0;
        scrollPauseCount[i] = 0;
        scrollTickDiv[i] = 0;
        scrollState[i] = PAUSE;
        textCopyBuffer[i][0] = 0;

        // Move textArea into a clipping container
        remove(*textAreas[i]);
        textClip[i].setPosition(textAreas[i]->getX(), textAreas[i]->getY(), VIEWPORT_WIDTHS[i], VIEWPORT_HEIGHT);
        textAreas[i]->setXY(0, 0);
        textClip[i].add(*textAreas[i]);

        // Create copy for seamless loop
        textCopy[i].setColor(textAreas[i]->getColor());
        textCopy[i].setLinespacing(0);
        textCopy[i].setTypedText(textAreas[i]->getTypedText());
        textCopy[i].setWildcard(textCopyBuffer[i]);
        textCopy[i].setVisible(false);
        textClip[i].add(textCopy[i]);

        add(textClip[i]);
    }

    textArea1.setWildcard(zoneName[0]);
    textArea2.setWildcard(zoneName[1]);
    textArea3.setWildcard(zoneName[2]);
    textArea4.setWildcard(zoneName[3]);

    textArea5.setWildcard(volumeText[0]);
    textArea6.setWildcard(volumeText[1]);
    textArea7.setWildcard(volumeText[2]);
    textArea8.setWildcard(volumeText[3]);

    button1.setAction(myButtonCallback);
    button2.setAction(myButtonCallback);
    button3.setAction(myButtonCallback);
    button4.setAction(myButtonCallback);
}

void CustomContainer2::setListElements(int item)
{
    itemIndex = item;
    int base  = itemIndex * 4;

    stopScrollTimer();

    // hide everything first
    button1.setVisible(false);
    button2.setVisible(false);
    button3.setVisible(false);
    button4.setVisible(false);

    button1.setTouchable(false);
    button2.setTouchable(false);
    button3.setTouchable(false);
    button4.setTouchable(false);

    textClip[0].setVisible(false);
    textClip[1].setVisible(false);
    textClip[2].setVisible(false);
    textClip[3].setVisible(false);

    textArea5.setVisible(false);
    textArea6.setVisible(false);
    textArea7.setVisible(false);
    textArea8.setVisible(false);

    circleProgress1.setVisible(false);
    circleProgress2.setVisible(false);
    circleProgress3.setVisible(false);
    circleProgress4.setVisible(false);

    image1.setVisible(false);
    image2.setVisible(false);
    image3.setVisible(false);
    image4.setVisible(false);

    touchgfx::TextAreaWithOneWildcard* textAreas[NUM_SLOTS] = { &textArea1, &textArea2, &textArea3, &textArea4 };

    // populate active slots
    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;

        if(zoneIndex < zoneCount)
        {
            const char* configuredName = 0;

            if(modelInstance != 0)
            {
                configuredName = modelInstance->getZoneName(zoneIndex);
            }

            if(configuredName != 0 && configuredName[0] != '\0')
            {
                Unicode::fromUTF8((const uint8_t*)configuredName, zoneName[i], 20);
            }
            else
            {
                Unicode::snprintf(zoneName[i], 20, "Zone %d", zoneIndex + 1);
            }

            int vol = (modelInstance != 0) ? modelInstance->getZoneVolume(zoneIndex) : 0;
            Unicode::snprintf(volumeText[i], 8, "%d", vol);

            bool muted = (modelInstance != 0) && modelInstance->getZoneMuted(zoneIndex);

            textClip[i].setVisible(true);
            setupSlotScroll(i, *textAreas[i]);

            if(i == 0)
            {
                button1.setVisible(true);
                button1.setTouchable(!isDragging);
                textArea5.setVisible(!muted);
                image1.setVisible(muted);
                circleProgress1.setVisible(!reducedRenderingMode);
                circleProgress1.setValue(vol);
            }
            else if(i == 1)
            {
                button2.setVisible(true);
                button2.setTouchable(!isDragging);
                textArea6.setVisible(!muted);
                image2.setVisible(muted);
                circleProgress2.setVisible(!reducedRenderingMode);
                circleProgress2.setValue(vol);
            }
            else if(i == 2)
            {
                button3.setVisible(true);
                button3.setTouchable(!isDragging);
                textArea7.setVisible(!muted);
                image3.setVisible(muted);
                circleProgress3.setVisible(!reducedRenderingMode);
                circleProgress3.setValue(vol);
            }
            else if(i == 3)
            {
                button4.setVisible(true);
                button4.setTouchable(!isDragging);
                textArea8.setVisible(!muted);
                image4.setVisible(muted);
                circleProgress4.setVisible(!reducedRenderingMode);
                circleProgress4.setValue(vol);
            }
        }
    }

    // Start scroll timer if any slot needs it
    for (int i = 0; i < NUM_SLOTS; i++)
    {
        if (slotScrolling[i])
        {
            startScrollTimer();
            break;
        }
    }

    invalidate();
}

void CustomContainer2::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer2::handleButtonPress(const touchgfx::AbstractButton& src)
{
    if(suppressNextClick)
    {
        suppressNextClick = false;
        return;
    }

    int zone = -1;

    if(&src == &button1)      zone = 0;
    else if(&src == &button2) zone = 1;
    else if(&src == &button3) zone = 2;
    else if(&src == &button4) zone = 3;

    if(zone == -1) return;

    int realZone = itemIndex * 4 + zone;

    if(realZone < 0 || realZone >= zoneCount) return;

    if(action && action->isValid())
    {
        action->execute(realZone);
    }
}

void CustomContainer2::refreshVolumes()
{
    if(itemIndex < 0 || modelInstance == 0) return;

    int base = itemIndex * 4;

    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;
        if(zoneIndex < zoneCount)
        {
            int  vol   = modelInstance->getZoneVolume(zoneIndex);
            bool muted = modelInstance->getZoneMuted(zoneIndex);

            Unicode::snprintf(volumeText[i], 8, "%d", vol);

            switch(i)
            {
                case 0:
                    circleProgress1.setValue(vol);
                    textArea5.setVisible(!muted);
                    image1.setVisible(muted);
                    break;
                case 1:
                    circleProgress2.setValue(vol);
                    textArea6.setVisible(!muted);
                    image2.setVisible(muted);
                    break;
                case 2:
                    circleProgress3.setValue(vol);
                    textArea7.setVisible(!muted);
                    image3.setVisible(muted);
                    break;
                case 3:
                    circleProgress4.setValue(vol);
                    textArea8.setVisible(!muted);
                    image4.setVisible(muted);
                    break;
            }
        }
    }

    invalidate();
}

void CustomContainer2::setReducedRenderingMode(bool enabled)
{
    if(reducedRenderingMode == enabled) return;

    reducedRenderingMode = enabled;

    circleProgress1.setVisible(!reducedRenderingMode && button1.isVisible());
    circleProgress2.setVisible(!reducedRenderingMode && button2.isVisible());
    circleProgress3.setVisible(!reducedRenderingMode && button3.isVisible());
    circleProgress4.setVisible(!reducedRenderingMode && button4.isVisible());

    invalidate();
}

void CustomContainer2::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if(event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        isDragging = false;
    }
    else if(event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        button1.setTouchable(button1.isVisible());
        button2.setTouchable(button2.isVisible());
        button3.setTouchable(button3.isVisible());
        button4.setTouchable(button4.isVisible());
    }

    CustomContainer2Base::handleClickEvent(event);
}

void CustomContainer2::handleDragEvent(const touchgfx::DragEvent& event)
{
    if(!isDragging)
    {
        isDragging        = true;
        suppressNextClick = true;

        button1.setTouchable(false);
        button2.setTouchable(false);
        button3.setTouchable(false);
        button4.setTouchable(false);
    }

    if(parent)
    {
        parent->handleDragEvent(event);
    }
}

void CustomContainer2::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    if(parent)
    {
        parent->handleGestureEvent(event);
    }
}

void CustomContainer2::setupSlotScroll(int slot, touchgfx::TextAreaWithOneWildcard& textArea)
{
    slotScrolling[slot] = false;
    scrollOffset[slot] = 0;
    scrollPauseCount[slot] = 0;
    scrollTickDiv[slot] = 0;
    scrollState[slot] = PAUSE;

    // Measure single text width
    textArea.setWidth(300);
    textArea.resizeToCurrentText();
    int16_t singleWidth = textArea.getWidth();

    // Reset position
    textArea.setXY(0, 0);
    textArea.setWidth(VIEWPORT_WIDTHS[slot]);
    textArea.setHeight(VIEWPORT_HEIGHT);
    textCopy[slot].setVisible(false);

    if (singleWidth > VIEWPORT_WIDTHS[slot])
    {
        textArea.setWidth(singleWidth + 4);

        loopWidth[slot] = singleWidth + TEXT_GAP;
        Unicode::strncpy(textCopyBuffer[slot], zoneName[slot], 20);
        textCopy[slot].setWildcard(textCopyBuffer[slot]);
        textCopy[slot].setPosition(loopWidth[slot], 0, singleWidth + 4, VIEWPORT_HEIGHT);
        textCopy[slot].setVisible(true);

        slotScrolling[slot] = true;
    }
}

void CustomContainer2::handleTickEvent()
{
    if (!scrollNeeded)
        return;

    for (int i = 0; i < NUM_SLOTS; i++)
    {
        if (!slotScrolling[i])
            continue;

        touchgfx::TextAreaWithOneWildcard* textAreas[NUM_SLOTS] = { &textArea1, &textArea2, &textArea3, &textArea4 };

        switch (scrollState[i])
        {
            case PAUSE:
                if (++scrollPauseCount[i] >= SCROLL_PAUSE_TICKS)
                {
                    scrollState[i] = SCROLLING;
                    scrollPauseCount[i] = 0;
                    scrollTickDiv[i] = 0;
                }
                break;

            case SCROLLING:
                if (++scrollTickDiv[i] >= SCROLL_TICK_DIVIDER)
                {
                    scrollTickDiv[i] = 0;
                    scrollOffset[i]++;

                    if (scrollOffset[i] >= loopWidth[i])
                    {
                        scrollOffset[i] = 0;
                    }

                    textAreas[i]->moveTo(-scrollOffset[i], 0);
                    textCopy[i].moveTo(loopWidth[i] - scrollOffset[i], 0);
                    textClip[i].invalidate();
                }
                break;
        }
    }
}

void CustomContainer2::startScrollTimer()
{
    if (!scrollNeeded)
    {
        scrollNeeded = true;
        touchgfx::Application::getInstance()->registerTimerWidget(this);
    }
}

void CustomContainer2::stopScrollTimer()
{
    if (scrollNeeded)
    {
        touchgfx::Application::getInstance()->unregisterTimerWidget(this);
        scrollNeeded = false;
    }
    for (int i = 0; i < NUM_SLOTS; i++)
    {
        slotScrolling[i] = false;
        scrollOffset[i] = 0;
    }
}

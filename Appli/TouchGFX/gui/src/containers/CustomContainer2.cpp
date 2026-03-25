#include <gui/containers/CustomContainer2.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Unicode.hpp>

CustomContainer2::CustomContainer2() :
    itemIndex(-1),
    action(0),
    isDragging(false),
    suppressNextClick(false),
    reducedRenderingMode(false),
    myButtonCallback(this, &CustomContainer2::handleButtonPress)
{
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
    int base = itemIndex * 4;

    // --- hide everything first -------------------------------------------

    button1.setVisible(false);
    button2.setVisible(false);
    button3.setVisible(false);
    button4.setVisible(false);

    button1.setTouchable(false);
    button2.setTouchable(false);
    button3.setTouchable(false);
    button4.setTouchable(false);

    textArea1.setVisible(false);
    textArea2.setVisible(false);
    textArea3.setVisible(false);
    textArea4.setVisible(false);

    textArea5.setVisible(false);
    textArea6.setVisible(false);
    textArea7.setVisible(false);
    textArea8.setVisible(false);

    // hide all circles before selectively showing active ones
    circleProgress1.setVisible(false);
    circleProgress2.setVisible(false);
    circleProgress3.setVisible(false);
    circleProgress4.setVisible(false);

    // --- populate active slots -------------------------------------------

    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;
        const char* configuredName = 0;

        if(zoneIndex < zoneCount)
        {
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

            if(i == 0)
            {
                textArea1.setVisible(true);
                button1.setVisible(true);
                button1.setTouchable(!isDragging);
                textArea5.setVisible(true);
                circleProgress1.setVisible(!reducedRenderingMode);
                circleProgress1.setValue(vol);
            }
            else if(i == 1)
            {
                textArea2.setVisible(true);
                button2.setVisible(true);
                button2.setTouchable(!isDragging);
                textArea6.setVisible(true);
                circleProgress2.setVisible(!reducedRenderingMode);
                circleProgress2.setValue(vol);
            }
            else if(i == 2)
            {
                textArea3.setVisible(true);
                button3.setVisible(true);
                button3.setTouchable(!isDragging);
                textArea7.setVisible(true);
                circleProgress3.setVisible(!reducedRenderingMode);
                circleProgress3.setValue(vol);
            }
            else if(i == 3)
            {
                textArea4.setVisible(true);
                button4.setVisible(true);
                button4.setTouchable(!isDragging);
                textArea8.setVisible(true);
                circleProgress4.setVisible(!reducedRenderingMode);
                circleProgress4.setValue(vol);
            }
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

    if(&src == &button1) zone = 0;
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
            int vol = modelInstance->getZoneVolume(zoneIndex);
            Unicode::snprintf(volumeText[i], 8, "%d", vol);

            switch(i)
            {
                case 0: circleProgress1.setValue(vol); break;
                case 1: circleProgress2.setValue(vol); break;
                case 2: circleProgress3.setValue(vol); break;
                case 3: circleProgress4.setValue(vol); break;
            }
        }
    }

    invalidate();
}

void CustomContainer2::setReducedRenderingMode(bool enabled)
{
    if(reducedRenderingMode == enabled)
    {
        return;
    }

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
        // Re-enable children after potential drag so next tap works normally.
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
        isDragging = true;
        suppressNextClick = true;

        // Let the list consume drag events instead of button children.
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

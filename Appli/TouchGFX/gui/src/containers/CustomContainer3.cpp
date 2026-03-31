#include <gui/containers/CustomContainer3.hpp>

CustomContainer3::CustomContainer3() :
    itemIndex(0),
    isDragging(false),
    suppressNextClick(false),
    buttonCallback(this, &CustomContainer3::buttonCallbackHandler),
    action(0)
{
    sourceNameBuffer[0] = 0;
}

void CustomContainer3::initialize()
{
    CustomContainer3Base::initialize();

    image2.setVisible(false);
    image2.invalidate();
}

void CustomContainer3::setSourceName(const char* name)
{
    if (name && name[0] != '\0')
    {
        touchgfx::Unicode::fromUTF8((const uint8_t*)name, sourceNameBuffer, 32);
    }
    else
    {
        touchgfx::Unicode::snprintf(sourceNameBuffer, 32, "---");
    }

    textArea1.setWildcard(sourceNameBuffer);
    textArea1.invalidate();
}

void CustomContainer3::setItemIndex(int16_t index)
{
    itemIndex = index;
}

int16_t CustomContainer3::getItemIndex() const
{
    return itemIndex;
}

void CustomContainer3::setSelected(bool selected)
{
    image2.setVisible(selected);
    image2.invalidate();
}

void CustomContainer3::setAction(touchgfx::GenericCallback<int16_t>& callback)
{
    action = &callback;
}

void CustomContainer3::buttonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if(suppressNextClick)
    {
        suppressNextClick = false;
        return;
    }

    if(!isDragging)
    {
        triggerAction();
    }
}

void CustomContainer3::triggerAction()
{
    if(action && action->isValid())
    {
        action->execute(itemIndex);
    }
}

void CustomContainer3::handleClickEvent(const touchgfx::ClickEvent& event)
{
    if(event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        isDragging = false;
    }
    else if(event.getType() == touchgfx::ClickEvent::RELEASED)
    {

    }

    CustomContainer3Base::handleClickEvent(event);
}

void CustomContainer3::handleDragEvent(const touchgfx::DragEvent& event)
{
    if(!isDragging)
    {
        isDragging = true;
        suppressNextClick = true;

    }

    if(parent)
    {
        parent->handleDragEvent(event);
    }
}

void CustomContainer3::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    if(parent)
    {
        parent->handleGestureEvent(event);
    }
}

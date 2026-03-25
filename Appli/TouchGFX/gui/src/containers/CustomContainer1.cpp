#include <gui/containers/CustomContainer1.hpp>
#include <images/BitmapDatabase.hpp>

CustomContainer1::CustomContainer1() :
    itemIndex(-1),
    action(0),
    isDragging(false),
    suppressNextClick(false),
    myButtonCallback(this, &CustomContainer1::myButtonCallbackHandler)
{
    button2.setAction(myButtonCallback);
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
        "BLUE..",
        "NOTIF..",
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

    Unicode::fromUTF8((const uint8_t*)names[item], textArea1Buffer, 20);
    textArea1.setWildcard(textArea1Buffer);
    button2.setTouchable(true);

    image2.invalidate();
    textArea1.invalidate();

    invalidate();
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

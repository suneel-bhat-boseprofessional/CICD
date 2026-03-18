#include <gui/containers/CustomContainer1.hpp>
#include <images/BitmapDatabase.hpp>

CustomContainer1::CustomContainer1() :
    itemIndex(-1),
    action(0),
    isDragging(false),
    myButtonCallback(this, &CustomContainer1::myButtonCallbackHandler),
    dummyCallback(this, &CustomContainer1::dummyCallbackHandler)
{
    // Replace base class button callback with our own from the start
    button1.setAction(myButtonCallback);
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
            button1.setBitmaps(Bitmap(BITMAP_ZONE_ID), Bitmap(BITMAP_ZONE_ID));
            break;

        case 1:
            button1.setBitmaps(Bitmap(BITMAP_INOUT_IMAGE_ID), Bitmap(BITMAP_INOUT_IMAGE_ID));
            break;

        case 2:
            button1.setBitmaps(Bitmap(BITMAP_METERS_IMAGE_ID), Bitmap(BITMAP_METERS_IMAGE_ID));
            break;

        case 3:
            button1.setBitmaps(Bitmap(BITMAP_SETTINGS_IMAGE_ID), Bitmap(BITMAP_SETTINGS_IMAGE_ID));
            break;

        case 4:
            button1.setBitmaps(Bitmap(BITMAP_BLUETOOTH_IMAGE_ID), Bitmap(BITMAP_BLUETOOTH_IMAGE_ID));
            break;

        case 5:
            button1.setBitmaps(Bitmap(BITMAP_NOTIFICATIONS_IMAGE_ID), Bitmap(BITMAP_NOTIFICATIONS_IMAGE_ID));
            break;

        case 6:
            button1.setBitmaps(Bitmap(BITMAP_SETUP_IMAGE_ID), Bitmap(BITMAP_SETUP_IMAGE_ID));
            break;
    }

    Unicode::fromUTF8((const uint8_t*)names[item], textArea1Buffer, 20);
    textArea1.setWildcard(textArea1Buffer);

    button1.invalidate();
    textArea1.invalidate();
}

void CustomContainer1::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer1::myButtonCallbackHandler(const touchgfx::AbstractButton& src)
{
    // This replaces buttonCallbackHandler from base — calls function1 only if not dragging
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
        button1.setAction(myButtonCallback);
    }

    CustomContainer1Base::handleClickEvent(event);
}

void CustomContainer1::handleDragEvent(const touchgfx::DragEvent& event)
{
    if(!isDragging)
    {
        isDragging = true;
        // Swap to dummy callback so button can never fire function1
        button1.setAction(dummyCallback);
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

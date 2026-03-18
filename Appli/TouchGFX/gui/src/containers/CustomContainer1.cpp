#include <gui/containers/CustomContainer1.hpp>
#include <images/BitmapDatabase.hpp>

CustomContainer1::CustomContainer1() :
    itemIndex(-1),
    action(0),
    isDragging(false)
{
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

void CustomContainer1::function1()
{
    if(action && action->isValid())
    {
        action->execute(itemIndex);
    }
}

void CustomContainer1::handleClickEvent(const touchgfx::ClickEvent& event)
{
    isDragging = false;

    if (event.getType() == touchgfx::ClickEvent::RELEASED && !isDragging)
    {
        // Normal click — let base handle it
        CustomContainer1Base::handleClickEvent(event);
    }
    else if (event.getType() == touchgfx::ClickEvent::CANCEL)
    {
        // Touch was cancelled (e.g. drag started) — don't fire button
        button1.invalidate();
    }
    else
    {
        CustomContainer1Base::handleClickEvent(event);
    }
}

void CustomContainer1::handleDragEvent(const touchgfx::DragEvent& event)
{
    isDragging = true;

    // Cancel the button pressed state visually
    touchgfx::ClickEvent cancelEvent(touchgfx::ClickEvent::CANCEL, event.getNewX(), event.getNewY());
    button1.handleClickEvent(cancelEvent);
    button1.invalidate();

    // Forward drag to parent scroll list
    if (parent)
    {
        parent->handleDragEvent(event);
    }
}

void CustomContainer1::handleGestureEvent(const touchgfx::GestureEvent& event)
{
    isDragging = true;

    if (parent)
    {
        parent->handleGestureEvent(event);
    }
}

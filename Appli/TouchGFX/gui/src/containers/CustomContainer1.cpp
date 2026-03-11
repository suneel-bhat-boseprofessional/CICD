#include <gui/containers/CustomContainer1.hpp>
#include <images/BitmapDatabase.hpp>

CustomContainer1::CustomContainer1() :
    itemIndex(-1),
    action(0)
{
}

void CustomContainer1::setListElements(int item)
{
    itemIndex = item;

    static const char* names[] =
    {
        "ZONE",
        "INOUT",
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

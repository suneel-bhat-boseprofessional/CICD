#include <gui/containers/CustomContainer4.hpp>
#include <touchgfx/Color.hpp>

CustomContainer4::CustomContainer4() :
    itemIndex(-1)
{
    nameBuffer[0] = 0;
}

void CustomContainer4::initialize()
{
    CustomContainer4Base::initialize();
}

void CustomContainer4::setSettingItem(int16_t index)
{
    itemIndex = index;

    static const char* names[] = {
        "System Information",
        "Network",
        "Display",
        "Factory Reset"
    };

    const char* name = (index >= 0 && index < 4) ? names[index] : "---";
    touchgfx::Unicode::fromUTF8((const uint8_t*)name, nameBuffer, 32);
    textArea1.setWildcard(nameBuffer);

    // White text on black background
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));

    // Grey out non-touchable items (only Display index 2 is active)
    if (index != 2)
    {
        textArea1.setAlpha(100);
    }
    else
    {
        textArea1.setAlpha(255);
    }

    textArea1.invalidate();
}

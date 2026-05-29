#include <gui/containers/CustomContainer8.hpp>
#include <touchgfx/Color.hpp>

CustomContainer8::CustomContainer8()
{
    msgBuffer[0] = 0;
}

void CustomContainer8::initialize()
{
    CustomContainer8Base::initialize();
}

void CustomContainer8::setData(int type, const char* msg)
{
    // type: 1 = alert (E74B49), 0 = warning (E78024)
    if (type == 1)
    {
        image4.setVisible(true);
        image3.setVisible(false);
        textArea1.setColor(touchgfx::Color::getColorFromRGB(0xE7, 0x4B, 0x49));
    }
    else
    {
        image3.setVisible(true);
        image4.setVisible(false);
        textArea1.setColor(touchgfx::Color::getColorFromRGB(0xE7, 0x80, 0x24));
    }

    touchgfx::Unicode::strncpy(msgBuffer, msg, MSG_BUF_SIZE);
    textArea1.setWildcard(msgBuffer);

    image3.invalidate();
    image4.invalidate();
    textArea1.invalidate();
}

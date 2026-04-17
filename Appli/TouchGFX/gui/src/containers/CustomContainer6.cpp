#include <gui/containers/CustomContainer6.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

// Y positions and heights matching the label textAreas
static const int16_t ROW_Y[]      = { 0, 23, 44, 65, 84 };
static const int16_t ROW_HEIGHT[] = { 23, 21, 21, 19, 18 };

CustomContainer6::CustomContainer6()
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        valueBuf[i][0] = 0;
        valueArea[i].setPosition(140, ROW_Y[i], 150, ROW_HEIGHT[i]);
        valueArea[i].setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
        valueArea[i].setLinespacing(0);
        valueArea[i].setTypedText(touchgfx::TypedText(T___SINGLEUSE_VZ20));
        valueArea[i].setWildcard(valueBuf[i]);
        add(valueArea[i]);
    }
}

void CustomContainer6::initialize()
{
    CustomContainer6Base::initialize();
}

void CustomContainer6::setValue(int row, const char* value)
{
    if (row < 0 || row >= NUM_ROWS) return;
    touchgfx::Unicode::fromUTF8((const uint8_t*)value, valueBuf[row], BUF_SIZE);
    valueArea[row].invalidate();
}

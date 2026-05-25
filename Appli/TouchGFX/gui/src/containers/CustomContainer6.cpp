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

void CustomContainer6::hideContent()
{
    textArea1.setVisible(false);
    textArea2.setVisible(false);
    textArea3.setVisible(false);
    textArea4.setVisible(false);
    textArea5.setVisible(false);
    textArea6.setVisible(false);
    textArea7.setVisible(false);
    textArea9.setVisible(false);
    textArea10.setVisible(false);
    textArea12.setVisible(false);
    textArea13.setVisible(false);
    textArea14.setVisible(false);
    textArea15.setVisible(false);
    textArea16.setVisible(false);
    textArea17.setVisible(false);
    textArea18.setVisible(false);
    for (int i = 0; i < NUM_ROWS; i++)
    {
        valueArea[i].setVisible(false);
    }
}

void CustomContainer6::showContent()
{
    textArea1.setVisible(true);
    textArea2.setVisible(true);
    textArea3.setVisible(true);
    textArea4.setVisible(true);
    textArea5.setVisible(true);
    textArea6.setVisible(true);
    textArea7.setVisible(true);
    textArea9.setVisible(true);
    textArea10.setVisible(true);
    textArea12.setVisible(true);
    textArea13.setVisible(true);
    textArea14.setVisible(true);
    textArea15.setVisible(true);
    textArea16.setVisible(true);
    textArea17.setVisible(true);
    textArea18.setVisible(true);
    for (int i = 0; i < NUM_ROWS; i++)
    {
        valueArea[i].setVisible(true);
    }
}

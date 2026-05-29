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
    }

    // Wire wildcard buffers to generated TextAreaWithOneWildcard members
    Name_1.setWildcard(valueBuf[0]);
    Model_1.setWildcard(valueBuf[1]);
    FW_V_1.setWildcard(valueBuf[2]);
    Serial_N_1.setWildcard(valueBuf[3]);
    Clock_status_1.setWildcard(valueBuf[4]);
    Temparature_1.setWildcard(valueBuf[5]);
    Disk_S_1.setWildcard(valueBuf[6]);
    CPU_U_1.setWildcard(valueBuf[7]);
}

void CustomContainer6::initialize()
{
    CustomContainer6Base::initialize();
}

void CustomContainer6::setValue(int row, const char* value)
{
    if (row < 0 || row >= NUM_ROWS) return;
    touchgfx::Unicode::fromUTF8((const uint8_t*)value, valueBuf[row], BUF_SIZE);
    switch (row)
    {
    case 0: Name_1.invalidate(); break;
    case 1: Model_1.invalidate(); break;
    case 2: FW_V_1.invalidate(); break;
    case 3: Serial_N_1.invalidate(); break;
    case 4: Clock_status_1.invalidate(); break;
    case 5: Temparature_1.invalidate(); break;
    case 6: Disk_S_1.invalidate(); break;
    case 7: CPU_U_1.invalidate(); break;
    }
}

void CustomContainer6::hideContent()
{
    // Hide static labels and wildcard fields present in generated base
    box1.setVisible(false);
    textArea1.setVisible(false);
    textArea2.setVisible(false);
    textArea3.setVisible(false);
    textArea4.setVisible(false);
    textArea5.setVisible(false);
    textArea13.setVisible(false);
    textArea15.setVisible(false);
    textArea16.setVisible(false);

    Name_1.setVisible(false);
    Model_1.setVisible(false);
    FW_V_1.setVisible(false);
    Serial_N_1.setVisible(false);
    Clock_status_1.setVisible(false);
    Temparature_1.setVisible(false);
    Disk_S_1.setVisible(false);
    CPU_U_1.setVisible(false);
}

void CustomContainer6::showContent()
{
    box1.setVisible(true);
    textArea1.setVisible(true);
    textArea2.setVisible(true);
    textArea3.setVisible(true);
    textArea4.setVisible(true);
    textArea5.setVisible(true);
    textArea13.setVisible(true);
    textArea15.setVisible(true);
    textArea16.setVisible(true);

    Name_1.setVisible(true);
    Model_1.setVisible(true);
    FW_V_1.setVisible(true);
    Serial_N_1.setVisible(true);
    Clock_status_1.setVisible(true);
    Temparature_1.setVisible(true);
    Disk_S_1.setVisible(true);
    CPU_U_1.setVisible(true);
}

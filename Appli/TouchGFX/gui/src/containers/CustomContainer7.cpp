#include <gui/containers/CustomContainer7.hpp>

CustomContainer7::CustomContainer7()
{
    labelBuffer[0] = 0;
    valueBuffer[0] = 0;
}

void CustomContainer7::initialize()
{
    CustomContainer7Base::initialize();
    textArea1.setWildcard(labelBuffer);
    textArea2.setWildcard(valueBuffer);
}

void CustomContainer7::setData(const char* label, const char* value)
{
    touchgfx::Unicode::strncpy(labelBuffer, label ? label : "", LABEL_BUF_SIZE);
    touchgfx::Unicode::strncpy(valueBuffer, value ? value : "", VALUE_BUF_SIZE);
    textArea1.setWildcard(labelBuffer);
    textArea2.setWildcard(valueBuffer);
    textArea1.invalidate();
    textArea2.invalidate();
    setVisible(true);
    invalidate();
}

void CustomContainer7::clearData()
{
    labelBuffer[0] = 0;
    valueBuffer[0] = 0;
    textArea1.setWildcard(labelBuffer);
    textArea2.setWildcard(valueBuffer);
    textArea1.invalidate();
    textArea2.invalidate();
}

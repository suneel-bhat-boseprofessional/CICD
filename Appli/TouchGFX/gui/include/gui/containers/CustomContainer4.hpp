#ifndef CUSTOMCONTAINER4_HPP
#define CUSTOMCONTAINER4_HPP

#include <gui_generated/containers/CustomContainer4Base.hpp>
#include <touchgfx/Unicode.hpp>

class CustomContainer4 : public CustomContainer4Base
{
public:
    CustomContainer4();
    virtual ~CustomContainer4() {}

    virtual void initialize();

    void setSettingItem(int16_t itemIndex);

protected:
    touchgfx::Unicode::UnicodeChar nameBuffer[32];
    int16_t itemIndex;
};

#endif // CUSTOMCONTAINER4_HPP

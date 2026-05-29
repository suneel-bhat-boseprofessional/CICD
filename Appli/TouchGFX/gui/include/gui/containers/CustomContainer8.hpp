#ifndef CUSTOMCONTAINER8_HPP
#define CUSTOMCONTAINER8_HPP

#include <gui_generated/containers/CustomContainer8Base.hpp>
#include <touchgfx/Unicode.hpp>

class CustomContainer8 : public CustomContainer8Base
{
public:
    CustomContainer8();
    virtual ~CustomContainer8() {}

    virtual void initialize();

    // type: 1 = alert, 0 = warning
    void setData(int type, const char* msg);

protected:
    static const int MSG_BUF_SIZE = 32;
    touchgfx::Unicode::UnicodeChar msgBuffer[MSG_BUF_SIZE];
};

#endif // CUSTOMCONTAINER8_HPP

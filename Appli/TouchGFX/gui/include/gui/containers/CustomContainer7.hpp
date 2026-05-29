#ifndef CUSTOMCONTAINER7_HPP
#define CUSTOMCONTAINER7_HPP

#include <gui_generated/containers/CustomContainer7Base.hpp>
#include <touchgfx/Unicode.hpp>

class CustomContainer7 : public CustomContainer7Base
{
public:
    static const uint16_t LABEL_BUF_SIZE = 24;
    static const uint16_t VALUE_BUF_SIZE = 24;

    CustomContainer7();
    virtual ~CustomContainer7() {}

    virtual void initialize();
    void setData(const char* label, const char* value);
    void clearData();
protected:
    touchgfx::Unicode::UnicodeChar labelBuffer[LABEL_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar valueBuffer[VALUE_BUF_SIZE];
};

#endif // CUSTOMCONTAINER7_HPP

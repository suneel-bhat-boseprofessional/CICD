#ifndef CUSTOMCONTAINER6_HPP
#define CUSTOMCONTAINER6_HPP

#include <gui_generated/containers/CustomContainer6Base.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/Unicode.hpp>

class CustomContainer6 : public CustomContainer6Base
{
public:
    CustomContainer6();
    virtual ~CustomContainer6() {}

    virtual void initialize();

    void setValue(int row, const char* value);
    void hideContent();
    void showContent();

protected:
    static const int NUM_ROWS = 8;
    static const int BUF_SIZE = 24;

    touchgfx::Unicode::UnicodeChar valueBuf[NUM_ROWS][BUF_SIZE];
};

#endif // CUSTOMCONTAINER6_HPP

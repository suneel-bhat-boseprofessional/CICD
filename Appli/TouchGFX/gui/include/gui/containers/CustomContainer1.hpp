#ifndef CUSTOMCONTAINER1_HPP
#define CUSTOMCONTAINER1_HPP

#include <gui_generated/containers/CustomContainer1Base.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Callback.hpp>

class CustomContainer1 : public CustomContainer1Base
{
public:
    CustomContainer1();
    virtual ~CustomContainer1() {}

    void setListElements(int item);
    void setAction(touchgfx::GenericCallback<int>& callback);

    virtual void function1();

private:
    int itemIndex;
    touchgfx::GenericCallback<int>* action;

    touchgfx::Unicode::UnicodeChar textArea1Buffer[20];
};

#endif

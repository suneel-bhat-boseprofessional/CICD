#ifndef CUSTOMCONTAINER2_HPP
#define CUSTOMCONTAINER2_HPP

#include <gui_generated/containers/CustomContainer2Base.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/Unicode.hpp>

using namespace touchgfx;

class CustomContainer2 : public CustomContainer2Base
{
public:
    CustomContainer2();

    void setListElements(int item);

    void setAction(GenericCallback<int>& callback);

    void function1();

protected:

    int itemIndex;
    GenericCallback<int>* action;

    // Wildcard buffers for 4 elements
    Unicode::UnicodeChar zoneName[4][20];
};

#endif

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
    void handleButtonPress(const touchgfx::AbstractButton& src);

    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);

protected:
    int itemIndex;
    GenericCallback<int>* action;
    Unicode::UnicodeChar zoneName[4][20];

    // our own callback — separate from base class one
    touchgfx::Callback<CustomContainer2,
        const touchgfx::AbstractButton&> myButtonCallback;
};

#endif

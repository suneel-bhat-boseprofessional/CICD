#ifndef CUSTOMCONTAINER2_HPP
#define CUSTOMCONTAINER2_HPP

#include <gui_generated/containers/CustomContainer2Base.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/events/ClickEvent.hpp>

using namespace touchgfx;

class CustomContainer2 : public CustomContainer2Base
{
public:
    CustomContainer2();

    void setListElements(int item);
    void setAction(GenericCallback<int>& callback);
    void handleButtonPress(const touchgfx::AbstractButton& src);
    void refreshVolumes();
    void setReducedRenderingMode(bool enabled);

    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);

protected:
    int  itemIndex;
    GenericCallback<int>* action;
    bool isDragging;
    bool suppressNextClick;
    bool reducedRenderingMode;
    Unicode::UnicodeChar zoneName[4][20];
    Unicode::UnicodeChar volumeText[4][8];

    touchgfx::Callback<CustomContainer2,
        const touchgfx::AbstractButton&> myButtonCallback;
};

#endif

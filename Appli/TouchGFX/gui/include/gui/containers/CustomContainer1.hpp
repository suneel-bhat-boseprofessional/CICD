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

    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);

private:
    int itemIndex;
    touchgfx::GenericCallback<int>* action;
    bool isDragging;

    touchgfx::Unicode::UnicodeChar textArea1Buffer[20];

    // Our own button callback to replace the base class one
    touchgfx::Callback<CustomContainer1, const touchgfx::AbstractButton&> myButtonCallback;
    void myButtonCallbackHandler(const touchgfx::AbstractButton& src);

    // Dummy callback that does nothing — assigned during drag
    touchgfx::Callback<CustomContainer1, const touchgfx::AbstractButton&> dummyCallback;
    void dummyCallbackHandler(const touchgfx::AbstractButton& src) {}
};

#endif

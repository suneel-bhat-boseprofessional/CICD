#ifndef CUSTOMCONTAINER3_HPP
#define CUSTOMCONTAINER3_HPP

#include <gui_generated/containers/CustomContainer3Base.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/Callback.hpp>
#include <touchgfx/containers/buttons/AbstractButtonContainer.hpp>

class CustomContainer3 : public CustomContainer3Base
{
public:
    CustomContainer3();
    virtual ~CustomContainer3() {}

    virtual void initialize();

    void setSourceName(const char* name);
    void setItemIndex(int16_t index);
    int16_t getItemIndex() const;
    void setSelected(bool selected);

    void setAction(touchgfx::GenericCallback<int16_t>& callback);

    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);

protected:
    touchgfx::Unicode::UnicodeChar sourceNameBuffer[32];
    int16_t itemIndex;

    bool isDragging;
    bool suppressNextClick;

    touchgfx::Callback<CustomContainer3, const touchgfx::AbstractButtonContainer&> buttonCallback;
    touchgfx::GenericCallback<int16_t>* action;

    void buttonCallbackHandler(const touchgfx::AbstractButtonContainer& src);
    void triggerAction();
};

#endif

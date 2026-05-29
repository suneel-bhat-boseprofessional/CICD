#ifndef INOUTVIEW_HPP
#define INOUTVIEW_HPP

#include <gui_generated/inout_screen/InoutViewBase.hpp>
#include <gui/inout_screen/InoutPresenter.hpp>

class InoutView : public InoutViewBase
{
public:
    InoutView();
    virtual ~InoutView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
protected:
};

#endif // INOUTVIEW_HPP

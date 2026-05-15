#ifndef INVIEW_HPP
#define INVIEW_HPP

#include <gui_generated/in_screen/InViewBase.hpp>
#include <gui/in_screen/InPresenter.hpp>

class InView : public InViewBase
{
public:
    InView();
    virtual ~InView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // INVIEW_HPP

#ifndef OUTVIEW_HPP
#define OUTVIEW_HPP

#include <gui_generated/out_screen/OutViewBase.hpp>
#include <gui/out_screen/OutPresenter.hpp>

class OutView : public OutViewBase
{
public:
    OutView();
    virtual ~OutView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // OUTVIEW_HPP

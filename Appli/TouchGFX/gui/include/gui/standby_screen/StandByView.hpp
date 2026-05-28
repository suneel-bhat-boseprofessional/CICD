#ifndef STANDBYVIEW_HPP
#define STANDBYVIEW_HPP

#include <gui_generated/standby_screen/StandByViewBase.hpp>
#include <gui/standby_screen/StandByPresenter.hpp>

class StandByView : public StandByViewBase
{
public:
    StandByView();
    virtual ~StandByView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // STANDBYVIEW_HPP

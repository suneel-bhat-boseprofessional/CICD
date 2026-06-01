#ifndef SETUPVIEW_HPP
#define SETUPVIEW_HPP

#include <gui_generated/setup_screen/SetupViewBase.hpp>
#include <gui/setup_screen/SetupPresenter.hpp>

class SetupView : public SetupViewBase
{
public:
    SetupView();
    virtual ~SetupView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SETUPVIEW_HPP

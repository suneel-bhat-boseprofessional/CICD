#ifndef LAUNCHVIEW_HPP
#define LAUNCHVIEW_HPP

#include <gui_generated/launch_screen/launchViewBase.hpp>
#include <gui/launch_screen/launchPresenter.hpp>

class launchView : public launchViewBase
{
public:
    launchView();
    virtual ~launchView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif

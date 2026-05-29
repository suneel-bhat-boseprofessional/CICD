#ifndef WINKVIEW_HPP
#define WINKVIEW_HPP

#include <gui_generated/wink_screen/WinkViewBase.hpp>
#include <gui/wink_screen/WinkPresenter.hpp>

class WinkView : public WinkViewBase
{
public:
    WinkView();
    virtual ~WinkView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // WINKVIEW_HPP

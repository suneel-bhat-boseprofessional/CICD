#ifndef ZONE2VIEW_HPP
#define ZONE2VIEW_HPP

#include <gui_generated/zone2_screen/zone2ViewBase.hpp>
#include <gui/zone2_screen/zone2Presenter.hpp>

class zone2View : public zone2ViewBase
{
public:
    zone2View();
    virtual ~zone2View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    void volumeChanged(int value);

protected:
};

#endif

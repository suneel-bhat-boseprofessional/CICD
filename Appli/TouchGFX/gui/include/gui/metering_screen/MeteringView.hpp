#ifndef METERINGVIEW_HPP
#define METERINGVIEW_HPP

#include <gui_generated/metering_screen/MeteringViewBase.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>

class MeteringView : public MeteringViewBase
{
public:
    MeteringView();
    virtual ~MeteringView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // METERINGVIEW_HPP

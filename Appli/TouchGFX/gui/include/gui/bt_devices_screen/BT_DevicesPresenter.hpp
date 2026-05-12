#ifndef BT_DEVICESPRESENTER_HPP
#define BT_DEVICESPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BT_DevicesView;

class BT_DevicesPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BT_DevicesPresenter(BT_DevicesView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~BT_DevicesPresenter() {}

private:
    BT_DevicesPresenter();

    BT_DevicesView& view;
};

#endif // BT_DEVICESPRESENTER_HPP

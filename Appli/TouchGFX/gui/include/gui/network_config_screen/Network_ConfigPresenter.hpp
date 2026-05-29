#ifndef NETWORK_CONFIGPRESENTER_HPP
#define NETWORK_CONFIGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Network_ConfigView;

class Network_ConfigPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Network_ConfigPresenter(Network_ConfigView& v);

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

    virtual ~Network_ConfigPresenter() {}

private:
    Network_ConfigPresenter();

    Network_ConfigView& view;
};

#endif // NETWORK_CONFIGPRESENTER_HPP

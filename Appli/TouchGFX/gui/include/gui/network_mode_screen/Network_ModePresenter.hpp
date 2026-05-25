#ifndef NETWORK_MODEPRESENTER_HPP
#define NETWORK_MODEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Network_ModeView;

class Network_ModePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Network_ModePresenter(Network_ModeView& v);

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

    virtual ~Network_ModePresenter() {}

private:
    Network_ModePresenter();

    Network_ModeView& view;
};

#endif // NETWORK_MODEPRESENTER_HPP

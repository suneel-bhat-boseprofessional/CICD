#ifndef IP_ADRESSPRESENTER_HPP
#define IP_ADRESSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class IP_AdressView;

class IP_AdressPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    IP_AdressPresenter(IP_AdressView& v);

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

    virtual ~IP_AdressPresenter() {}

private:
    IP_AdressPresenter();

    IP_AdressView& view;
};

#endif // IP_ADRESSPRESENTER_HPP

#ifndef DEVICE_INFORMATIONPRESENTER_HPP
#define DEVICE_INFORMATIONPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Device_InformationView;

class Device_InformationPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Device_InformationPresenter(Device_InformationView& v);

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

    virtual void notifyDeviceInfoChanged();

    virtual ~Device_InformationPresenter() {}

private:
    Device_InformationPresenter();

    Device_InformationView& view;
};

#endif // DEVICE_INFORMATIONPRESENTER_HPP

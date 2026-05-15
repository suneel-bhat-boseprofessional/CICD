#ifndef ETHERNET_SETTINGSPRESENTER_HPP
#define ETHERNET_SETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Ethernet_SettingsView;

class Ethernet_SettingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Ethernet_SettingsPresenter(Ethernet_SettingsView& v);

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

    virtual ~Ethernet_SettingsPresenter() {}

private:
    Ethernet_SettingsPresenter();

    Ethernet_SettingsView& view;
};

#endif // ETHERNET_SETTINGSPRESENTER_HPP

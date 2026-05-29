#ifndef BT_SETTINGSPRESENTER_HPP
#define BT_SETTINGSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BT_SettingsView;

class BT_SettingsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    BT_SettingsPresenter(BT_SettingsView& v);

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

    virtual ~BT_SettingsPresenter() {}

private:
    BT_SettingsPresenter();

    BT_SettingsView& view;
};

#endif // BT_SETTINGSPRESENTER_HPP

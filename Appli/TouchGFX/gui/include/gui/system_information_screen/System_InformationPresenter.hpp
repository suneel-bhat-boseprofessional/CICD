#ifndef SYSTEM_INFORMATIONPRESENTER_HPP
#define SYSTEM_INFORMATIONPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class System_InformationView;

class System_InformationPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    System_InformationPresenter(System_InformationView& v);

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

    virtual ~System_InformationPresenter() {}

private:
    System_InformationPresenter();

    System_InformationView& view;
};

#endif // SYSTEM_INFORMATIONPRESENTER_HPP

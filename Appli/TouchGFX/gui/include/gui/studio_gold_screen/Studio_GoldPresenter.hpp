#ifndef STUDIO_GOLDPRESENTER_HPP
#define STUDIO_GOLDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Studio_GoldView;

class Studio_GoldPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Studio_GoldPresenter(Studio_GoldView& v);

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

    virtual ~Studio_GoldPresenter() {}

private:
    Studio_GoldPresenter();

    Studio_GoldView& view;
};

#endif // STUDIO_GOLDPRESENTER_HPP

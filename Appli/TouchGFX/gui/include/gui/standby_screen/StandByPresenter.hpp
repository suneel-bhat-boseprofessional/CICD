#ifndef STANDBYPRESENTER_HPP
#define STANDBYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class StandByView;

class StandByPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    StandByPresenter(StandByView& v);

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

    virtual ~StandByPresenter() {}

private:
    StandByPresenter();

    StandByView& view;
};

#endif // STANDBYPRESENTER_HPP

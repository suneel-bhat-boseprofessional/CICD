#ifndef FACTORY_RESETPRESENTER_HPP
#define FACTORY_RESETPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Factory_ResetView;

class Factory_ResetPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Factory_ResetPresenter(Factory_ResetView& v);

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

    virtual ~Factory_ResetPresenter() {}

private:
    Factory_ResetPresenter();

    Factory_ResetView& view;
};

#endif // FACTORY_RESETPRESENTER_HPP

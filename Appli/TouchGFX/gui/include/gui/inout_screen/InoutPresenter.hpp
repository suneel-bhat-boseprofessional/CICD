#ifndef INOUTPRESENTER_HPP
#define INOUTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class InoutView;

class InoutPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    InoutPresenter(InoutView& v);

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

    virtual ~InoutPresenter() {}

private:
    InoutPresenter();

    InoutView& view;
};

#endif // INOUTPRESENTER_HPP

#ifndef METERINGPRESENTER_HPP
#define METERINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class MeteringView;

class MeteringPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    MeteringPresenter(MeteringView& v);

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

    virtual ~MeteringPresenter() {}

private:
    MeteringPresenter();

    MeteringView& view;
};

#endif // METERINGPRESENTER_HPP

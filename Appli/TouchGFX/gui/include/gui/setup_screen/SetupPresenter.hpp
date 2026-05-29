#ifndef SETUPPRESENTER_HPP
#define SETUPPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class SetupView;

class SetupPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    SetupPresenter(SetupView& v);

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

    virtual ~SetupPresenter() {}

private:
    SetupPresenter();

    SetupView& view;
};

#endif // SETUPPRESENTER_HPP

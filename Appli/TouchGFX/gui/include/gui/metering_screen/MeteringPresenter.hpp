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
    virtual ~MeteringPresenter() {}

    virtual void activate();
    virtual void deactivate();

    virtual void notifySourceConfigChanged();
    virtual void zoneNamesUpdated();

private:
    MeteringPresenter();
    MeteringView& view;
};

#endif // METERINGPRESENTER_HPP

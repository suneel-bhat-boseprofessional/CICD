#ifndef ZONEPRESENTER_HPP
#define ZONEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class zoneView;

class zonePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    zonePresenter(zoneView& v);

    virtual void activate();
    virtual void deactivate();
    virtual void zoneNamesUpdated();
    virtual void notifyGoToLaunch();

    void setSelectedZone(int index);
    int  getZoneCount() const;      // used by zoneView instead of global zoneCount

private:
    zonePresenter();
    zoneView& view;
};

#endif // ZONEPRESENTER_HPP

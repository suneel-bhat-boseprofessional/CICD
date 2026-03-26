#ifndef ZONE2PRESENTER_HPP
#define ZONE2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class zone2View;

class zone2Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    zone2Presenter(zone2View& v);

    virtual void activate();
    virtual void deactivate();

    int getSelectedZone();
    int getZoneVolume(int index);
    void setZoneVolume(int index, int value);

    virtual void zoneNamesUpdated();

private:
    zone2Presenter();

    zone2View& view;
};

#endif

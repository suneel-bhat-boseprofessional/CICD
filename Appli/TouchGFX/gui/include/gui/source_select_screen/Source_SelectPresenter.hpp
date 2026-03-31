#ifndef SOURCE_SELECTPRESENTER_HPP
#define SOURCE_SELECTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Source_SelectView;

class Source_SelectPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Source_SelectPresenter(Source_SelectView& v);

    virtual void activate();
    virtual void deactivate();

    int getSelectedZone();
    int getSourceCount();
    const char* getSourceName(int srcIdx);
    int getSelectedSource();
    void setSelectedSource(int srcIdx);

    virtual void zoneNamesUpdated();

    virtual ~Source_SelectPresenter() {}

private:
    Source_SelectPresenter();

    Source_SelectView& view;
};

#endif

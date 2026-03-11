#ifndef ZONEVIEW_HPP
#define ZONEVIEW_HPP

#include <gui_generated/zone_screen/zoneViewBase.hpp>
#include <gui/zone_screen/zonePresenter.hpp>
#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/Callback.hpp>

class zoneView : public zoneViewBase
{
public:
    zoneView();
    virtual ~zoneView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer2& item, int16_t itemIndex);

    void zoneSelected(int16_t index);

protected:
    touchgfx::Callback<zoneView, int16_t> zoneSelectedCallback;
};

#endif

#ifndef ZONEVIEW_HPP
#define ZONEVIEW_HPP

#include <gui_generated/zone_screen/zoneViewBase.hpp>
#include <gui/zone_screen/zonePresenter.hpp>
#include <touchgfx/Callback.hpp>
#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/events/DragEvent.hpp>
#include <touchgfx/events/GestureEvent.hpp>

class zoneView : public zoneViewBase
{
public:
    zoneView();
    virtual ~zoneView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    void scrollList1UpdateItem(CustomContainer2& item, int16_t itemIndex);

    void zoneSelected(int index);

    void zoneNamesUpdated();

    virtual void handleDragEvent(const touchgfx::DragEvent& event);
    virtual void handleGestureEvent(const touchgfx::GestureEvent& event);

protected:
    touchgfx::Callback<zoneView, int> zoneSelectedCallback;
    bool scrollOccurred;
};

#endif

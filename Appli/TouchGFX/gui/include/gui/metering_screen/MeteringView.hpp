#ifndef METERINGVIEW_HPP
#define METERINGVIEW_HPP

#include <gui_generated/metering_screen/MeteringViewBase.hpp>
#include <gui/metering_screen/MeteringPresenter.hpp>
#include <gui/containers/CustomContainer5.hpp>

class MeteringView : public MeteringViewBase
{
public:
    MeteringView();
    virtual ~MeteringView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    // Called by MeteringPresenter when zone count changes
    void updateSourceConfig(int totalZones);

    // ScrollableList item callback — called by generated base
    virtual void scrollList1UpdateItem(CustomContainer5& item, int16_t itemIndex);

    // Model pointer — set by presenter so containers can read zone names
    void setModelPtr(Model* m) { modelPtr = m; }

protected:
    int    currentSourceCount;
    Model* modelPtr;
};

#endif // METERINGVIEW_HPP

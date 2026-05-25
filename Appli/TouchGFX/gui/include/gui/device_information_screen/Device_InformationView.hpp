#ifndef DEVICE_INFORMATIONVIEW_HPP
#define DEVICE_INFORMATIONVIEW_HPP

#include <gui_generated/device_information_screen/Device_InformationViewBase.hpp>
#include <gui/device_information_screen/Device_InformationPresenter.hpp>

class Device_InformationView : public Device_InformationViewBase
{
public:
    Device_InformationView();
    virtual ~Device_InformationView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
    virtual void scrollList1UpdateItem(CustomContainer6& item, int16_t itemIndex);
protected:
    static int32_t savedScrollOffset;
    bool pendingScrollRestore;
};

#endif // DEVICE_INFORMATIONVIEW_HPP

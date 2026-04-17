#ifndef SYSTEM_INFORMATIONVIEW_HPP
#define SYSTEM_INFORMATIONVIEW_HPP

#include <gui_generated/system_information_screen/System_InformationViewBase.hpp>
#include <gui/system_information_screen/System_InformationPresenter.hpp>

class System_InformationView : public System_InformationViewBase
{
public:
    System_InformationView();
    virtual ~System_InformationView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer6& item, int16_t itemIndex);
protected:
};

#endif // SYSTEM_INFORMATIONVIEW_HPP

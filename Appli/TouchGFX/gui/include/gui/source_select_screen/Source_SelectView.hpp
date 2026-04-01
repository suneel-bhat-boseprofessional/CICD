#ifndef SOURCE_SELECTVIEW_HPP
#define SOURCE_SELECTVIEW_HPP

#include <gui_generated/source_select_screen/Source_SelectViewBase.hpp>
#include <gui/source_select_screen/Source_SelectPresenter.hpp>
#include <touchgfx/Callback.hpp>

class Source_SelectView : public Source_SelectViewBase
{
public:
    Source_SelectView();
    virtual ~Source_SelectView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer3& item, int16_t itemIndex);

    void sourcesUpdated();
    void goToLaunchScreen();

protected:
    touchgfx::Callback<Source_SelectView, int16_t> itemSelectedCb;
    void itemSelectedHandler(int16_t itemIndex);
};

#endif

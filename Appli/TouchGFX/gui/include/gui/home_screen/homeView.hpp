#ifndef HOMEVIEW_HPP
#define HOMEVIEW_HPP

#include <gui_generated/home_screen/homeViewBase.hpp>
#include <gui/home_screen/homePresenter.hpp>
#include <gui/containers/CustomContainer1.hpp>
#include <touchgfx/Callback.hpp>

class homeView : public homeViewBase
{
public:
    homeView();
    virtual ~homeView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void scrollList1UpdateItem(CustomContainer1& item, int16_t itemIndex);

    void itemSelected(int index);

private:
    touchgfx::Callback<homeView, int> itemSelectedCallback;
};

#endif

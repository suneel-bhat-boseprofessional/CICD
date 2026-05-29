#ifndef STUDIO_GOLDVIEW_HPP
#define STUDIO_GOLDVIEW_HPP

#include <gui_generated/studio_gold_screen/Studio_GoldViewBase.hpp>
#include <gui/studio_gold_screen/Studio_GoldPresenter.hpp>
#include <touchgfx/Unicode.hpp>

class Studio_GoldView : public Studio_GoldViewBase
{
public:
    Studio_GoldView();
    virtual ~Studio_GoldView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    void flexButtonClicked(const touchgfx::AbstractButtonContainer& src);
    touchgfx::Callback<Studio_GoldView, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    static const int BUF_SIZE = 6;
    touchgfx::Unicode::UnicodeChar buf1[BUF_SIZE];
    touchgfx::Unicode::UnicodeChar buf3[BUF_SIZE];
    touchgfx::Unicode::UnicodeChar buf4[BUF_SIZE];
    touchgfx::Unicode::UnicodeChar buf5[BUF_SIZE];
    touchgfx::Unicode::UnicodeChar buf6[BUF_SIZE];
    touchgfx::Unicode::UnicodeChar buf7[BUF_SIZE];
};

#endif // STUDIO_GOLDVIEW_HPP

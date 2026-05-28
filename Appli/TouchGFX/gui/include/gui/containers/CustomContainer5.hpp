#ifndef CUSTOMCONTAINER5_HPP
#define CUSTOMCONTAINER5_HPP

#include <gui_generated/containers/CustomContainer5Base.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/Unicode.hpp>
#include <gui/model/Model.hpp>

class CustomContainer5 : public CustomContainer5Base
{
public:
    CustomContainer5();
    virtual ~CustomContainer5()
    {
        touchgfx::Application::getInstance()->unregisterTimerWidget(this);
    }

    virtual void initialize();
    virtual void handleTickEvent();

    void setListElements(int itemIndex, int totalZones, Model* model);

protected:
    static const int TICKS_PER_STEP = 1;
    static const int NUM_LEVELS     = 6;
    static const int TOTAL_PHASES   = 2 * NUM_LEVELS;   // 12
    static const int MAX_SLOTS      = 4;
    static const int NAME_BUF_SIZE  = MODEL_ZONE_NAME_MAX_LEN + 1;  // 33

    int  tickCounter;
    int  myItemIndex;
    int  phase[MAX_SLOTS];
    bool slotActive[MAX_SLOTS];
    int  slotMode[MAX_SLOTS]; // 0 = mono, 1 = stereo

    touchgfx::Unicode::UnicodeChar nameBuf1[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf2[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf3[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf4[NAME_BUF_SIZE];

    int  phaseToLevel(int p) const;
    void updateIndicators();
    void hideSourceSlot(int slot);

    // Each hideSourceN() hides BOTH stereo (L/R) AND mono bars.
    // showSourceNStereo() only shows stereo — mono stays hidden.
    void hideSource1();  void showSource1Stereo(int l);
    void hideSource2();  void showSource2Stereo(int l);
    void hideSource3();  void showSource3Stereo(int l);
    void hideSource4();  void showSource4Stereo(int l);

public:
    // Set slot mode: 0 = mono, 1 = stereo
    void setSlotMode(int slot, int mode) { if (slot >= 0 && slot < MAX_SLOTS) slotMode[slot] = mode; }
    int getSlotMode(int slot) const { return (slot >= 0 && slot < MAX_SLOTS) ? slotMode[slot] : 0; }
};

#endif // CUSTOMCONTAINER5_HPP

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

    // Main update — call this from scrollList1UpdateItem
    void setListElements(int itemIndex, int totalZones, Model* model);

    // Call these any time to switch a slot's mode at runtime.
    // slotIndex: 0-3 within this container.
    void setSlotMono(int slotIndex);
    void setSlotStereo(int slotIndex);
    void toggleSlotMode(int slotIndex);   // convenience: flips current mode

protected:
    static const int TICKS_PER_STEP = 1;
    static const int NUM_LEVELS     = 6;
    static const int TOTAL_PHASES   = 2 * NUM_LEVELS;  // 12
    static const int MAX_SLOTS      = 4;
    static const int NAME_BUF_SIZE  = MODEL_ZONE_NAME_MAX_LEN + 1;  // 33

    int  tickCounter;
    int  myItemIndex;
    int  phase[MAX_SLOTS];
    bool slotActive[MAX_SLOTS];
    bool slotMono[MAX_SLOTS];   // true = mono mode, false = stereo mode

    touchgfx::Unicode::UnicodeChar nameBuf1[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf2[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf3[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf4[NAME_BUF_SIZE];

    int  phaseToLevel(int p) const;
    void updateIndicators();
    void hideSourceSlot(int slot);
    void updateSlot(int slot, int level);   // picks stereo or mono based on slotMono[]

    // Hide clears BOTH stereo and mono bars for that slot.
    // Show functions only show their respective set.
    void hideSource1();
    void showSource1Stereo(int l);
    void showSource1Mono(int l);

    void hideSource2();
    void showSource2Stereo(int l);
    void showSource2Mono(int l);

    void hideSource3();
    void showSource3Stereo(int l);
    void showSource3Mono(int l);

    void hideSource4();
    void showSource4Stereo(int l);
    void showSource4Mono(int l);
};

#endif // CUSTOMCONTAINER5_HPP

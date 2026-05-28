#include <gui/containers/CustomContainer5.hpp>

// ---------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------
CustomContainer5::CustomContainer5()
    : tickCounter(0), myItemIndex(0)
{
    phase[0] = 0;
    phase[1] = 3;
    phase[2] = 6;
    phase[3] = 9;

    for (int i = 0; i < MAX_SLOTS; i++)
        slotActive[i] = false;
}

// ---------------------------------------------------------------
// initialize()
// ---------------------------------------------------------------
void CustomContainer5::initialize()
{
    CustomContainer5Base::initialize();

    touchgfx::Application::getInstance()->registerTimerWidget(this);

    textArea1.setWildcard(nameBuf1);
    textArea2.setWildcard(nameBuf2);
    textArea3.setWildcard(nameBuf3);
    textArea4.setWildcard(nameBuf4);

    nameBuf1[0] = 0; nameBuf2[0] = 0;
    nameBuf3[0] = 0; nameBuf4[0] = 0;

    tickCounter = 0;

    // Hide ALL slots completely — stereo, mono, frame image, text
    for (int i = 0; i < MAX_SLOTS; i++)
    {
        slotActive[i] = false;
        hideSourceSlot(i);
    }

    textArea1.setVisible(false); textArea1.invalidate();
    textArea2.setVisible(false); textArea2.invalidate();
    textArea3.setVisible(false); textArea3.invalidate();
    textArea4.setVisible(false); textArea4.invalidate();
}

// ---------------------------------------------------------------
// setListElements()
// ---------------------------------------------------------------
void CustomContainer5::setListElements(int itemIndex, int totalZones, Model* model)
{
    myItemIndex = itemIndex;

    touchgfx::Unicode::UnicodeChar* nameBufs[MAX_SLOTS] = {
        nameBuf1, nameBuf2, nameBuf3, nameBuf4
    };

    touchgfx::TextArea* textAreas[MAX_SLOTS] = {
        &textArea1, &textArea2, &textArea3, &textArea4
    };

    for (int slot = 0; slot < MAX_SLOTS; slot++)
    {
        int  zoneIndex = itemIndex * MAX_SLOTS + slot;
        bool show      = (model != nullptr) && (zoneIndex < totalZones);

        slotActive[slot] = show;

        if (show)
        {
            const char* name = model->getZoneName(zoneIndex);
            if (name == nullptr) name = "";
            touchgfx::Unicode::fromUTF8(
                reinterpret_cast<const uint8_t*>(name),
                nameBufs[slot],
                NAME_BUF_SIZE);
        }
        else
        {
            nameBufs[slot][0] = 0;
            hideSourceSlot(slot);   // hides stereo + mono + image
        }

        textAreas[slot]->setVisible(show);
        textAreas[slot]->invalidate();
    }

    updateIndicators();
}

// ---------------------------------------------------------------
// handleTickEvent
// ---------------------------------------------------------------
void CustomContainer5::handleTickEvent()
{
    if (++tickCounter >= TICKS_PER_STEP)
    {
        tickCounter = 0;
        for (int i = 0; i < MAX_SLOTS; i++)
            phase[i] = (phase[i] + 1) % TOTAL_PHASES;
        updateIndicators();
    }
}

// ---------------------------------------------------------------
// phaseToLevel — triangle wave 0..5..0
// ---------------------------------------------------------------
int CustomContainer5::phaseToLevel(int p) const
{
    if (p < NUM_LEVELS) return p;
    return (2 * NUM_LEVELS - 1) - p - 1;
}

// ---------------------------------------------------------------
// updateIndicators — hides everything first, then shows only
// the correct set (stereo only; mono not used here)
// ---------------------------------------------------------------
void CustomContainer5::updateIndicators()
{
    for (int slot = 0; slot < MAX_SLOTS; slot++)
    {
        if (!slotActive[slot]) continue;

        int level = phaseToLevel(phase[slot]);

        switch (slot)
        {
            case 0: hideSource1(); showSource1Stereo(level); break;
            case 1: hideSource2(); showSource2Stereo(level); break;
            case 2: hideSource3(); showSource3Stereo(level); break;
            case 3: hideSource4(); showSource4Stereo(level); break;
        }
    }
    invalidate();
}

// ---------------------------------------------------------------
// hideSourceSlot — hides stereo bars + mono bars + frame image
// ---------------------------------------------------------------
void CustomContainer5::hideSourceSlot(int slot)
{
    switch (slot)
    {
        case 0: hideSource1(); image1.setVisible(false); break;
        case 1: hideSource2(); image2.setVisible(false); break;
        case 2: hideSource3(); image3.setVisible(false); break;
        case 3: hideSource4(); image4.setVisible(false); break;
    }
}

// ---------------------------------------------------------------
// Source 1 — hides BOTH stereo and mono bars
// ---------------------------------------------------------------
void CustomContainer5::hideSource1()
{
    // Stereo
    L11.setVisible(false); R11.setVisible(false);
    L12.setVisible(false); R12.setVisible(false);
    L13.setVisible(false); R13.setVisible(false);
    L14.setVisible(false); R14.setVisible(false);
    L15.setVisible(false); R15.setVisible(false);
    L16.setVisible(false); R16.setVisible(false);
    // Mono
    Mono11.setVisible(false); Mono12.setVisible(false);
    Mono13.setVisible(false); Mono14.setVisible(false);
    Mono15.setVisible(false); Mono16.setVisible(false);
}
void CustomContainer5::showSource1Stereo(int l)
{
    L11.setVisible(l >= 0); R11.setVisible(l >= 0);
    L12.setVisible(l >= 1); R12.setVisible(l >= 1);
    L13.setVisible(l >= 2); R13.setVisible(l >= 2);
    L14.setVisible(l >= 3); R14.setVisible(l >= 3);
    L15.setVisible(l >= 4); R15.setVisible(l >= 4);
    L16.setVisible(l >= 5); R16.setVisible(l >= 5);
    // Mono stays hidden — hideSource1() already cleared them
}

// ---------------------------------------------------------------
// Source 2
// ---------------------------------------------------------------
void CustomContainer5::hideSource2()
{
    L21.setVisible(false); R21.setVisible(false);
    L22.setVisible(false); R22.setVisible(false);
    L23.setVisible(false); R23.setVisible(false);
    L24.setVisible(false); R24.setVisible(false);
    L25.setVisible(false); R25.setVisible(false);
    L26.setVisible(false); R26.setVisible(false);
    Mono21.setVisible(false); Mono22.setVisible(false);
    Mono23.setVisible(false); Mono24.setVisible(false);
    Mono25.setVisible(false); Mono26.setVisible(false);
}
void CustomContainer5::showSource2Stereo(int l)
{
    L21.setVisible(l >= 0); R21.setVisible(l >= 0);
    L22.setVisible(l >= 1); R22.setVisible(l >= 1);
    L23.setVisible(l >= 2); R23.setVisible(l >= 2);
    L24.setVisible(l >= 3); R24.setVisible(l >= 3);
    L25.setVisible(l >= 4); R25.setVisible(l >= 4);
    L26.setVisible(l >= 5); R26.setVisible(l >= 5);
}

// ---------------------------------------------------------------
// Source 3
// ---------------------------------------------------------------
void CustomContainer5::hideSource3()
{
    L31.setVisible(false); R31.setVisible(false);
    L32.setVisible(false); R32.setVisible(false);
    L33.setVisible(false); R33.setVisible(false);
    L34.setVisible(false); R34.setVisible(false);
    L35.setVisible(false); R35.setVisible(false);
    L36.setVisible(false); R36.setVisible(false);
    Mono31.setVisible(false); Mono32.setVisible(false);
    Mono33.setVisible(false); Mono34.setVisible(false);
    Mono35.setVisible(false); Mono36.setVisible(false);
}
void CustomContainer5::showSource3Stereo(int l)
{
    L31.setVisible(l >= 0); R31.setVisible(l >= 0);
    L32.setVisible(l >= 1); R32.setVisible(l >= 1);
    L33.setVisible(l >= 2); R33.setVisible(l >= 2);
    L34.setVisible(l >= 3); R34.setVisible(l >= 3);
    L35.setVisible(l >= 4); R35.setVisible(l >= 4);
    L36.setVisible(l >= 5); R36.setVisible(l >= 5);
}

// ---------------------------------------------------------------
// Source 4
// ---------------------------------------------------------------
void CustomContainer5::hideSource4()
{
    L41.setVisible(false); R41.setVisible(false);
    L42.setVisible(false); R42.setVisible(false);
    L43.setVisible(false); R43.setVisible(false);
    L44.setVisible(false); R44.setVisible(false);
    L45.setVisible(false); R45.setVisible(false);
    L46.setVisible(false); R46.setVisible(false);
    Mono41.setVisible(false); Mono42.setVisible(false);
    Mono43.setVisible(false); Mono44.setVisible(false);
    Mono45.setVisible(false); Mono46.setVisible(false);
}
void CustomContainer5::showSource4Stereo(int l)
{
    L41.setVisible(l >= 0); R41.setVisible(l >= 0);
    L42.setVisible(l >= 1); R42.setVisible(l >= 1);
    L43.setVisible(l >= 2); R43.setVisible(l >= 2);
    L44.setVisible(l >= 3); R44.setVisible(l >= 3);
    L45.setVisible(l >= 4); R45.setVisible(l >= 4);
    L46.setVisible(l >= 5); R46.setVisible(l >= 5);
}

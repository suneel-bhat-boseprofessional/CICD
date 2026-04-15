#ifndef CUSTOMCONTAINER5_HPP
#define CUSTOMCONTAINER5_HPP

#include <gui_generated/containers/CustomContainer5Base.hpp>
#include <touchgfx/Application.hpp>
#include <touchgfx/Unicode.hpp>

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

protected:
    static const int TICKS_PER_STEP = 3; // 0.2 seconds at 60 fps
    static const int NUM_LEVELS = 6;      // levels 0-5: green, green, green, lightgreen, orange, red
    static const int TOTAL_PHASES = 2 * NUM_LEVELS; // full up+down cycle = 12 phases
    static const int NAME_BUF_SIZE = 16;

    int tickCounter;
    int phase[4];     // per-source phase (0 to TOTAL_PHASES-1)

    touchgfx::Unicode::UnicodeChar nameBuf1[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf2[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf3[NAME_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar nameBuf4[NAME_BUF_SIZE];

    int phaseToLevel(int p) const;
    void updateIndicators();
};

#endif // CUSTOMCONTAINER5_HPP

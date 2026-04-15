#include <gui/containers/CustomContainer5.hpp>

CustomContainer5::CustomContainer5()
    : tickCounter(0)
{
    phase[0] = 0;
    phase[1] = 3;   // offset by 3 phases
    phase[2] = 6;   // offset by 6 phases
    phase[3] = 9;   // offset by 9 phases
}

void CustomContainer5::initialize()
{
    CustomContainer5Base::initialize();

    touchgfx::Unicode::strncpy(nameBuf1, "Reception", NAME_BUF_SIZE);
    touchgfx::Unicode::strncpy(nameBuf2, "Gym", NAME_BUF_SIZE);
    touchgfx::Unicode::strncpy(nameBuf3, "Room", NAME_BUF_SIZE);
    touchgfx::Unicode::strncpy(nameBuf4, "Hall", NAME_BUF_SIZE);

    textArea1.setWildcard(nameBuf1);
    textArea2.setWildcard(nameBuf2);
    textArea3.setWildcard(nameBuf3);
    textArea4.setWildcard(nameBuf4);

    // Start with all indicators hidden
    tickCounter = 0;
    updateIndicators();

    touchgfx::Application::getInstance()->registerTimerWidget(this);
}

void CustomContainer5::handleTickEvent()
{
    tickCounter++;
    if (tickCounter >= TICKS_PER_STEP)
    {
        tickCounter = 0;

        for (int i = 0; i < 4; i++)
        {
            phase[i] = (phase[i] + 1) % TOTAL_PHASES;
        }

        updateIndicators();
    }
}

int CustomContainer5::phaseToLevel(int p) const
{
    // phases 0..5 = rising: level -1,0,1,2,3,4,5 -> we map 0=level0, 5=level5
    // phases 6..11 = falling: level 4,3,2,1,0,-1
    if (p < NUM_LEVELS)
    {
        return p;  // rising: 0->0, 1->1, ..., 5->5
    }
    else
    {
        return (2 * NUM_LEVELS - 1) - p - 1; // falling: 6->4, 7->3, 8->2, 9->1, 10->0, 11->-1
    }
}

void CustomContainer5::updateIndicators()
{
    int l0 = phaseToLevel(phase[0]);
    int l1 = phaseToLevel(phase[1]);
    int l2 = phaseToLevel(phase[2]);
    int l3 = phaseToLevel(phase[3]);

    // Source 1 (dual)
    image5.setVisible(l0 >= 0);
    image6.setVisible(l0 >= 0);
    image7.setVisible(l0 >= 1);
    image8.setVisible(l0 >= 1);
    image9.setVisible(l0 >= 2);
    image10.setVisible(l0 >= 2);
    image11.setVisible(l0 >= 3);
    image12.setVisible(l0 >= 3);
    extra1.setVisible(l0 >= 4);
    extra2.setVisible(l0 >= 4);
    image13.setVisible(l0 >= 5);
    image14.setVisible(l0 >= 5);

    // Source 2 (single)
    image15.setVisible(l1 >= 0);
    image16.setVisible(l1 >= 1);
    image17.setVisible(l1 >= 2);
    image18.setVisible(l1 >= 3);
    extra3.setVisible(l1 >= 4);
    image19.setVisible(l1 >= 5);

    // Source 3 (single)
    image20.setVisible(l2 >= 0);
    image21.setVisible(l2 >= 1);
    image22.setVisible(l2 >= 2);
    image23.setVisible(l2 >= 3);
    extra4.setVisible(l2 >= 4);
    image24.setVisible(l2 >= 5);

    // Source 4 (dual)
    image25.setVisible(l3 >= 0);
    image26.setVisible(l3 >= 0);
    image27.setVisible(l3 >= 1);
    image28.setVisible(l3 >= 1);
    image29.setVisible(l3 >= 2);
    image30.setVisible(l3 >= 2);
    image31.setVisible(l3 >= 3);
    image32.setVisible(l3 >= 3);
    extra5.setVisible(l3 >= 4);
    image35.setVisible(l3 >= 4);
    image33.setVisible(l3 >= 5);
    image34.setVisible(l3 >= 5);

    invalidate();
}

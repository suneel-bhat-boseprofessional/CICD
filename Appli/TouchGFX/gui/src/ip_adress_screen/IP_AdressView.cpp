#include <gui/ip_adress_screen/IP_AdressView.hpp>
#include <gui/network_config_screen/Network_ConfigView.hpp>

uint8_t IP_AdressView::octetValues[2][IP_AdressView::OCTET_COUNT] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
int IP_AdressView::activeSource = 0;

IP_AdressView::IP_AdressView()
    : activeOctet(-1), dragStartY(0), dragAnchorValue(0), visibleOctet(-1)
{
    for (int i = 0; i < OCTET_COUNT; ++i)
    {
        bufU[i][0] = 0;
        bufC[i][0] = 0;
        bufD[i][0] = 0;
    }
}

void IP_AdressView::setupScreen()
{
    IP_AdressViewBase::setupScreen();

    activeSource = static_cast<int>(Network_ConfigView::configSource);

    textArea1.setWildcard(bufC[0]);
    textArea2.setWildcard(bufC[1]);
    textArea3.setWildcard(bufC[2]);
    textArea4.setWildcard(bufC[3]);
    textAreaU1.setWildcard(bufU[0]);
    textAreaU2.setWildcard(bufU[1]);
    textAreaU3.setWildcard(bufU[2]);
    textAreaU4.setWildcard(bufU[3]);
    textAreaD1.setWildcard(bufD[0]);
    textAreaD2.setWildcard(bufD[1]);
    textAreaD3.setWildcard(bufD[2]);
    textAreaD4.setWildcard(bufD[3]);

    refreshAll();
    hideAllUD();
}

void IP_AdressView::tearDownScreen()
{
    IP_AdressViewBase::tearDownScreen();
}

void IP_AdressView::hideAllUD()
{
    textAreaU1.setVisible(false); textAreaD1.setVisible(false);
    textAreaU2.setVisible(false); textAreaD2.setVisible(false);
    textAreaU3.setVisible(false); textAreaD3.setVisible(false);
    textAreaU4.setVisible(false); textAreaD4.setVisible(false);
    textAreaU1.invalidate(); textAreaD1.invalidate();
    textAreaU2.invalidate(); textAreaD2.invalidate();
    textAreaU3.invalidate(); textAreaD3.invalidate();
    textAreaU4.invalidate(); textAreaD4.invalidate();
    visibleOctet = -1;
}

void IP_AdressView::showUDForOctet(int index)
{
    hideAllUD();
    visibleOctet = index;
    switch (index)
    {
    case 0:
        textAreaU1.setVisible(true); textAreaD1.setVisible(true);
        textAreaU1.invalidate(); textAreaD1.invalidate(); break;
    case 1:
        textAreaU2.setVisible(true); textAreaD2.setVisible(true);
        textAreaU2.invalidate(); textAreaD2.invalidate(); break;
    case 2:
        textAreaU3.setVisible(true); textAreaD3.setVisible(true);
        textAreaU3.invalidate(); textAreaD3.invalidate(); break;
    case 3:
        textAreaU4.setVisible(true); textAreaD4.setVisible(true);
        textAreaU4.invalidate(); textAreaD4.invalidate(); break;
    }
}

void IP_AdressView::refreshOctet(int i)
{
    if (i < 0 || i >= OCTET_COUNT) return;
    uint8_t c = octetValues[activeSource][i];
    uint8_t u = static_cast<uint8_t>((c == 0) ? 255 : (c - 1));
    uint8_t d = static_cast<uint8_t>((c == 255) ? 0 : (c + 1));

    touchgfx::Unicode::snprintf(bufC[i], OCTET_BUF_SIZE, "%d", c);
    touchgfx::Unicode::snprintf(bufU[i], OCTET_BUF_SIZE, "%d", u);
    touchgfx::Unicode::snprintf(bufD[i], OCTET_BUF_SIZE, "%d", d);

    switch (i)
    {
    case 0:
        textArea1.invalidate();  textAreaU1.invalidate(); textAreaD1.invalidate(); break;
    case 1:
        textArea2.invalidate();  textAreaU2.invalidate(); textAreaD2.invalidate(); break;
    case 2:
        textArea3.invalidate();  textAreaU3.invalidate(); textAreaD3.invalidate(); break;
    case 3:
        textArea4.invalidate();  textAreaU4.invalidate(); textAreaD4.invalidate(); break;
    }
}

void IP_AdressView::refreshAll()
{
    for (int i = 0; i < OCTET_COUNT; ++i) refreshOctet(i);
}

int IP_AdressView::hitTestOctet(int16_t x, int16_t y) const
{
    // Hit zone: full vertical column for each octet (covers U/center/D rows).
    // Column X ranges align with image2..image5 (width ~80 each).
    if (y < 20 || y > 125) return -1;

    if (x >= 73  && x < 153) return 0;
    if (x >= 164 && x < 244) return 1;
    if (x >= 254 && x < 334) return 2;
    if (x >= 343 && x < 423) return 3;
    return -1;
}

void IP_AdressView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    int16_t x = event.getX();
    int16_t y = event.getY();

    if (event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        int hit = hitTestOctet(x, y);
        if (hit >= 0)
        {
            if (visibleOctet == hit)
            {
                // Same octet tapped again — close the popup
                hideAllUD();
                activeOctet = -1;
                return;
            }
            activeOctet = hit;
            dragStartY = y;
            dragAnchorValue = octetValues[activeSource][hit];
            showUDForOctet(hit);
            return;
        }
        else
        {
            hideAllUD();
        }
    }
    else if (event.getType() == touchgfx::ClickEvent::RELEASED ||
             event.getType() == touchgfx::ClickEvent::CANCEL)
    {
        activeOctet = -1;
    }

    IP_AdressViewBase::handleClickEvent(event);
}

void IP_AdressView::handleDragEvent(const touchgfx::DragEvent& event)
{
    if (activeOctet >= 0)
    {
        int16_t deltaY = dragStartY - event.getNewY(); // up = positive
        int steps = deltaY / DRAG_STEP_PX;
        int newValue = (static_cast<int>(dragAnchorValue) + steps) % 256;
        if (newValue < 0) newValue += 256;

        if (static_cast<uint8_t>(newValue) != octetValues[activeSource][activeOctet])
        {
            octetValues[activeSource][activeOctet] = static_cast<uint8_t>(newValue);
            refreshOctet(activeOctet);
        }
        return;
    }

    IP_AdressViewBase::handleDragEvent(event);
}

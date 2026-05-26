#include <gui/network_config_screen/Network_ConfigView.hpp>
#include <gui/network_mode_screen/Network_ModeView.hpp>
#include <gui/ip_adress_screen/IP_AdressView.hpp>
#include <stdio.h>

static char ipBuf[16];   // "xxx.xxx.xxx.xxx" + null

Network_ConfigView::NetworkField Network_ConfigView::fields[FIELD_COUNT] =
{
    { "Network Mode", "DHCP" },
    { "IP Address",   "0.0.0.0" },
    { "Subnet Mask",  "0.0.0.0" },
    { "Gateway",      "0.0.0.0" },
    { "MAC Address",  "00:00:00:00:00:00" }
};

Network_ConfigView::ConfigSource Network_ConfigView::configSource = Network_ConfigView::SOURCE_ETHERNET;

Network_ConfigView::Network_ConfigView()
    : pressX(0), pressY(0), dragged(false)
{
}

void Network_ConfigView::setupScreen()
{
    Network_ConfigViewBase::setupScreen();

    if (configSource == SOURCE_WIFI)
    {
        touchgfx::Unicode::strncpy(titleBuffer, "WIFI SETTINGS", TITLE_BUF_SIZE);
    }
    else
    {
        touchgfx::Unicode::strncpy(titleBuffer, "ETHERNET SETTINGS", TITLE_BUF_SIZE);
    }
    textArea1.setWildcard(titleBuffer);
    textArea1.resizeToCurrentText();
    textArea1.invalidate();

    // Sync Network Mode field from Network_ModeView selection
    int src = static_cast<int>(configSource);
    fields[0].value = Network_ModeView::dhcpSelected[src] ? "DHCP" : "Static";

    // Sync IP Address field from IP_AdressView octets
    snprintf(ipBuf, sizeof(ipBuf), "%d.%d.%d.%d",
             IP_AdressView::getOctet(src, 0),
             IP_AdressView::getOctet(src, 1),
             IP_AdressView::getOctet(src, 2),
             IP_AdressView::getOctet(src, 3));
    fields[1].value = ipBuf;

    scrollList1.setNumberOfItems(FIELD_COUNT);
    scrollList1.invalidate();
}

void Network_ConfigView::tearDownScreen()
{
    Network_ConfigViewBase::tearDownScreen();
}

void Network_ConfigView::scrollList1UpdateItem(CustomContainer7& item, int16_t itemIndex)
{
    if (itemIndex >= 0 && itemIndex < FIELD_COUNT)
    {
        item.setData(fields[itemIndex].label, fields[itemIndex].value);
    }
    else
    {
        item.clearData();
    }
}

void Network_ConfigView::setField(int index, const char* value)
{
    if (index >= 0 && index < FIELD_COUNT)
    {
        fields[index].value = value;
    }
}

void Network_ConfigView::handleDragEvent(const touchgfx::DragEvent& event)
{
    dragged = true;
    Network_ConfigViewBase::handleDragEvent(event);
}

void Network_ConfigView::handleClickEvent(const touchgfx::ClickEvent& event)
{
    int16_t x = event.getX();
    int16_t y = event.getY();

    if (event.getType() == touchgfx::ClickEvent::PRESSED)
    {
        pressX = x;
        pressY = y;
        dragged = false;
    }
    else if (event.getType() == touchgfx::ClickEvent::RELEASED)
    {
        // Only treat as a tap if movement was small (not a scroll)
        int16_t dx = (x > pressX) ? (x - pressX) : (pressX - x);
        int16_t dy = (y > pressY) ? (y - pressY) : (pressY - y);

        if (dx < 10 && dy < 10 && !dragged)
        {
            // Check if tap is within scrollList1 bounds
            int16_t slX = scrollList1.getX();
            int16_t slY = scrollList1.getY();
            int16_t slW = static_cast<int16_t>(scrollList1.getWidth());
            int16_t slH = static_cast<int16_t>(scrollList1.getHeight());

            if (x >= slX && x < slX + slW && y >= slY && y < slY + slH)
            {
                int16_t localY = y - slY;
                int itemIndex = localY / 51;

                // Index 0 = Network Mode
                if (itemIndex == 0)
                {
                    application().gotoNetwork_Mode_ScreenNoTransition();
                    return;
                }

                // Index 1 = IP Address (only navigate if Static mode)
                if (itemIndex == 1 && !Network_ModeView::dhcpSelected[static_cast<int>(configSource)])
                {
                    application().gotoIP_AdressScreenNoTransition();
                    return;
                }
            }
        }
    }

    Network_ConfigViewBase::handleClickEvent(event);
}

#include <gui/network_config_screen/Network_ConfigView.hpp>
#include <gui/ethernet_settings_screen/Ethernet_SettingsView.hpp>

Network_ConfigView::NetworkField Network_ConfigView::fields[FIELD_COUNT] =
{
    { "Network Mode", "Static" },
    { "IP Address",   "192.168.1.5" },
    { "Subnet Mask",  "255.255.255.0" },
    { "Gateway",      "192.168.0.1" },
    { "MAC Address",  "12.1SDN67263323" }
};

Network_ConfigView::Network_ConfigView()
{
}

void Network_ConfigView::setupScreen()
{
    Network_ConfigViewBase::setupScreen();

    if (Ethernet_SettingsView::savedSelection == 2)
    {
        touchgfx::Unicode::strncpy(titleBuffer, "Secondary Port", TITLE_BUF_SIZE);
    }
    else
    {
        touchgfx::Unicode::strncpy(titleBuffer, "Primary Port", TITLE_BUF_SIZE);
    }
    textArea1.setWildcard(titleBuffer);
    textArea1.resizeToCurrentText();
    textArea1.invalidate();

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

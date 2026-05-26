#ifndef NETWORK_CONFIGVIEW_HPP
#define NETWORK_CONFIGVIEW_HPP

#include <gui_generated/network_config_screen/Network_ConfigViewBase.hpp>
#include <gui/network_config_screen/Network_ConfigPresenter.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/events/DragEvent.hpp>

class Network_ConfigView : public Network_ConfigViewBase
{
public:
    enum ConfigSource { SOURCE_ETHERNET = 0, SOURCE_WIFI = 1 };
    static ConfigSource configSource;

    static const int FIELD_COUNT = 5;
    static const uint16_t TITLE_BUF_SIZE = 20;

    struct NetworkField
    {
        const char* label;
        const char* value;
    };

    Network_ConfigView();
    virtual ~Network_ConfigView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void scrollList1UpdateItem(CustomContainer7& item, int16_t itemIndex);
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleDragEvent(const touchgfx::DragEvent& event);

    // Update a single field by index and refresh the list (optional API).
    static void setField(int index, const char* value);
protected:
    static NetworkField fields[FIELD_COUNT];
    touchgfx::Unicode::UnicodeChar titleBuffer[TITLE_BUF_SIZE];

    int16_t pressX;
    int16_t pressY;
    bool    dragged;
};

#endif // NETWORK_CONFIGVIEW_HPP

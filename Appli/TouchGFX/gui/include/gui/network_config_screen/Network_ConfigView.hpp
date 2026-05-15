#ifndef NETWORK_CONFIGVIEW_HPP
#define NETWORK_CONFIGVIEW_HPP

#include <gui_generated/network_config_screen/Network_ConfigViewBase.hpp>
#include <gui/network_config_screen/Network_ConfigPresenter.hpp>
#include <touchgfx/Unicode.hpp>

class Network_ConfigView : public Network_ConfigViewBase
{
public:
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

    // Update a single field by index and refresh the list (optional API).
    static void setField(int index, const char* value);
protected:
    static NetworkField fields[FIELD_COUNT];
    touchgfx::Unicode::UnicodeChar titleBuffer[TITLE_BUF_SIZE];
};

#endif // NETWORK_CONFIGVIEW_HPP

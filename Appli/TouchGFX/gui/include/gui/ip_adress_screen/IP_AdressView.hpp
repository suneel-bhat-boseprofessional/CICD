#ifndef IP_ADRESSVIEW_HPP
#define IP_ADRESSVIEW_HPP

#include <gui_generated/ip_adress_screen/IP_AdressViewBase.hpp>
#include <gui/ip_adress_screen/IP_AdressPresenter.hpp>
#include <touchgfx/Unicode.hpp>

class IP_AdressView : public IP_AdressViewBase
{
public:
    static const int OCTET_COUNT = 4;
    static const uint16_t OCTET_BUF_SIZE = 5;
    static const int16_t DRAG_STEP_PX = 12; // pixels per value-step

    IP_AdressView();
    virtual ~IP_AdressView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleClickEvent(const touchgfx::ClickEvent& event);
    virtual void handleDragEvent(const touchgfx::DragEvent& event);

    static uint8_t getOctet(int index) { return (index >= 0 && index < OCTET_COUNT) ? octetValues[activeSource][index] : 0; }
    static uint8_t getOctet(int source, int index) { return (source >= 0 && source < 2 && index >= 0 && index < OCTET_COUNT) ? octetValues[source][index] : 0; }
protected:
    static uint8_t octetValues[2][OCTET_COUNT]; // [0]=Ethernet, [1]=WiFi
    static int activeSource;

    int activeOctet;
    int16_t dragStartY;
    uint8_t dragAnchorValue;
    int visibleOctet; // which octet has U/D visible (-1 = none)

    touchgfx::Unicode::UnicodeChar bufU[OCTET_COUNT][OCTET_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar bufC[OCTET_COUNT][OCTET_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar bufD[OCTET_COUNT][OCTET_BUF_SIZE];

    int hitTestOctet(int16_t x, int16_t y) const;
    void refreshOctet(int index);
    void refreshAll();
    void showUDForOctet(int index);
    void hideAllUD();
};

#endif // IP_ADRESSVIEW_HPP

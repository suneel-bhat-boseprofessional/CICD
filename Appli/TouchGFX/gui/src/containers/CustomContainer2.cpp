#include <gui/containers/CustomContainer2.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Unicode.hpp>

CustomContainer2::CustomContainer2() :
    itemIndex(-1),
    action(0),
    myButtonCallback(this, &CustomContainer2::handleButtonPress)
{
    textArea1.setWildcard(zoneName[0]);
    textArea2.setWildcard(zoneName[1]);
    textArea3.setWildcard(zoneName[2]);
    textArea4.setWildcard(zoneName[3]);

    // rebind all buttons to OUR callback
    // this overrides what the base constructor set
    button1.setAction(myButtonCallback);
    button2.setAction(myButtonCallback);
    button3.setAction(myButtonCallback);
    button4.setAction(myButtonCallback);
}

void CustomContainer2::setListElements(int item)
{
    itemIndex = item;
    int base = itemIndex * 4;

    // reset all 4 zones first
    image1.setVisible(false);
    image2.setVisible(false);
    image3.setVisible(false);
    image4.setVisible(false);

    button1.setVisible(false);
    button2.setVisible(false);
    button3.setVisible(false);
    button4.setVisible(false);

    button1.setTouchable(false);
    button2.setTouchable(false);
    button3.setTouchable(false);
    button4.setTouchable(false);

    textArea1.setVisible(false);
    textArea2.setVisible(false);
    textArea3.setVisible(false);
    textArea4.setVisible(false);

    image1.invalidate();
    image2.invalidate();
    image3.invalidate();
    image4.invalidate();

    button1.invalidate();
    button2.invalidate();
    button3.invalidate();
    button4.invalidate();

    textArea1.invalidate();
    textArea2.invalidate();
    textArea3.invalidate();
    textArea4.invalidate();

    // now set only valid zones visible
    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;

        if(zoneIndex < zoneCount)
        {
            Unicode::snprintf(zoneName[i], 20, "Zone %d", zoneIndex + 1);

            if(i == 0)
            {
                textArea1.setVisible(true);
                image1.setVisible(true);
                button1.setVisible(true);
                button1.setTouchable(true);
                textArea1.invalidate();
                image1.invalidate();
                button1.invalidate();
            }
            else if(i == 1)
            {
                textArea2.setVisible(true);
                image2.setVisible(true);
                button2.setVisible(true);
                button2.setTouchable(true);
                textArea2.invalidate();
                image2.invalidate();
                button2.invalidate();
            }
            else if(i == 2)
            {
                textArea3.setVisible(true);
                image3.setVisible(true);
                button3.setVisible(true);
                button3.setTouchable(true);
                textArea3.invalidate();
                image3.invalidate();
                button3.invalidate();
            }
            else if(i == 3)
            {
                textArea4.setVisible(true);
                image4.setVisible(true);
                button4.setVisible(true);
                button4.setTouchable(true);
                textArea4.invalidate();
                image4.invalidate();
                button4.invalidate();
            }
        }
    }

    invalidate();
}

void CustomContainer2::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer2::handleButtonPress(const touchgfx::AbstractButton& src)
{
    int zone = -1;

    if(&src == &button1) zone = 0;
    else if(&src == &button2) zone = 1;
    else if(&src == &button3) zone = 2;
    else if(&src == &button4) zone = 3;

    if(zone == -1) return;

    int realZone = itemIndex * 4 + zone;

    // guard — reject invalid zones
    if(realZone < 0 || realZone >= zoneCount) return;

    if(action && action->isValid())
    {
        action->execute(realZone);
    }
}

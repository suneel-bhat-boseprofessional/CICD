#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/Unicode.hpp>

extern int zoneCount;

CustomContainer2::CustomContainer2() :
    itemIndex(-1),
    action(0)
{
    textArea1.setWildcard(zoneName[0]);
    textArea2.setWildcard(zoneName[1]);
    textArea3.setWildcard(zoneName[2]);
    textArea4.setWildcard(zoneName[3]);
}

void CustomContainer2::setListElements(int item)
{
    itemIndex = item;

    int base = itemIndex * 4;

    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;

        if(zoneIndex < zoneCount)
        {
            Unicode::snprintf(zoneName[i],20,"Zone %d",zoneIndex+1);

            if(i==0)
            {
                textArea1.setVisible(true);
                textArea1.invalidate();

                image1.setVisible(true);
                image1.invalidate();

                button1.setVisible(true);
                button1.setTouchable(true);
                button1.invalidate();
            }
            else if(i==1)
            {
                textArea2.setVisible(true);
                textArea2.invalidate();

                image2.setVisible(true);
                image2.invalidate();

                button2.setVisible(true);
                button2.setTouchable(true);
                button2.invalidate();
            }
            else if(i==2)
            {
                textArea3.setVisible(true);
                textArea3.invalidate();

                image3.setVisible(true);
                image3.invalidate();

                button3.setVisible(true);
                button3.setTouchable(true);
                button3.invalidate();
            }
            else if(i==3)
            {
                textArea4.setVisible(true);
                textArea4.invalidate();

                image4.setVisible(true);
                image4.invalidate();

                button4.setVisible(true);
                button4.setTouchable(true);
                button4.invalidate();
            }
        }
        else
        {
            zoneName[i][0] = 0;

            if(i==0)
            {
                textArea1.setVisible(false);
                textArea1.invalidate();

                image1.setVisible(false);
                image1.invalidate();

                button1.setVisible(false);
                button1.setTouchable(false);
                button1.invalidate();
            }
            else if(i==1)
            {
                textArea2.setVisible(false);
                textArea2.invalidate();

                image2.setVisible(false);
                image2.invalidate();

                button2.setVisible(false);
                button2.setTouchable(false);
                button2.invalidate();
            }
            else if(i==2)
            {
                textArea3.setVisible(false);
                textArea3.invalidate();

                image3.setVisible(false);
                image3.invalidate();

                button3.setVisible(false);
                button3.setTouchable(false);
                button3.invalidate();
            }
            else if(i==3)
            {
                textArea4.setVisible(false);
                textArea4.invalidate();

                image4.setVisible(false);
                image4.invalidate();

                button4.setVisible(false);
                button4.setTouchable(false);
                button4.invalidate();
            }
        }
    }
}

void CustomContainer2::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer2::function1(int zone)
{
    int realZone = itemIndex * 4 + zone;

    if(realZone >= zoneCount)
        return;

    if(action && action->isValid())
    {
        action->execute(realZone);
    }
}

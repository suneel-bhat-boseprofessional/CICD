#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/Unicode.hpp>

using namespace touchgfx;

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

    TextArea* texts[4] =
    {
        &textArea1,
        &textArea2,
        &textArea3,
        &textArea4
    };

    for(int i = 0; i < 4; i++)
    {
        int zoneIndex = base + i;

        if(zoneIndex < zoneCount)
        {
            Unicode::snprintf(zoneName[i],20,"Zone %d",zoneIndex+1);
            texts[i]->setVisible(true);
        }
        else
        {
            Unicode::snprintf(zoneName[i],20,"");
            texts[i]->setVisible(false);
        }
    }

    invalidate();
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
        action->execute(realZone);
}


#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/Unicode.hpp>
#include <gui/model/Model.hpp>

CustomContainer2::CustomContainer2() :
    itemIndex(-1),
    action(0)
{
    // attach wildcard buffers
    textArea1.setWildcard(zoneName[0]);
    textArea2.setWildcard(zoneName[1]);
    textArea3.setWildcard(zoneName[2]);
    textArea4.setWildcard(zoneName[3]);
}

void CustomContainer2::setListElements(int item)
{
    itemIndex = item;
    // Use Model::getZoneName for each zone
    for (int i = 0; i < 4; ++i) {
        Unicode::strncpy(zoneName[i], Model::zoneNames[i], 20);
        zoneName[i][19] = '\0';
    }
    textArea1.invalidate();
    textArea2.invalidate();
    textArea3.invalidate();
    textArea4.invalidate();
}

void CustomContainer2::setAction(GenericCallback<int>& callback)
{
    action = &callback;
}

void CustomContainer2::function1()
{
    if(action && action->isValid())
    {
        action->execute(itemIndex);
    }
}

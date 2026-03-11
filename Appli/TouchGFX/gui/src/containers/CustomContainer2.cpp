#include <gui/containers/CustomContainer2.hpp>
#include <touchgfx/Unicode.hpp>

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

    if(item == 0)
    {
        Unicode::snprintf(zoneName[0],20,"Gym");
        Unicode::snprintf(zoneName[1],20,"Sports");
        Unicode::snprintf(zoneName[2],20,"Fest");
        Unicode::snprintf(zoneName[3],20,"Silent");
    }

    else if(item == 1)
    {
        Unicode::snprintf(zoneName[0],20,"Room");
        Unicode::snprintf(zoneName[1],20,"Lab");
        Unicode::snprintf(zoneName[2],20,"Driving");
        Unicode::snprintf(zoneName[3],20,"Stadium");
    }

    else if(item == 2)
    {
        Unicode::snprintf(zoneName[0],20,"Hall");
        Unicode::snprintf(zoneName[1],20,"Office");
        Unicode::snprintf(zoneName[2],20,"Garden");
        Unicode::snprintf(zoneName[3],20,"Studio");
    }
    else if(item == 3)
      {
          Unicode::snprintf(zoneName[0],20,"Bus");
          Unicode::snprintf(zoneName[1],20,"Car");
          Unicode::snprintf(zoneName[2],20,"Train");
          Unicode::snprintf(zoneName[3],20,"Studio");
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

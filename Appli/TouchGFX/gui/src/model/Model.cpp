#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

int zoneCount = 6;     // CHANGE ZONE COUNT HERE

Model::Model() :
    modelListener(0),
    selectedZone(0)
{
    for(int i = 0; i < MAX_ZONES; i++)
    {
        zoneVolume[i] = 50;
    }
}

void Model::bind(ModelListener* listener)
{
    modelListener = listener;
}

void Model::tick()
{
}

int Model::getSelectedZone()
{
    return selectedZone;
}

void Model::setSelectedZone(int index)
{
    selectedZone = index;
}

int Model::getZoneVolume(int index)
{
    if(index >= zoneCount)
        return 0;

    return zoneVolume[index];
}

void Model::setZoneVolume(int index, int value)
{
    if(index >= zoneCount)
        return;

    zoneVolume[index] = value;
}

extern "C" void set_zone_name_c(int index, const char* name)
{
}

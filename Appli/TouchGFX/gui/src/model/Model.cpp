#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{
    selectedZone = 0;

    // initial volumes for zones
    zoneVolume[0] = 50; // Gym
    zoneVolume[1] = 80; // Bedroom
    zoneVolume[2] = 30; // Fest
    zoneVolume[3] = 00; // Driving
}

void Model::bind(ModelListener* listener)
{
    modelListener = listener;
}

void Model::tick()
{
}

void Model::setSelectedZone(int index)
{
    selectedZone = index;
}

int Model::getSelectedZone()
{
    return selectedZone;
}

void Model::setZoneVolume(int index, int value)
{
    zoneVolume[index] = value;
}

int Model::getZoneVolume(int index)
{
    return zoneVolume[index];
}

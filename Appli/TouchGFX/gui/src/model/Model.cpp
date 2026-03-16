#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <string.h>

int zoneCount = 9;   // change to test

Model* modelInstance = 0;

Model::Model() :
    modelListener(0),
    selectedZone(0),
    zoneNamesChanged(false)   // ← init flag
{
    modelInstance = this;

    for(int i = 0; i < 16; i++)
    {
        zoneVolumes[i] = 0;
        zoneNames[i][0] = '\0';
    }
}

void Model::tick()
{
    // called every frame by TouchGFX task — safe to notify UI here
    if(zoneNamesChanged)
    {
        zoneNamesChanged = false;
        if(modelListener != 0)
        {
            modelListener->zoneNamesUpdated();
        }
    }
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
    if(index >= 0 && index < 16)
    {
        zoneVolumes[index] = value;
    }
}

int Model::getZoneVolume(int index)
{
    if(index >= 0 && index < 16)
    {
        return zoneVolumes[index];
    }
    return 0;
}

void Model::setZoneName(int index, const char* name)
{
    if(index >= 0 && index < 16)
    {
        strncpy(zoneNames[index], name, 31);
        zoneNames[index][31] = '\0';
        zoneNamesChanged = true;   // ← just set flag, do NOT call listener here
    }
}

const char* Model::getZoneName(int index)
{
    if(index >= 0 && index < 16)
    {
        return zoneNames[index];
    }
    return "";
}

extern "C" void set_zone_name_c(int idx, const char* name)
{
    if(modelInstance != 0)
    {
        modelInstance->setZoneName(idx, name);
    }
}

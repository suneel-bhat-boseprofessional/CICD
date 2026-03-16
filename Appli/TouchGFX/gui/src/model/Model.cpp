#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <string.h>

int zoneCount = 4;

Model* modelInstance = 0;

Model::Model() :
    modelListener(0),
    selectedZone(0),
    zoneNamesChanged(false)   // ← init flag
{
    modelInstance = this;

    for(int i = 0; i < MODEL_MAX_ZONES; i++)
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
    if(index >= 0 && index < MODEL_MAX_ZONES)
    {
        zoneVolumes[index] = value;
    }
}

int Model::getZoneVolume(int index)
{
    if(index >= 0 && index < MODEL_MAX_ZONES)
    {
        return zoneVolumes[index];
    }
    return 0;
}

void Model::setZoneCount(int count)
{
    if (count < 0)
    {
        count = 0;
    }
    else if (count > MODEL_MAX_ZONES)
    {
        count = MODEL_MAX_ZONES;
    }

    if (zoneCount != count)
    {
        zoneCount = count;

        if (selectedZone >= zoneCount)
        {
            selectedZone = (zoneCount > 0) ? (zoneCount - 1) : 0;
        }

        for (int i = zoneCount; i < MODEL_MAX_ZONES; i++)
        {
            zoneNames[i][0] = '\0';
            zoneVolumes[i] = 0;
        }

        zoneNamesChanged = true;
    }
}

int Model::getZoneCount() const
{
    return zoneCount;
}

void Model::setZoneName(int index, const char* name)
{
    if(index >= 0 && index < MODEL_MAX_ZONES)
    {
        strncpy(zoneNames[index], name, MODEL_ZONE_NAME_MAX_LEN - 1);
        zoneNames[index][MODEL_ZONE_NAME_MAX_LEN - 1] = '\0';
        zoneNamesChanged = true;   // ← just set flag, do NOT call listener here
    }
}

const char* Model::getZoneName(int index)
{
    if(index >= 0 && index < MODEL_MAX_ZONES)
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

extern "C" void set_zone_count_c(int count)
{
    if (modelInstance != 0)
    {
        modelInstance->setZoneCount(count);
    }
}

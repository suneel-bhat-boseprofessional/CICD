#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <string.h>

int zoneCount = 0;

Model* modelInstance = 0;

Model::Model() :
    modelListener(0),
    selectedZone(0),
    zoneNamesChanged(false)
{
    modelInstance = this;

    for(int i = 0; i < MODEL_MAX_ZONES; i++)
    {
        zoneVolumes[i]     = 0;
        zonePrevVolumes[i] = 0;
        zoneMuted[i]       = false;
        zoneNames[i][0]    = '\0';
    }
}

void Model::tick()
{
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
        if(!zoneMuted[index])
        {
            zonePrevVolumes[index] = value;
        }
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

void Model::setZoneMuted(int index, bool muted)
{
    if(index < 0 || index >= MODEL_MAX_ZONES) return;

    // On entering mute, remember last audible volume.
    if(muted && !zoneMuted[index])
    {
        zonePrevVolumes[index] = zoneVolumes[index];
    }

    // On leaving mute, restore last audible volume if current is zero.
    if(!muted && zoneMuted[index] && zoneVolumes[index] == 0)
    {
        zoneVolumes[index] = zonePrevVolumes[index];
    }

    zoneMuted[index] = muted;
}

bool Model::getZoneMuted(int index)
{
    if(index < 0 || index >= MODEL_MAX_ZONES) return false;
    return zoneMuted[index];
}

void Model::setZoneCount(int count)
{
    if(count < 0)
    {
        count = 0;
    }
    else if(count > MODEL_MAX_ZONES)
    {
        count = MODEL_MAX_ZONES;
    }

    if(zoneCount != count)
    {
        zoneCount = count;

        if(selectedZone >= zoneCount)
        {
            selectedZone = (zoneCount > 0) ? (zoneCount - 1) : 0;
        }

        for(int i = zoneCount; i < MODEL_MAX_ZONES; i++)
        {
            zoneNames[i][0]    = '\0';
            zoneVolumes[i]     = 0;
            zonePrevVolumes[i] = 0;
            zoneMuted[i]       = false;
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
        zoneNamesChanged = true;
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
    if(modelInstance != 0)
    {
        modelInstance->setZoneCount(count);
    }
}

extern "C" int get_zone_count_c(void)
{
    if(modelInstance != 0)
    {
        return modelInstance->getZoneCount();
    }
    return 0;
}

extern "C" void set_zone_volume_c(int idx, int value)
{
    if(modelInstance != 0)
    {
        modelInstance->setZoneVolume(idx, value);
    }
}

extern "C" void set_zone_muted_c(int idx, int muted)
{
    if(modelInstance != 0)
    {
        modelInstance->setZoneMuted(idx, muted ? true : false);
    }
}

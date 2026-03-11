#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "string.h"
#include <stdint.h>

char Model::zoneNames[ZONE_COUNT][ZONE_NAME_MAX_LEN] = { "Gym", "Sports", "Fest", "Silent" };

typedef enum
{
    ZONE_NAMES_IDLE = 0,
    ZONE_NAMES_NEW_UPDATE = 1
} ZoneNamesUpdateState;

static volatile ZoneNamesUpdateState zoneNamesUpdateState = ZONE_NAMES_IDLE;

extern "C" void set_zone_name_c(int idx, const char* name)
{
    if (idx >= 0 && idx < ZONE_COUNT && name != 0)
    {
        strncpy(Model::zoneNames[idx], name, ZONE_NAME_MAX_LEN - 1);
        Model::zoneNames[idx][ZONE_NAME_MAX_LEN - 1] = '\0';
        zoneNamesUpdateState = ZONE_NAMES_NEW_UPDATE;
    }
}

Model::Model() : modelListener(0)
{
    selectedZone = 0;
    // initial volumes for zones
    zoneVolume[0] = 50;
    zoneVolume[1] = 80;
    zoneVolume[2] = 30;
    zoneVolume[3] = 0;
}
void Model::setZoneName(int index, const char* name)
{
    if (index >= 0 && index < ZONE_COUNT) {
        strncpy(zoneNames[index], name, ZONE_NAME_MAX_LEN - 1);
        zoneNames[index][ZONE_NAME_MAX_LEN - 1] = '\0';
    }
}

const char* Model::getZoneName(int index) const
{
    if (index >= 0 && index < ZONE_COUNT) {
        return zoneNames[index];
    }
    return "";
}

void Model::setAllZoneNames(const char* names[], int count)
{
    for (int i = 0; i < count && i < ZONE_COUNT; ++i) {
        setZoneName(i, names[i]);
    }
}

void Model::bind(ModelListener* listener)
{
    modelListener = listener;
}

void Model::tick()
{
    if (zoneNamesUpdateState == ZONE_NAMES_NEW_UPDATE)
    {
        zoneNamesUpdateState = ZONE_NAMES_IDLE;
        if (modelListener)
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
    zoneVolume[index] = value;
}

int Model::getZoneVolume(int index)
{
    return zoneVolume[index];
}

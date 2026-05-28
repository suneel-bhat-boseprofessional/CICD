#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <stdint.h>
#include <string.h>

extern "C" void LCD_SetBacklight(uint8_t brightness_percent);

// ---------------------------------------------------------------
// Singleton — only used by the C bridge functions below
// ---------------------------------------------------------------
Model* modelInstance = 0;

// ---------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------
Model::Model() :
    modelListener(0),
    selectedZone(0),
    zoneCount(0),           // member initialised here — no global
    lcdBrightness(10),
    zoneNamesChanged(false),
    readyReceived(false),
    goToLaunchRequested(false),
    ioColorsChanged(false),
    deviceInfoChanged(false)
{
    modelInstance = this;

    for (int i = 0; i < MODEL_MAX_ZONES; i++)
    {
        zoneVolumes[i]     = 0;
        zonePrevVolumes[i] = 0;
        zoneMuted[i]       = false;
        zoneNames[i][0]    = '\0';
        zoneSourceCount[i] = 0;
        selectedSource[i]  = 0;

        for (int j = 0; j < MODEL_MAX_SOURCES_PER_ZONE; j++)
        {
            zoneSources[i][j][0] = '\0';
        }
    }
}

// ---------------------------------------------------------------
// tick() — called every frame by the TouchGFX scheduler.
// Consumes all pending flags and notifies the Presenter.
// ---------------------------------------------------------------
void Model::tick()
{
    if (zoneNamesChanged)
    {
        zoneNamesChanged = false;
        if (modelListener != 0)
            modelListener->zoneNamesUpdated();
    }

    if (readyReceived)
    {
        readyReceived = false;
        if (modelListener != 0)
            modelListener->notifyReadyReceived();
    }

    if (goToLaunchRequested)
    {
        goToLaunchRequested = false;
        if (modelListener != 0)
            modelListener->notifyGoToLaunch();
    }

    if (ioColorsChanged)
    {
        ioColorsChanged = false;
        if (modelListener != 0)
            modelListener->notifyIOColorsChanged();
    }

    if (deviceInfoChanged)
    {
        deviceInfoChanged = false;
        if (modelListener != 0)
            modelListener->notifyDeviceInfoChanged();
    }
}

// ---------------------------------------------------------------
// Zone selection
// ---------------------------------------------------------------
void Model::setSelectedZone(int index)
{
    selectedZone = index;
}

int Model::getSelectedZone()
{
    return selectedZone;
}

// ---------------------------------------------------------------
// Volume
// ---------------------------------------------------------------
void Model::setZoneVolume(int index, int value)
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return;

    zoneVolumes[index] = value;
    if (!zoneMuted[index])
        zonePrevVolumes[index] = value;

    zoneNamesChanged = true;
}

int Model::getZoneVolume(int index)
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return 0;
    return zoneVolumes[index];
}

// ---------------------------------------------------------------
// Mute
// ---------------------------------------------------------------
void Model::setZoneMuted(int index, bool muted)
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return;

    if (muted && !zoneMuted[index])
        zonePrevVolumes[index] = zoneVolumes[index];

    if (!muted && zoneMuted[index] && zoneVolumes[index] == 0)
        zoneVolumes[index] = zonePrevVolumes[index];

    zoneMuted[index]  = muted;
    zoneNamesChanged  = true;
}

bool Model::getZoneMuted(int index)
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return false;
    return zoneMuted[index];
}

// ---------------------------------------------------------------
// Zone count
// ---------------------------------------------------------------
void Model::setZoneCount(int count)
{
    if (count < 0)                count = 0;
    if (count > MODEL_MAX_ZONES)  count = MODEL_MAX_ZONES;

    if (zoneCount == count) return;   // no change — skip flag set

    zoneCount = count;

    // Clamp selected zone
    if (selectedZone >= zoneCount)
        selectedZone = (zoneCount > 0) ? (zoneCount - 1) : 0;

    // Clear data for zones that no longer exist
    for (int i = zoneCount; i < MODEL_MAX_ZONES; i++)
    {
        zoneNames[i][0]    = '\0';
        zoneVolumes[i]     = 0;
        zonePrevVolumes[i] = 0;
        zoneMuted[i]       = false;
    }

    zoneNamesChanged = true;
}

int Model::getZoneCount() const
{
    return zoneCount;   // reads the member, not a global
}

// ---------------------------------------------------------------
// Zone names
// ---------------------------------------------------------------
void Model::setZoneName(int index, const char* name)
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return;

    strncpy(zoneNames[index], name, MODEL_ZONE_NAME_MAX_LEN - 1);
    zoneNames[index][MODEL_ZONE_NAME_MAX_LEN - 1] = '\0';
    zoneNamesChanged = true;
}

const char* Model::getZoneName(int index) const
{
    if (index < 0 || index >= MODEL_MAX_ZONES) return "";
    return zoneNames[index];
}

// ---------------------------------------------------------------
// Sources
// ---------------------------------------------------------------
void Model::setZoneSourceCount(int zoneIdx, int count)
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES) return;
    if (count < 0)                         count = 0;
    if (count > MODEL_MAX_SOURCES_PER_ZONE) count = MODEL_MAX_SOURCES_PER_ZONE;

    zoneSourceCount[zoneIdx] = count;
    zoneNamesChanged = true;
}

int Model::getZoneSourceCount(int zoneIdx) const
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES) return 0;
    return zoneSourceCount[zoneIdx];
}

void Model::setZoneSourceName(int zoneIdx, int srcIdx, const char* name)
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES)           return;
    if (srcIdx  < 0 || srcIdx  >= MODEL_MAX_SOURCES_PER_ZONE) return;

    strncpy(zoneSources[zoneIdx][srcIdx], name, MODEL_SOURCE_NAME_MAX_LEN - 1);
    zoneSources[zoneIdx][srcIdx][MODEL_SOURCE_NAME_MAX_LEN - 1] = '\0';
    zoneNamesChanged = true;
}

const char* Model::getZoneSourceName(int zoneIdx, int srcIdx) const
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES)           return "";
    if (srcIdx  < 0 || srcIdx  >= MODEL_MAX_SOURCES_PER_ZONE) return "";
    return zoneSources[zoneIdx][srcIdx];
}

void Model::setSelectedSource(int zoneIdx, int srcIdx)
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES)           return;
    if (srcIdx  < 0 || srcIdx  >= MODEL_MAX_SOURCES_PER_ZONE) return;

    selectedSource[zoneIdx] = srcIdx;
    zoneNamesChanged = true;
}

int Model::getSelectedSource(int zoneIdx) const
{
    if (zoneIdx < 0 || zoneIdx >= MODEL_MAX_ZONES) return 0;
    return selectedSource[zoneIdx];
}

// ---------------------------------------------------------------
// LCD brightness
// ---------------------------------------------------------------
void Model::setLcdBrightness(int value)
{
    if (value < 10)  value = 10;
    if (value > 100) value = 100;

    lcdBrightness = value;
    LCD_SetBacklight((uint8_t)lcdBrightness);
}

int Model::getLcdBrightness() const
{
    return lcdBrightness;
}

// ===============================================================
// C bridge — all functions are safe to call from any C file.
// They write to volatile flags so the compiler cannot optimise
// away the write across the C/C++ translation-unit boundary.
// ===============================================================

extern "C" void set_zone_name_c(int idx, const char* name)
{
    if (modelInstance) modelInstance->setZoneName(idx, name);
}

extern "C" void set_zone_count_c(int count)
{
    if (modelInstance) modelInstance->setZoneCount(count);
}

extern "C" int get_zone_count_c(void)
{
    if (modelInstance) return modelInstance->getZoneCount();
    return 0;
}

extern "C" void set_zone_volume_c(int idx, int value)
{
    if (modelInstance) modelInstance->setZoneVolume(idx, value);
}

extern "C" void set_zone_muted_c(int idx, int muted)
{
    if (modelInstance) modelInstance->setZoneMuted(idx, muted != 0);
}

extern "C" void set_zone_source_count_c(int zoneIdx, int count)
{
    if (modelInstance) modelInstance->setZoneSourceCount(zoneIdx, count);
}

extern "C" int get_zone_source_count_c(int zoneIdx)
{
    if (modelInstance) return modelInstance->getZoneSourceCount(zoneIdx);
    return 0;
}

extern "C" void set_zone_source_name_c(int zoneIdx, int srcIdx, const char* name)
{
    if (modelInstance) modelInstance->setZoneSourceName(zoneIdx, srcIdx, name);
}

extern "C" void set_selected_source_c(int zoneIdx, int srcIdx)
{
    if (modelInstance) modelInstance->setSelectedSource(zoneIdx, srcIdx);
}

extern "C" void set_ready_received_c(void)
{
    if (modelInstance) modelInstance->readyReceived = true;
}

extern "C" void set_go_to_launch_c(void)
{
    if (modelInstance) modelInstance->goToLaunchRequested = true;
}

extern "C" void set_io_colors_changed_c(void)
{
    if (modelInstance) modelInstance->ioColorsChanged = true;
}

extern "C" void set_device_info_changed_c(void)
{
    if (modelInstance) modelInstance->deviceInfoChanged = true;
}

extern "C" void set_lcd_brightness_c(int value)
{
    if (modelInstance) modelInstance->setLcdBrightness(value);
}

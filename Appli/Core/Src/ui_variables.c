#include "ui_variables.h"
#include <string.h>

/* Global source info used by protocol.c (C) and TouchGFX C++ code
 * Defined here with C linkage. */
int g_source_count = 0;
const char* g_source_names[32] = {0};

/* ======================================================================
 * IO Colors
 * ====================================================================== */

/* Default color assignments per mode/channel */
static uint8_t ioColorState[IO_MODE_COUNT][IO_CHANNEL_COUNT] = {
    /*GPIO:   */ { 1, 2, 3, 1 },
    /* IN:  */ { 1, 2, 3, 4 },
    /* OUT: */ { 1, 5, 5, 5 }
};

/* RGB look-up table (index 1-5) */
static const uint32_t colorLUT[IO_COLOR_COUNT] = {
    0x337F5C,  /* 1 = Green  */
    0xFAB62E,  /* 2 = Yellow */
    0x3D3C38,  /* 3 = Grey   */
    0x0B84B8,  /* 4 = Blue   */
    0xD03B1E   /* 5 = Red    */
};

uint8_t IOColors_Get(uint8_t mode, uint8_t channel)
{
    if (mode >= IO_MODE_COUNT || channel >= IO_CHANNEL_COUNT)
        return 0;
    return ioColorState[mode][channel];
}

void IOColors_Set(uint8_t mode, uint8_t channel, uint8_t colorIndex)
{
    if (mode >= IO_MODE_COUNT || channel >= IO_CHANNEL_COUNT)
        return;
    if (colorIndex < 1 || colorIndex > IO_COLOR_COUNT)
        return;
    ioColorState[mode][channel] = colorIndex;
}

uint32_t IOColors_IndexToRGB(uint8_t colorIndex)
{
    if (colorIndex < 1 || colorIndex > IO_COLOR_COUNT)
        return 0;
    return colorLUT[colorIndex - 1];
}

/* ======================================================================
 * Device Info
 * ====================================================================== */

static char deviceInfoFields[DEVINFO_FIELD_COUNT][DEVINFO_STR_MAX] = {
    "--",   /* name */
    "--",   /* model */
    "--",   /* firmwareVersion */
    "--",   /* serialNumber */
    "--",   /* temperature */
    "--",   /* cpuUsage */
    "--",   /* diskUsage */
    "--"    /* clockStatus */
};

const char* DeviceInfo_Get(uint8_t field)
{
    if (field >= DEVINFO_FIELD_COUNT)
        return "--";
    return deviceInfoFields[field];
}

void DeviceInfo_Set(uint8_t field, const char* value)
{
    if (field >= DEVINFO_FIELD_COUNT || value == NULL)
        return;
    strncpy(deviceInfoFields[field], value, DEVINFO_STR_MAX - 1);
    deviceInfoFields[field][DEVINFO_STR_MAX - 1] = '\0';
}

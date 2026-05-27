#ifndef UI_VARIABLES_H
#define UI_VARIABLES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ======================================================================
 * IO Colors
 * Color index mapping:
 *   1 = Green   (#337F5C)
 *   2 = Yellow  (#FAB62E)
 *   3 = Grey    (#3D3C38)
 *   4 = Blue    (#0B84B8)
 *   5 = Red     (#D03B1E)
 *
 * IO modes: 0=GPIO, 1=IN, 2=OUT
 * Each mode has 4 channels (indices 0-3).
 * ====================================================================== */

#define IO_COLOR_COUNT   5
#define IO_MODE_COUNT    3
#define IO_CHANNEL_COUNT 4

uint8_t  IOColors_Get(uint8_t mode, uint8_t channel);
void     IOColors_Set(uint8_t mode, uint8_t channel, uint8_t colorIndex);
uint32_t IOColors_IndexToRGB(uint8_t colorIndex);

/* ======================================================================
 * Device Info
 * Fields received from server via {"action":"deviceInfo","payload":{...}}
 * ====================================================================== */

#define DEVINFO_STR_MAX        32
#define DEVINFO_FIELD_COUNT     8

#define DEVINFO_NAME             0
#define DEVINFO_MODEL            1
#define DEVINFO_FIRMWARE_VERSION 2
#define DEVINFO_SERIAL_NUMBER    3
#define DEVINFO_TEMPERATURE      4
#define DEVINFO_CPU_USAGE        5
#define DEVINFO_DISK_USAGE       6
#define DEVINFO_CLOCK_STATUS     7

const char* DeviceInfo_Get(uint8_t field);
void        DeviceInfo_Set(uint8_t field, const char* value);

#ifdef __cplusplus
}
#endif

#endif /* UI_VARIABLES_H */

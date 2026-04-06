/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : firmware_updater.h
  * @brief          : Firmware updater definitions
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIRMWARE_UPDATER_H
#define __FIRMWARE_UPDATER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Firmware Version ----------------------------------------------------------*/
#define FW_VERSION_MAJOR    1
#define FW_VERSION_MINOR    0
#define FW_VERSION_PATCH    0

/* Restart Configuration -----------------------------------------------------*/
#define FW_RESTART_DELAY_MS 500

/* Flash Configuration -------------------------------------------------------*/
#define FLASH_BASE_ADDRESS      0x70000000U
#define FLASH_SIZE              0x00800000U   /* 8 MB */
#define FLASH_SECTOR_SIZE       0x1000U       /* 4 KB */
#define FW_UPDATE_FLAG_ADDRESS  (FLASH_BASE_ADDRESS + FLASH_SIZE - FLASH_SECTOR_SIZE)  /* 0x707FF000 - last sector */
#define FW_UPDATE_FLAG_VALUE    0xA5A5A5A5U  /* Arbitrary unique value to indicate update mode */
/* Device Identification -----------------------------------------------------*/
#define DEVICE_ID               0x00000486U

/* Command IDs ---------------------------------------------------------------*/
#define CMD_IDENTIFY            0x01  /* Detect whether device is in application or bootloader */
#define CMD_ENTER_BOOTLOADER    0x02  /* Request application to reboot into bootloader */

#ifdef __cplusplus
}
#endif

#endif /* __FIRMWARE_UPDATER_H */

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : ram_functions.h
  * @brief          : Header for ram_functions.c file.
  *                   Contains function declarations for RAM-based operations.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RAM_FUNCTIONS_H
#define __RAM_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/**
 * @brief Flash update status enumeration
 */
typedef enum {
    FLASH_UPDATE_OK = 0,
    FLASH_UPDATE_ERROR_INVALID_ADDR,
    FLASH_UPDATE_ERROR_INVALID_SIZE,
    FLASH_UPDATE_ERROR_ERASE_FAILED,
    FLASH_UPDATE_ERROR_PROGRAM_FAILED,
    FLASH_UPDATE_ERROR_VERIFY_FAILED,
    FLASH_UPDATE_ERROR_TIMEOUT
} FlashUpdateStatus_t;

/**
 * @brief Flash update data structure
 */
typedef struct {
    uint32_t flash_base_address;    /* Base flash address */
    uint32_t offset;                /* Offset from base address */
    uint8_t *data;                  /* Pointer to data array */
    uint32_t size;                  /* Size of data in bytes */
    uint8_t verify_after_write;     /* 1 = verify after write, 0 = no verify */
} FlashUpdateConfig_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */
#define XSPI_FUNCTIONAL_MODE_INDIRECT_WRITE ((uint32_t)0x00000000)         /*!< Indirect write mode    */
#define XSPI_FUNCTIONAL_MODE_INDIRECT_READ  ((uint32_t)XSPI_CR_FMODE_0)    /*!< Indirect read mode     */
#define XSPI_FUNCTIONAL_MODE_AUTO_POLLING   ((uint32_t)XSPI_CR_FMODE_1)    /*!< Automatic polling mode */
#define XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED  ((uint32_t)XSPI_CR_FMODE)      /*!< Memory-mapped mode     */
/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */

/**
 * @brief Update flash memory from RAM
 * @param config: Pointer to flash update configuration structure
 * @retval FlashUpdateStatus_t: Status of the update operation
 * @note This function executes from RAM to avoid conflicts during flash operations
 */
FlashUpdateStatus_t RAM_UpdateFlashFlag(FlashUpdateConfig_t *config) __attribute__((section(".ramcode")));

/**
 * @brief Simple flash write function (single word)
 * @param flash_address: Flash address to write to
 * @param offset: Offset from base address
 * @param data: 32-bit data to write
 * @retval FlashUpdateStatus_t: Status of the update operation
 * @note This function executes from RAM
 */
FlashUpdateStatus_t RAM_WriteFlashWord(uint32_t flash_address, uint32_t offset, uint32_t data) __attribute__((section(".ramcode")));

/**
 * @brief Flash array write function (register-based)
 * @param flash_address: Flash address to write to
 * @param offset: Offset from base address
 * @param data: Pointer to data array
 * @param size: Size of data in bytes
 * @retval FlashUpdateStatus_t: Status of the update operation
 * @note This function executes from RAM
 */
FlashUpdateStatus_t RAM_WriteFlashArray(uint32_t flash_address, uint32_t offset,
                                        const uint8_t* data, uint32_t size) __attribute__((section(".ramcode")));

/**
 * @brief Copy RAM functions from ROM to RAM
 * @retval None
 * @note Call this function during system initialization before using RAM functions
 */
void RAM_InitializeFunctions(void);

/**
 * @brief Simple RAM-based flash write for small data
 * @param address: Flash address to write to
 * @param data: Pointer to data
 * @param size: Size in bytes (recommended <= 32 bytes)
 * @retval FlashUpdateStatus_t: Status of the operation
 * @note Optimized for small writes, uses minimal stack space
 */
FlashUpdateStatus_t RAM_WriteFlashSimple(uint32_t address, const uint8_t* data, uint32_t size) __attribute__((section(".ramcode")));

/**
 * @brief Flash array write function (register-based)
 * @param flash_address: Flash address to write to
 * @param offset: Offset from base address
 * @param data: Pointer to data array
 * @param size: Size of data in bytes
 * @retval FlashUpdateStatus_t: Status of the update operation
 * @note This function executes from RAM
 */
FlashUpdateStatus_t RAM_WriteFlashArray(uint32_t flash_address, uint32_t offset,
                                        const uint8_t* data, uint32_t size) __attribute__((section(".ramcode")));


/**********EXAMPLE CODE TO VERIFY THE FLASH FLAG************************/
void Example_UseRAMFlashFunctions(void);


#ifdef __cplusplus
}
#endif

#endif /* __RAM_FUNCTIONS_H */
/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif


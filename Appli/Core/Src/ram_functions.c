/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : ram_functions.c
  * @brief          : Register-based RAM functions for flash operations
  *                   Based on Update_External_Flag_Safe implementation
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

/* Includes ------------------------------------------------------------------*/
#include "ram_functions.h"
#include <string.h>  /* For memcmp */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define FLASH_MEMORY_BASE         0x70000000U
#define FLASH_SECTOR_SIZE         4096U         /* 4KB sectors */
#define FLASH_PAGE_SIZE           256U          /* 256-byte pages */

/* Flash commands */
#define FLASH_CMD_WRITE_ENABLE    0x06
#define FLASH_CMD_PAGE_PROGRAM    0x02
#define FLASH_CMD_SECTOR_ERASE    0x20
#define FLASH_CMD_READ_STATUS     0x05
#define FLASH_CMD_READ_DATA       0x03
#define FLASH_CMD_FAST_READ       0xEB

/* Status register bits */
#define FLASH_SR_WIP              0x01         /* Write in progress */
#define FLASH_SR_WEL              0x02         /* Write enable latch */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* Helper macros for register-based XSPI operations - based on Update_External_Flag_Safe */
#define XSPI_REG_WRITE_ENABLE() \
    do { \
        while (xspi->SR & XSPI_SR_BUSY); \
        MODIFY_REG(xspi->CR,  XSPI_CR_FMODE, 0U); \
        MODIFY_REG(xspi->CR,  XSPI_CR_MSEL,  0U); \
        xspi->CCR = 0U; \
        MODIFY_REG(xspi->TCR, XSPI_TCR_DCYC, 0U); \
        MODIFY_REG(xspi->CCR, (XSPI_CCR_IMODE | XSPI_CCR_IDTR | XSPI_CCR_ISIZE), \
                   (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_DTR_DISABLE | HAL_XSPI_INSTRUCTION_8_BITS)); \
        xspi->IR = FLASH_CMD_WRITE_ENABLE; \
        while (xspi->SR & XSPI_SR_BUSY); \
        xspi->FCR = XSPI_FCR_CTCF; \
    } while(0)

#define XSPI_REG_WAIT_WIP(wip_var) \
    do { \
        do { \
            while (xspi->SR & XSPI_SR_BUSY); \
            MODIFY_REG(xspi->CR,  XSPI_CR_FMODE, 0U); \
            MODIFY_REG(xspi->CR,  XSPI_CR_MSEL,  0U); \
            xspi->CCR = 0U; \
            MODIFY_REG(xspi->TCR, XSPI_TCR_DCYC, 0U); \
            xspi->DLR = 0U; \
            MODIFY_REG(xspi->CCR, (XSPI_CCR_IMODE | XSPI_CCR_IDTR | XSPI_CCR_ISIZE | \
                                   XSPI_CCR_DMODE  | XSPI_CCR_DDTR), \
                       (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_DTR_DISABLE | HAL_XSPI_INSTRUCTION_8_BITS | \
                        HAL_XSPI_DATA_1_LINE        | HAL_XSPI_DATA_DTR_DISABLE)); \
            xspi->CR |= XSPI_CR_FMODE_0; \
            xspi->IR  = FLASH_CMD_READ_STATUS; \
            while (!(xspi->SR & XSPI_SR_FTF)); \
            wip_var = xspi->DR; \
            while (!(xspi->SR & XSPI_SR_TCF)); \
            xspi->FCR = XSPI_FCR_CTCF; \
        } while (wip_var & FLASH_SR_WIP); \
    } while(0)

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief Update flash memory from RAM using register-based approach
 * @param config: Pointer to flash update configuration structure
 * @retval FlashUpdateStatus_t: Status of the update operation  
 * @note This function executes from RAM and uses register-based XSPI control
 *       Based on Update_External_Flag_Safe implementation
 */
__attribute__((section(".ramcode")))
FlashUpdateStatus_t RAM_UpdateFlashFlag(FlashUpdateConfig_t *config)
{
    XSPI_TypeDef *xspi = XSPI2;
    volatile uint8_t wip_status;
    uint32_t target_address, flash_offset;
    uint32_t sector_start, sector_end;
    uint32_t bytes_written = 0;
    uint32_t bytes_verified = 0;  /* Declare at function level */
    uint8_t verify_buf[FLASH_PAGE_SIZE]; /* Stack-based buffer for verification */
    
    /* Validate input parameters */
    if (config == NULL || config->data == NULL || config->size == 0) {
        return FLASH_UPDATE_ERROR_INVALID_ADDR;
    }
    
    target_address = config->flash_base_address + config->offset;
    
    /* Validate flash address range */
    if ((target_address < FLASH_MEMORY_BASE) ||
        (target_address >= (FLASH_MEMORY_BASE + 0x4000000))) {
        return FLASH_UPDATE_ERROR_INVALID_ADDR;
    }
    
    flash_offset = target_address - FLASH_MEMORY_BASE;
    
    /* Calculate sector boundaries for erase operations */
    sector_start = (target_address & ~(FLASH_SECTOR_SIZE - 1));
    sector_end = ((target_address + config->size - 1) & ~(FLASH_SECTOR_SIZE - 1));
    
    /* -------------------------------------------------------------------------
     * CRITICAL: Enter Atomic State - same as Update_External_Flag_Safe
     * -------------------------------------------------------------------------*/
    __disable_irq();
    __DSB(); /* Ensure all memory transactions are finished */
    __ISB(); /* Flush instruction pipeline */
    
    /* -------------------------------------------------------------------------
     * ABORT XIP MODE (Switch to Indirect/Command Mode)
     * -------------------------------------------------------------------------*/
    SET_BIT(XSPI2->CR, XSPI_CR_ABORT);
    CLEAR_BIT(XSPI2->CR, XSPI_CR_TCEN);
    CLEAR_BIT(XSPI2->CR, XSPI_CR_FMODE);
    __DSB(); __ISB();
    
    /* -------------------------------------------------------------------------
     * SECTOR ERASE (Erase all required sectors)
     * -------------------------------------------------------------------------*/
    for (uint32_t sector_addr = sector_start; sector_addr <= sector_end; sector_addr += FLASH_SECTOR_SIZE) {
        uint32_t sector_offset = sector_addr - FLASH_MEMORY_BASE;
        
        /* Write enable for erase */
        XSPI_REG_WRITE_ENABLE();
        
        /* Configure sector erase command */
        while (xspi->SR & XSPI_SR_BUSY);
        MODIFY_REG(xspi->CR,  XSPI_CR_FMODE, 0U);
        MODIFY_REG(xspi->CR,  XSPI_CR_MSEL,  0U);
        xspi->CCR = 0U;
        MODIFY_REG(xspi->TCR, XSPI_TCR_DCYC, 0U);
        MODIFY_REG(xspi->CCR, (XSPI_CCR_IMODE | XSPI_CCR_IDTR | XSPI_CCR_ISIZE |
                               XSPI_CCR_ADMODE | XSPI_CCR_ADDTR | XSPI_CCR_ADSIZE),
                   (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_DTR_DISABLE | HAL_XSPI_INSTRUCTION_8_BITS |
                    HAL_XSPI_ADDRESS_1_LINE     | HAL_XSPI_ADDRESS_DTR_DISABLE     | HAL_XSPI_ADDRESS_24_BITS));
        xspi->IR = FLASH_CMD_SECTOR_ERASE;
        xspi->AR = sector_offset;
        while (xspi->SR & XSPI_SR_BUSY);
        xspi->FCR = XSPI_FCR_CTCF;
        
        /* Wait for erase completion */
        XSPI_REG_WAIT_WIP(wip_status);
    }
    
    /* -------------------------------------------------------------------------
     * PAGE PROGRAM (Write data page by page)
     * -------------------------------------------------------------------------*/
    while (bytes_written < config->size) {
        uint32_t page_offset = flash_offset + bytes_written;
        uint32_t bytes_to_write = ((config->size - bytes_written) > FLASH_PAGE_SIZE) ? 
                                  FLASH_PAGE_SIZE : (config->size - bytes_written);
        
        /* Write enable for programming */
        XSPI_REG_WRITE_ENABLE();
        
        /* Configure page program command */
        while (xspi->SR & XSPI_SR_BUSY);
        MODIFY_REG(xspi->CR,  XSPI_CR_FMODE, 0U);
        MODIFY_REG(xspi->CR,  XSPI_CR_MSEL,  0U);
        xspi->CCR = 0U;
        MODIFY_REG(xspi->TCR, XSPI_TCR_DCYC, 0U);
        xspi->DLR = bytes_to_write - 1U;  /* DLR = bytes - 1 */
        MODIFY_REG(xspi->CCR, (XSPI_CCR_IMODE | XSPI_CCR_IDTR | XSPI_CCR_ISIZE |
                               XSPI_CCR_ADMODE | XSPI_CCR_ADDTR | XSPI_CCR_ADSIZE |
                               XSPI_CCR_DMODE  | XSPI_CCR_DDTR),
                   (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_DTR_DISABLE | HAL_XSPI_INSTRUCTION_8_BITS |
                    HAL_XSPI_ADDRESS_1_LINE     | HAL_XSPI_ADDRESS_DTR_DISABLE     | HAL_XSPI_ADDRESS_24_BITS    |
                    HAL_XSPI_DATA_1_LINE        | HAL_XSPI_DATA_DTR_DISABLE));
        xspi->IR = FLASH_CMD_PAGE_PROGRAM;
        xspi->AR = page_offset;
        
        /* Write data bytes - wait for FIFO space via FTF */
        for (uint32_t i = 0U; i < bytes_to_write; i++) {
            while (!(xspi->SR & XSPI_SR_FTF));
            *(__IO uint8_t*)&xspi->DR = config->data[bytes_written + i];
        }
        while (!(xspi->SR & XSPI_SR_TCF));
        xspi->FCR = XSPI_FCR_CTCF;
        
        /* Wait for program completion */
        XSPI_REG_WAIT_WIP(wip_status);
        
        bytes_written += bytes_to_write;
    }
    
    /* -------------------------------------------------------------------------
     * VERIFICATION (Read back and verify if requested)
     * -------------------------------------------------------------------------*/
    if (config->verify_after_write) {
        bytes_verified = 0;  /* Initialize verification counter */
        
        while (bytes_verified < config->size) {
            uint32_t verify_offset = flash_offset + bytes_verified;
            uint32_t bytes_to_verify = ((config->size - bytes_verified) > FLASH_PAGE_SIZE) ? 
                                       FLASH_PAGE_SIZE : (config->size - bytes_verified);
            
            /* Configure read command */
            while (xspi->SR & XSPI_SR_BUSY);
            MODIFY_REG(xspi->CR,  XSPI_CR_FMODE, 0U);
            MODIFY_REG(xspi->CR,  XSPI_CR_MSEL,  0U);
            xspi->CCR = 0U;
            MODIFY_REG(xspi->TCR, XSPI_TCR_DCYC, 0U);
            xspi->DLR = bytes_to_verify - 1U;
            MODIFY_REG(xspi->CCR, (XSPI_CCR_IMODE | XSPI_CCR_IDTR | XSPI_CCR_ISIZE |
                                   XSPI_CCR_ADMODE | XSPI_CCR_ADDTR | XSPI_CCR_ADSIZE |
                                   XSPI_CCR_DMODE  | XSPI_CCR_DDTR),
                       (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_DTR_DISABLE | HAL_XSPI_INSTRUCTION_8_BITS |
                        HAL_XSPI_ADDRESS_1_LINE     | HAL_XSPI_ADDRESS_DTR_DISABLE     | HAL_XSPI_ADDRESS_24_BITS    |
                        HAL_XSPI_DATA_1_LINE        | HAL_XSPI_DATA_DTR_DISABLE));
            xspi->CR |= XSPI_CR_FMODE_0;   /* Indirect Read mode */
            xspi->IR  = FLASH_CMD_READ_DATA;
            xspi->AR  = verify_offset;
            
            /* Read data for verification */
            for (uint32_t i = 0U; i < bytes_to_verify; i++) {
                while (!(xspi->SR & XSPI_SR_FTF));
                verify_buf[i] = *(__IO uint8_t*)&xspi->DR;
            }
            while (!(xspi->SR & XSPI_SR_TCF));
            xspi->FCR = XSPI_FCR_CTCF;
            
            /* Compare with expected data */
            for (uint32_t i = 0; i < bytes_to_verify; i++) {
                if (verify_buf[i] != config->data[bytes_verified + i]) {
                    /* Restore XIP mode before returning error */
                    goto restore_xip_mode;
                }
            }
            
            bytes_verified += bytes_to_verify;
        }
    }
    
restore_xip_mode:
    /* -------------------------------------------------------------------------
     * RESTORE XIP MODE (Fast Quad Read 0xEB) - same as Update_External_Flag_Safe
     * -------------------------------------------------------------------------*/
    xspi->CR &= ~XSPI_CR_FMODE; /* Force Indirect mode while configuring */
    __DSB(); __ISB();
    
    xspi->CCR = (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_8_BITS |
                 HAL_XSPI_ADDRESS_4_LINES     | HAL_XSPI_ADDRESS_24_BITS    |
                 HAL_XSPI_DATA_4_LINES);
    
    /* Set Instruction Code for Read */
    xspi->IR = FLASH_CMD_FAST_READ;
    
    /* Set Dummy Cycles (6 as per reference code) */
    xspi->TCR = (6U << XSPI_TCR_DCYC_Pos);
    
    /* Configure WRITE CCR (WCCR) - Quad Page Program 0x38 */
    xspi->WCCR = (HAL_XSPI_INSTRUCTION_1_LINE | HAL_XSPI_INSTRUCTION_8_BITS |
                  HAL_XSPI_ADDRESS_4_LINES     | HAL_XSPI_ADDRESS_24_BITS    |
                  HAL_XSPI_DATA_4_LINES);
    
    /* Set Instruction Code for Write */
    xspi->WIR = 0x38;
    
    /* ATOMIC SWITCH TO MEMORY MAPPED */
    __DSB(); __ISB();
    
    uint32_t cr_val = xspi->CR;
    cr_val &= ~(XSPI_CR_FMODE | XSPI_CR_TCEN);
    cr_val |= (XSPI_FUNCTIONAL_MODE_MEMORY_MAPPED);
    xspi->CR = cr_val;
    
    __DSB(); __ISB();
    
    /* Cache Invalidation (Crucial for N6) */
    SCB_InvalidateICache();
    SCB_InvalidateDCache_by_Addr((uint32_t*)target_address, 
                                 ((config->size + 31) & ~31)); /* Align to cache line */
    
    __enable_irq();
    
    /* Check verification result */
    if (config->verify_after_write && (bytes_verified != bytes_written)) {
        return FLASH_UPDATE_ERROR_VERIFY_FAILED;
    }
    
    return FLASH_UPDATE_OK;
}

/**
 * @brief Simple flash write function for single word (register-based)
 * @param flash_address: Flash address to write to
 * @param offset: Offset from base address
 * @param data: 32-bit data to write
 * @retval FlashUpdateStatus_t: Status of the update operation
 * @note This function executes from RAM and uses the same approach as Update_External_Flag_Safe
 */
__attribute__((section(".ramcode")))
FlashUpdateStatus_t RAM_WriteFlashWord(uint32_t flash_address, uint32_t offset, uint32_t data)
{
    /* Create a simple configuration for the word write */
    uint8_t write_data[4] = { 
        (uint8_t)(data),         /* LSB first */
        (uint8_t)(data >> 8U), 
        (uint8_t)(data >> 16U), 
        (uint8_t)(data >> 24U)   /* MSB last */
    };
    
    FlashUpdateConfig_t config = {
        .flash_base_address = flash_address,
        .offset = offset,
        .data = write_data,
        .size = 4,
        .verify_after_write = 1  /* Always verify single word writes */
    };
    
    return RAM_UpdateFlashFlag(&config);
}

/**
 * @brief Flash array write function (register-based)
 * @param flash_address: Flash address to write to
 * @param offset: Offset from base address
 * @param data: Pointer to data array
 * @param size: Size of data in bytes
 * @retval FlashUpdateStatus_t: Status of the update operation  
 * @note This function executes from RAM
 */
__attribute__((section(".ramcode")))
FlashUpdateStatus_t RAM_WriteFlashArray(uint32_t flash_address, uint32_t offset, 
                                       const uint8_t* data, uint32_t size)
{
    /* Create configuration for array write */
    FlashUpdateConfig_t config = {
        .flash_base_address = flash_address,
        .offset = offset,
        .data = (uint8_t*)data,  /* Cast away const for interface compatibility */
        .size = size,
        .verify_after_write = 0  /* Caller can choose verification separately */
    };
    
    return RAM_UpdateFlashFlag(&config);
}

/**
 * @brief Copy RAM functions from ROM to RAM
 * @retval None
 * @note Call this function during system initialization before using RAM functions
 */
void RAM_InitializeFunctions(void)
{
    extern uint32_t _siramcode;  /* Start of ramcode in ROM */
    extern uint32_t _sramcode;   /* Start of ramcode in RAM */
    extern uint32_t _eramcode;   /* End of ramcode in RAM */
    
    uint32_t *src = &_siramcode;
    uint32_t *dst = &_sramcode;
    uint32_t *end = &_eramcode;
    
    /* Copy functions from ROM to RAM */
    while (dst < end) {
        *dst++ = *src++;
    }
    
    /* Ensure copy is complete before proceeding */
    __DSB();
    __ISB();
}

/**
 * @brief Simple RAM-based flash write for small data (no large stack buffers)  
 * @param address: Flash address to write to
 * @param data: Pointer to data
 * @param size: Size in bytes (recommended <= 32 bytes)
 * @retval FlashUpdateStatus_t: Status of the operation
 * @note Optimized for small writes, uses minimal stack space
 */
__attribute__((section(".ramcode")))
FlashUpdateStatus_t RAM_WriteFlashSimple(uint32_t address, const uint8_t* data, uint32_t size)
{
    /* For small writes, disable verification to avoid large stack allocation */
    FlashUpdateConfig_t config = {
        .flash_base_address = address,
        .offset = 0,
        .data = (uint8_t*)data,
        .size = size,
        .verify_after_write = (size <= 4) ? 1 : 0  /* Only verify very small writes */
    };
    
    return RAM_UpdateFlashFlag(&config);
}


/**
 * @brief Example function showing how to use RAM-based flash functions
 * @note Different ways to use the new register-based flash operations
 */
void Example_UseRAMFlashFunctions(void)
{
    FlashUpdateStatus_t result;
    uint32_t test_address = 0x70200000; /* Example address in external flash */

    printf("Starting RAM flash functions test...\r\n");

    /* FIXED: Combine all data into single write to avoid sector erase conflicts */
    typedef struct {
        uint32_t test_word;                    /* Offset 0: 32-bit word */
        uint8_t test_array[8];                /* Offset 4: byte array */
        uint32_t padding;                      /* Offset 12: alignment */
        struct {                               /* Offset 16: configuration structure */
            uint32_t magic_number;
            uint16_t version;
            uint8_t flags;
            uint8_t reserved;
            char name[16];
        } config_data;
    } CombinedTestData_t;

    CombinedTestData_t combined_data = {
        .test_word = 0x12345678,
        .test_array = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x11, 0x22},
        .padding = 0x00000000,
        .config_data = {
            .magic_number = 0xDEADBEEF,
            .version = 0x0100,
            .flags = 0x42,
            .reserved = 0,
            .name = "TestConfig"
        }
    };

    /* Write all data in a single operation */
    FlashUpdateConfig_t flash_config = {
        .flash_base_address = test_address,
        .offset = 0,  /* Start at base address */
        .data = (uint8_t*)&combined_data,
        .size = sizeof(combined_data),
        .verify_after_write = 1  /* Enable verification */
    };

    result = RAM_UpdateFlashFlag(&flash_config);
    if (result == FLASH_UPDATE_OK) {
        printf("✅ All data written successfully in single operation\r\n");
        printf("   Word (0x%08X): 0x%08X\r\n", test_address, combined_data.test_word);
        printf("   Array (0x%08X): [0x%02X, 0x%02X, 0x%02X, 0x%02X...]\r\n",
               test_address + 4, combined_data.test_array[0], combined_data.test_array[1],
               combined_data.test_array[2], combined_data.test_array[3]);
        printf("   Struct (0x%08X): Magic=0x%08X, Version=0x%04X\r\n",
               test_address + 16, combined_data.config_data.magic_number, combined_data.config_data.version);
    } else {
        printf("❌ Combined data write failed: ");
        switch (result) {
            case FLASH_UPDATE_ERROR_INVALID_ADDR:
                printf("Invalid address\r\n");
                break;
            case FLASH_UPDATE_ERROR_ERASE_FAILED:
                printf("Sector erase failed\r\n");
                break;
            case FLASH_UPDATE_ERROR_PROGRAM_FAILED:
                printf("Programming failed\r\n");
                break;
            case FLASH_UPDATE_ERROR_VERIFY_FAILED:
                printf("Verification failed\r\n");
                break;
            default:
                printf("Error code %d\r\n", result);
                break;
        }
    }
}


/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined ( __ICCARM__ )
#  define CMSE_NS_CALL  __cmse_nonsecure_call
#  define CMSE_NS_ENTRY __cmse_nonsecure_entry
#else
#  define CMSE_NS_CALL  __attribute((cmse_nonsecure_call))
#  define CMSE_NS_ENTRY __attribute((cmse_nonsecure_entry))
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32n6xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;

// Touch processing constants
#define MAX_NUM_TOUCHES 10
#define MOVE_LIMIT 2
#define NO_TOUCH 0
#define KEY_DOWN 1
#define KEY_UP 2
#define KEY_MOVE 3
#define KEY_PRESS 4

// Touch processing structure (matches stx_getraw.c)
struct coop_data
{
    uint16_t per_x;
    uint16_t per_y;
    uint16_t x;
    uint16_t y;
    uint16_t status;
    uint16_t per_valuebit;
};

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* Function pointer declaration in non-secure*/
#if defined ( __ICCARM__ )
typedef void (CMSE_NS_CALL *funcptr)(void);
#else
typedef void CMSE_NS_CALL (*funcptr)(void);
#endif

/* typedef for non-secure callback functions */
typedef funcptr funcptr_NS;

/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
// Printf redirection functions
#ifdef __GNUC__
int _write(int file, char *ptr, int len);
#endif

#if defined(__ICCARM__) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
int fputc(int ch, FILE *f);
#endif

int __putchar(int ch);
void uart_printf(const char* format, ...);

// I2C functions
HAL_StatusTypeDef I2C_ReadRegister_0x55(uint8_t regAddr, uint8_t *data, uint16_t dataSize);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CTP_RESET_Pin GPIO_PIN_8
#define CTP_RESET_GPIO_Port GPIOE
#define VCOM_RX_Pin GPIO_PIN_6
#define VCOM_RX_GPIO_Port GPIOE
#define VCOM_TX_Pin GPIO_PIN_5
#define VCOM_TX_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

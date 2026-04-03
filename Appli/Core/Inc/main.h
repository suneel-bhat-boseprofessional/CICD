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
extern UART_HandleTypeDef huart;

// Touch processing constants
#define MAX_NUM_TOUCHES 10
#define MOVE_LIMIT 2

#define NO_TOUCH 0
#define KEY_DOWN 1
#define KEY_UP 2
#define KEY_MOVE 4

#define KEY_PRESS 3
#ifndef KEY_MOVE
#define KEY_MOVE KEY_PRESS
#endif

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

/* UART Configuration - Change USE_UART2 to switch between UARTs */
/* UART1 = Debug port, UART2 = Product port */
#define USE_UART2                   1  // Set to 1 for UART2 (product), 0 for UART1 (debug)

#if USE_UART2
    #define UART_INSTANCE           USART2
    #define UART_CLK_ENABLE()       __HAL_RCC_USART2_CLK_ENABLE()
    #define UART_CLK_DISABLE()      __HAL_RCC_USART2_CLK_DISABLE()
    #define UART_IRQn               USART2_IRQn
    #define UART_PERIPH_CLKSOURCE   RCC_PERIPHCLK_USART2
    #define UART_CLKSOURCE_PCLK     RCC_USART2CLKSOURCE_PCLK1
    #define UART_TX_GPIO_PORT       GPIOD
    #define UART_TX_PIN             GPIO_PIN_5
    #define UART_RX_GPIO_PORT       GPIOF
    #define UART_RX_PIN             GPIO_PIN_6
    #define UART_GPIO_AF            GPIO_AF7_USART2
    #define UART_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOD_CLK_ENABLE()
    #define UART_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOF_CLK_ENABLE()
    #define DEBUG_PRINTF(...)       printf(__VA_ARGS__)  // Debug output over UART2
#else
    #define UART_INSTANCE           USART1
    #define UART_CLK_ENABLE()       __HAL_RCC_USART1_CLK_ENABLE()
    #define UART_CLK_DISABLE()      __HAL_RCC_USART1_CLK_DISABLE()
    #define UART_IRQn               USART1_IRQn
    #define UART_PERIPH_CLKSOURCE   RCC_PERIPHCLK_USART1
    #define UART_CLKSOURCE_PCLK     RCC_USART1CLKSOURCE_PCLK2
    #define UART_TX_GPIO_PORT       GPIOE
    #define UART_TX_PIN             GPIO_PIN_5
    #define UART_RX_GPIO_PORT       GPIOE
    #define UART_RX_PIN             GPIO_PIN_6
    #define UART_GPIO_AF            GPIO_AF7_USART1
    #define UART_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()
    #define UART_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOE_CLK_ENABLE()
    #define DEBUG_PRINTF(...)       printf(__VA_ARGS__)  // Debug output enabled
#endif

#define LCD_BL_Pin GPIO_PIN_12
#define LCD_BL_GPIO_Port GPIOC
#define VCOM_RX_Pin GPIO_PIN_6
#define VCOM_RX_GPIO_Port GPIOE
#define VCOM_TX_Pin GPIO_PIN_5
#define VCOM_TX_GPIO_Port GPIOE
#define LCD_NRST_Pin GPIO_PIN_9
#define LCD_NRST_GPIO_Port GPIOD
#define LCD_ON_OFF_Pin GPIO_PIN_8
#define LCD_ON_OFF_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
#define RX_BUFFER_SIZE   1024
#define UART_QUEUE_LEN   sizeof(uint8_t)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

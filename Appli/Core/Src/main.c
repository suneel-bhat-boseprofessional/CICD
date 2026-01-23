/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
extern int notifyTouch;
#include "stm32n6xx_it.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Typedefs for compatibility
typedef uint8_t u8;
typedef uint16_t u16;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
int max_touches = MAX_NUM_TOUCHES;  
struct coop_data finger[MAX_NUM_TOUCHES];  
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);
static void SystemIsolation_Config(void);
/* USER CODE BEGIN PFP */
HAL_StatusTypeDef I2C_ReadRegister_0x55(uint8_t regAddr, uint8_t *data, uint16_t dataSize);
void process_touch_data(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
 * @brief Read register from I2C device at address 0x55
 * @param regAddr Register address to read from
 * @param data Pointer to buffer for received data
 * @param dataSize Number of bytes to read
 * @retval HAL status
 */
HAL_StatusTypeDef I2C_ReadRegister_0x55(uint8_t regAddr, uint8_t *data, uint16_t dataSize)
{
    HAL_StatusTypeDef status;
    uint16_t deviceAddr = 0x55 << 1; // Left shift for HAL (0xAA for write, 0xAB for read)
    
    // Step 1: Write register address (0xAA = write address)
    status = HAL_I2C_Master_Transmit(&hi2c1, deviceAddr, &regAddr, 1, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        printf("I2C Write failed: 0x%02X\r\n", status);
        return status;
    }
    
    // Step 2: Add delay as specified
    HAL_Delay(1);
    
    // Step 3: Read data (0xAB = read address, automatically handled by HAL)
    status = HAL_I2C_Master_Receive(&hi2c1, deviceAddr, data, dataSize, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        printf("I2C Read failed: 0x%02X\r\n", status);
        return status;
    }
    
    return HAL_OK;
}

/**
 * @brief Process touch data from I2C device
 * @retval None
 */
void process_touch_data(void)
{
    uint8_t regAddr = 0x12; // Register address to read from
    uint8_t readData[40];   // Buffer for read data
    uint16_t bytesToRead = 40; // Number of bytes to read
    uint8_t i;
    
    HAL_StatusTypeDef result = I2C_ReadRegister_0x55(regAddr, readData, bytesToRead);
    
    if (result == HAL_OK)
    {
        for (i = 0; i < max_touches; i++)
        {
            if (readData[i * 4] & 0x80)
            {
                finger[i].x = (u16)((readData[i * 4] & 0x70) << 4 | readData[i * 4 + 1]);
                finger[i].y = (u16)((readData[i * 4] & 0x07) << 8 | readData[i * 4 + 2]);
                if(finger[i].per_valuebit == 0)
                {
                    finger[i].status = KEY_DOWN;
                    finger[i].per_x = finger[i].x;
                    finger[i].per_y = finger[i].y;
                }
                else if((abs(finger[i].per_x - finger[i].x) > MOVE_LIMIT)||(abs(finger[i].per_y - finger[i].y) > MOVE_LIMIT))
                {
                    finger[i].status = KEY_MOVE;
                    finger[i].per_x = finger[i].x;
                    finger[i].per_y = finger[i].y;
                }
                else
                {
                    finger[i].status = KEY_PRESS;
                }
                finger[i].per_valuebit = 1;
                printf(" touch down X=%d,Y=%d\r\n", finger[i].x, finger[i].y);
            }
            else
            {
                finger[i].x = 0;
                finger[i].y = 0;
                finger[i].per_x = 0;
                finger[i].per_y = 0;
                if(finger[i].per_valuebit == 0)
                {
                    finger[i].status = NO_TOUCH;
                }
                else
                {
                    finger[i].status = KEY_UP;
                }
                finger[i].per_valuebit = 0;
            }
        }
    }
    else
    {
        printf("I2C Read failed with status: 0x%02X\r\n", result);
    }
    notifyTouch = 0; 
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  SystemIsolation_Config();
  /* USER CODE BEGIN 2 */
  printf("APPLICATION STARTED\r\n");
  HAL_StatusTypeDef result;
  uint8_t i;

  printf("Scanning I2C devices...\r\n");
  for (i=1; i<128; i++)
  {
    /*
     * the HAL wants a left aligned i2c address
     * &hi2c1 is the handle
     * (uint16_t)(i<<1) is the i2c address left aligned
     * retries 2
     * timeout 2
     */
    result = HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(i<<1), 2, 2);
    if (result != HAL_OK) // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
    {
      printf(".");
    }
    if (result == HAL_OK)
    {
      printf("0x%02X ", i);
    }
  }
  printf("\r\nI2C scan complete\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // Process touch data
    if(notifyTouch == 1)
      process_touch_data();
  /* USER CODE END 3 */
  }
}


/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RIF Initialization Function
  * @param None
  * @retval None
  */
  static void SystemIsolation_Config(void)
{

  /* USER CODE BEGIN RIF_Init 0 */

  /* USER CODE END RIF_Init 0 */

  /* set all required IPs as secure privileged */
  __HAL_RCC_RIFSC_CLK_ENABLE();

  /* RIF-Aware IPs Config */

  /* set up GPIO configuration */
  HAL_GPIO_ConfigPinAttributes(GPIOC,GPIO_PIN_1,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_5,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_6,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOE,GPIO_PIN_8,GPIO_PIN_SEC|GPIO_PIN_NPRIV);
  HAL_GPIO_ConfigPinAttributes(GPIOH,GPIO_PIN_9,GPIO_PIN_SEC|GPIO_PIN_NPRIV);

  /* USER CODE BEGIN RIF_Init 1 */

  /* USER CODE END RIF_Init 1 */
  /* USER CODE BEGIN RIF_Init 2 */

  /* USER CODE END RIF_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin : PE8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI8_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI8_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

// Retarget printf to UART
#ifdef __GNUC__
// For GCC toolchain
int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}
#endif

#ifdef __ICCARM__
// For IAR toolchain  
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
#endif

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
// For Keil MDK-ARM toolchain
int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
#endif

// Alternative function-style implementation for manual printf redirection
void uart_printf(const char* format, ...)
{
    char buffer[256];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    if(len > 0)
    {
        HAL_UART_Transmit(&huart1, (uint8_t*)buffer, len, HAL_MAX_DELAY);
    }
}

// __putchar implementation for some compilers
int __putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

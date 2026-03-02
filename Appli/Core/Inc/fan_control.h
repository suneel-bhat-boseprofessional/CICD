/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : fan_control.h
  * @brief          : Header for fan_control.c file.
  *                   Fan PWM control via UART JSON commands
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
#ifndef __FAN_CONTROL_H
#define __FAN_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported defines ----------------------------------------------------------*/
#define UART_RX_BUFFER_SIZE 128
#define PWM_PERIOD 1279
#define JSON_MAX_TOKENS 16  // Maximum number of JSON tokens to parse

/* Fan speed percentages */
#define SPEED_LOW_PERCENT   30
#define SPEED_MID_PERCENT   60
#define SPEED_HIGH_PERCENT  100

/* Exported types ------------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/
extern uint8_t uart_rx_buffer[512];

/* Exported functions prototypes ---------------------------------------------*/
void FanControl_Init(TIM_HandleTypeDef *htim, UART_HandleTypeDef *huart, uint32_t tim_channel);
void FanControl_SetSpeed(uint8_t percent);
void FanControl_ProcessJSON(uint8_t *data, uint16_t length);
void FanControl_UART_RxIdleCallback(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/* Generic JSON Helper Functions ---------------------------------------------*/
/**
  * @brief  Extract string value from JSON for any key using JSMN parser
  * @param  json: JSON string (e.g., "{\"key\":\"value\"}")
  * @param  key: Key name to search for
  * @param  value_buffer: Buffer to store extracted value
  * @param  buffer_size: Size of value_buffer
  * @retval Pointer to value_buffer on success, NULL if key not found
  * 
  * @example
  *   char buffer[32];
  *   // Parse: {"mode":"AUTO","temp":"25"}
  *   if (JSON_GetStringValue(json_str, "mode", buffer, sizeof(buffer))) {
  *     printf("Mode: %s\n", buffer);  // Output: Mode: AUTO
  *   }
  *   if (JSON_GetStringValue(json_str, "temp", buffer, sizeof(buffer))) {
  *     int temp = atoi(buffer);
  *     printf("Temperature: %d\n", temp);  // Output: Temperature: 25
  *   }
  */
char* JSON_GetStringValue(const char *json, const char *key, char *value_buffer, uint16_t buffer_size);

#ifdef __cplusplus
}
#endif

#endif /* __FAN_CONTROL_H */

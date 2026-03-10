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
// Generic JSON message types and helpers
typedef enum {
  MSG_TYPE_REQUEST,
  MSG_TYPE_RESPONSE,
  MSG_TYPE_EVENT,
  MSG_TYPE_UNKNOWN
} MessageType;

typedef enum {
  STATUS_SUCCESS,
  STATUS_ERROR,
  STATUS_UNKNOWN
} MessageStatus;

typedef struct {
  int code;
  char message[64];
} ErrorInfo;

typedef struct {
  char action[32];
  char requestId[32];
  MessageType type;
  MessageStatus status;
  ErrorInfo error;
  char payload[128]; // raw JSON string of payload
} GenericMessage;

MessageType ParseMessageType(const char *typeStr);
MessageStatus ParseStatus(const char *statusStr);
int ParseGenericMessage(const char *json, GenericMessage *msg);
void JSON_ProcessMessage(uint8_t *data, uint16_t length);
void SendGenericResponse(UART_HandleTypeDef *huart, const GenericMessage *msg);
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

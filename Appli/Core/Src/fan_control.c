/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : fan_control.c
  * @brief          : Fan PWM control via UART JSON commands
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
#include "fan_control.h"
#include "json_parser.h"
#include <string.h>
#include <stdio.h>

#include <stdlib.h> // for atoi

MessageType ParseMessageType(const char *typeStr)
{
  if (strcmp(typeStr, "request") == 0) return MSG_TYPE_REQUEST;
  if (strcmp(typeStr, "response") == 0) return MSG_TYPE_RESPONSE;
  if (strcmp(typeStr, "event") == 0) return MSG_TYPE_EVENT;
  return MSG_TYPE_UNKNOWN;
}

MessageStatus ParseStatus(const char *statusStr)
{
  if (strcmp(statusStr, "success") == 0) return STATUS_SUCCESS;
  if (strcmp(statusStr, "error") == 0) return STATUS_ERROR;
  return STATUS_UNKNOWN;
}

int ParseGenericMessage(const char *json, GenericMessage *msg)
{
  char buffer[128];

  if (!JSON_GetStringValue(json, "type", buffer, sizeof(buffer))) return -1;
  msg->type = ParseMessageType(buffer);

  if (!JSON_GetStringValue(json, "action", msg->action, sizeof(msg->action))) return -1;
  if (!JSON_GetStringValue(json, "requestId", msg->requestId, sizeof(msg->requestId))) return -1;

  if (JSON_GetStringValue(json, "status", buffer, sizeof(buffer)))
    msg->status = ParseStatus(buffer);
  else
    msg->status = STATUS_UNKNOWN;

  // Parse error object if present
  char errorCode[8], errorMsg[64];
  if (JSON_GetStringValue(json, "error.code", errorCode, sizeof(errorCode)) &&
    JSON_GetStringValue(json, "error.message", errorMsg, sizeof(errorMsg)))
  {
    msg->error.code = atoi(errorCode);
    strncpy(msg->error.message, errorMsg, sizeof(msg->error.message));
  }
  else
  {
    msg->error.code = 0;
    msg->error.message[0] = '\0';
  }

  // Extract payload as raw JSON string
  if (JSON_GetStringValue(json, "payload", msg->payload, sizeof(msg->payload)) == NULL)
    msg->payload[0] = '\0';

  return 0;
}

void SendGenericResponse(UART_HandleTypeDef *huart, const GenericMessage *msg)
{
  char buffer[256];
  int len = snprintf(buffer, sizeof(buffer),
    "{\"type\":\"response\",\"action\":\"%s\",\"requestId\":\"%s\",\"status\":\"%s\",\"payload\":%s,\"error\":{\"code\":%d,\"message\":\"%s\"}}\r\n",
    msg->action,
    msg->requestId,
    msg->status == STATUS_SUCCESS ? "success" : "error",
    msg->payload[0] ? msg->payload : "{}",
    msg->error.code,
    msg->error.message
  );
  HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 100);
}

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t uart_rx_buffer[512];


// Module handles - set during initialization
static TIM_HandleTypeDef *p_htim = NULL;
static UART_HandleTypeDef *p_huart = NULL;
static uint32_t tim_pwm_channel = TIM_CHANNEL_2;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Generic JSON string value parser using JSMN
  * @param  json: Pointer to JSON string
  * @param  key: Key to search for (e.g., "speed", "command", "value")
  * @param  value_buffer: Buffer to store the extracted value
  * @param  buffer_size: Size of value_buffer
  * @retval Pointer to value_buffer on success, NULL on failure
  * @note   Extracts string values in format: {"key":"value"}
  *         Can handle multiple keys in same JSON
  *         Uses JSMN parser for robust JSON parsing
  */
char* JSON_GetStringValue(const char *json, const char *key, char *value_buffer, uint16_t buffer_size)
{
  jsmn_parser parser;
  jsmntok_t tokens[JSON_MAX_TOKENS];
  int token_count;
  int i;
  int json_len;
  
  // Check inputs
  if (json == NULL || key == NULL || value_buffer == NULL || buffer_size == 0)
    return NULL;
  
  // Initialize JSMN parser
  jsmn_init(&parser);
  
  // Parse JSON
  json_len = strlen(json);
  token_count = jsmn_parse(&parser, json, json_len, tokens, JSON_MAX_TOKENS);
  
  // Check for parsing errors
  if (token_count < 0)
    return NULL;
  
  // Search for the key in tokens
  for (i = 1; i < token_count; i++)
  {
    // Check if this token is a string (potential key)
    if (tokens[i].type == JSMN_STRING)
    {
      int key_len = tokens[i].end - tokens[i].start;
      
      // Check if this token matches our key
      if (strncmp(json + tokens[i].start, key, key_len) == 0 && 
          strlen(key) == (size_t)key_len)
      {
        // Found the key! Next token should be the value
        if (i + 1 < token_count)
        {
          jsmntok_t *value_token = &tokens[i + 1];
          int value_len = value_token->end - value_token->start;
          
          // Copy value to buffer (limit by buffer size)
          if (value_len >= (int)buffer_size)
            value_len = buffer_size - 1;
          
          strncpy(value_buffer, json + value_token->start, value_len);
          value_buffer[value_len] = '\0';
          
          return value_buffer;
        }
      }
    }
  }
  
  return NULL;
}

/**
  * @brief  Initialize fan control system
  * @param  htim: Pointer to TIM handle for PWM
  * @param  huart: Pointer to UART handle for commands
  * @param  tim_channel: TIM channel to use for PWM (e.g., TIM_CHANNEL_2)
  * @retval None
  */
void FanControl_Init(TIM_HandleTypeDef *htim, UART_HandleTypeDef *huart, uint32_t tim_channel)
{
  // Store handles for later use
  p_htim = htim;
  p_huart = huart;
  tim_pwm_channel = tim_channel;
  
  // Display welcome messages
  HAL_UART_Transmit(p_huart, (uint8_t*)"Application\r\n", 13, 100);
  HAL_UART_Transmit(p_huart, (uint8_t*)"Fan Control Ready\r\n", 19, 100);
  HAL_UART_Transmit(p_huart, (uint8_t*)"Send JSON: {\"speed\":\"LOW\"} or {\"speed\":\"MID\"} or {\"speed\":\"HIGH\"}\r\n", 68, 100);
  
  // Start PWM
  HAL_TIM_PWM_Start(p_htim, tim_pwm_channel);
  
  // Start UART receive to idle interrupt for up to 512 bytes
  HAL_UARTEx_ReceiveToIdle_IT(p_huart, uart_rx_buffer, sizeof(uart_rx_buffer));


  // Set initial fan speed to LOW
  FanControl_SetSpeed(SPEED_LOW_PERCENT);
}

/**
  * @brief  Fan Control UART RX Idle handler - Call this from HAL_UARTEx_RxEventCallback
  * @param  huart: UART handle
  * @param  pData: Pointer to received data buffer
  * @param  Size: Number of bytes received
  * @retval None
  */
void FanControl_UART_RxIdleCallback(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
{
  if (huart == p_huart && Size > 0 && Size <= sizeof(uart_rx_buffer))
  {
    // Null-terminate the received data for string processing
    if (Size < sizeof(uart_rx_buffer))
      pData[Size] = '\0';
    else
      pData[sizeof(uart_rx_buffer) - 1] = '\0';

    // Process the received JSON packet (generic handler)
    JSON_ProcessMessage(pData, Size);
  }
  // Restart UART receive to idle interrupt
  HAL_UARTEx_ReceiveToIdle_IT(p_huart, uart_rx_buffer, sizeof(uart_rx_buffer));
}

/**
  * @brief  Set PWM duty cycle based on percentage
  * @param  percent: Duty cycle percentage (0-100)
  * @retval None
  */
void FanControl_SetSpeed(uint8_t percent)
{
  uint32_t pulse_value;
  
  // Check if module is initialized
  if (p_htim == NULL || p_huart == NULL) return;
  
  // Clamp percentage to 0-100
  if (percent > 100) percent = 100;
  
  // Calculate pulse value: (PWM_PERIOD + 1) * percent / 100
  pulse_value = ((PWM_PERIOD + 1) * percent) / 100;
  
  // Update PWM duty cycle
  __HAL_TIM_SET_COMPARE(p_htim, tim_pwm_channel, pulse_value);
  
  // Send confirmation
  char msg[50];
  sprintf(msg, "Fan speed set to %d%% (Pulse: %lu)\r\n", percent, pulse_value);
  HAL_UART_Transmit(p_huart, (uint8_t*)msg, strlen(msg), 100);
}

/**
  * @brief  Process received JSON packet and control PWM
  * @param  data: Pointer to JSON string
  * @param  length: Length of JSON string
  * @retval None
  * @note   JSON format: {"speed":"LOW"} or {"speed":"MID"} or {"speed":"HIGH"}
  *         Can be extended to support more commands by checking different keys
  */

void JSON_ProcessMessage(uint8_t *data, uint16_t length)
{
    GenericMessage msg;
    if (ParseGenericMessage((char*)data, &msg) != 0)
    {
        HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Invalid JSON\r\n", 21, 100);
        return;
    }

    switch (msg.type)
    {
        case MSG_TYPE_REQUEST:
            // Example: handle fan control request
            if (strcmp(msg.action, "setFanSpeed") == 0)
            {
                char speed[16];
                if (JSON_GetStringValue(msg.payload, "speed", speed, sizeof(speed)))
                {
                    if (strcmp(speed, "LOW") == 0)
                        FanControl_SetSpeed(SPEED_LOW_PERCENT);
                    else if (strcmp(speed, "MID") == 0)
                        FanControl_SetSpeed(SPEED_MID_PERCENT);
                    else if (strcmp(speed, "HIGH") == 0)
                        FanControl_SetSpeed(SPEED_HIGH_PERCENT);
                    else
                        HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Invalid speed value\r\n", 29, 100);
                }
                else
                {
                    HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Missing speed\r\n", 22, 100);
                }
            }
            // Add more actions here
            break;
        case MSG_TYPE_RESPONSE:
            // Handle response
            break;
        case MSG_TYPE_EVENT:
            // Handle event
            break;
        default:
            HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Unknown type\r\n", 21, 100);
            break;
    }
}



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

    // Process the received JSON packet
    FanControl_ProcessJSON(pData, Size);
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
void FanControl_ProcessJSON(uint8_t *data, uint16_t length)
{
  char value[16];
  
  // Check if module is initialized
  if (p_huart == NULL) return;
  
  // Try to extract "speed" command
  if (JSON_GetStringValue((char*)data, "speed", value, sizeof(value)) != NULL)
  {
    // Process speed command
    if (strcmp(value, "LOW") == 0)
    {
      FanControl_SetSpeed(SPEED_LOW_PERCENT);
    }
    else if (strcmp(value, "MID") == 0)
    {
      FanControl_SetSpeed(SPEED_MID_PERCENT);
    }
    else if (strcmp(value, "HIGH") == 0)
    {
      FanControl_SetSpeed(SPEED_HIGH_PERCENT);
    }
    else
    {
      HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Invalid speed value\r\n", 29, 100);
    }
  }
  // Future: Add more command handlers here
  // Example: else if (JSON_GetStringValue((char*)data, "mode", value, sizeof(value)) != NULL)
  // {
  //   // Handle mode command
  // }
  else
  {
    HAL_UART_Transmit(p_huart, (uint8_t*)"Error: Unknown command or invalid JSON\r\n", 41, 100);
  }
}



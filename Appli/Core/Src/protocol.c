/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : protocol.c
  * @brief          : UART JSON protocol handler
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
#include <protocol.h>
#include "json_parser.h"
#include <string.h>
#include <stdio.h>

extern void set_zone_name_c(int idx, const char* name);
extern void set_zone_count_c(int count);
extern int get_zone_count_c(void);
extern void set_zone_volume_c(int idx, int value);
extern void set_zone_muted_c(int idx, int muted);

#include <stdlib.h> // for atoi, atof

// Fix: Add FreeRTOS includes for QueueHandle_t and queue APIs
#include "FreeRTOS.h"
#include "queue.h"

int ParseGenericMessage(const char *json, GenericMessage *msg)
{
  if (json == NULL || msg == NULL) return -1;

  if (!JSON_GetStringValue(json, "action", msg->action, sizeof(msg->action))) return -1;

  // Extract payload as raw JSON string
  if (JSON_GetStringValue(json, "payload", msg->payload, sizeof(msg->payload)) == NULL)
    msg->payload[0] = '\0';

  return 0;
}


// Send NACK (failure) message only
void SendNack(UART_HandleTypeDef *huart, const char *failedAction, const char *errorMsg, int index) {
  (void)errorMsg;
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer),
        "{\"action\":\"nack\",\"payload\":{\"error\":\"%s\",\"index\":%d}}\r\n",
        failedAction, index);
    HAL_UART_Transmit(huart, (uint8_t*)buffer, len, 100);
}

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];


// Module handles - set during initialization
static TIM_HandleTypeDef *p_htim = NULL;
static UART_HandleTypeDef *p_huart = NULL;
static uint32_t tim_pwm_channel = TIM_CHANNEL_2;

/* Private function prototypes -----------------------------------------------*/
static void HandleSetFanSpeed(const GenericMessage *msg);
static void HandleIdentity(const GenericMessage *msg);
static void HandleZone(const GenericMessage *msg);
static void HandleZoneEnd(const GenericMessage *msg);
static void HandleSetGain(const GenericMessage *msg);
static void HandleSetMute(const GenericMessage *msg);

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

static char* JSON_GetObjectChildValue(const char *json,
                                      const char *objectKey,
                                      const char *childKey,
                                      char *value_buffer,
                                      uint16_t buffer_size)
{
  jsmn_parser parser;
  jsmntok_t tokens[JSON_MAX_TOKENS];
  int token_count;
  int i;

  if (json == NULL || objectKey == NULL || childKey == NULL || value_buffer == NULL || buffer_size == 0)
    return NULL;

  jsmn_init(&parser);
  token_count = jsmn_parse(&parser, json, strlen(json), tokens, JSON_MAX_TOKENS);
  if (token_count < 0)
    return NULL;

  for (i = 1; i < token_count - 1; i++)
  {
    if (tokens[i].type == JSMN_STRING)
    {
      int obj_key_len = tokens[i].end - tokens[i].start;
      if ((int)strlen(objectKey) == obj_key_len &&
          strncmp(json + tokens[i].start, objectKey, obj_key_len) == 0)
      {
        jsmntok_t *obj = &tokens[i + 1];
        int j;

        if (obj->type != JSMN_OBJECT)
          return NULL;

        for (j = i + 2; j < token_count - 1 && tokens[j].start < obj->end; j++)
        {
          if (tokens[j].type == JSMN_STRING)
          {
            int child_key_len = tokens[j].end - tokens[j].start;
            if ((int)strlen(childKey) == child_key_len &&
                strncmp(json + tokens[j].start, childKey, child_key_len) == 0)
            {
              jsmntok_t *value_token = &tokens[j + 1];
              int value_len = value_token->end - value_token->start;

              if (value_len >= (int)buffer_size)
                value_len = buffer_size - 1;

              strncpy(value_buffer, json + value_token->start, value_len);
              value_buffer[value_len] = '\0';
              return value_buffer;
            }
          }
        }
        return NULL;
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

    // Only enqueue the received message to the queue for processing in the default task
    extern QueueHandle_t uartRxQueue;
    if (uartRxQueue != NULL)
    {
      // Ensure null-termination for string processing in the task
      size_t msg_len = strlen((char*)pData);
      if (msg_len > 0 && msg_len < sizeof(uart_rx_buffer))
      {
        xQueueSend(uartRxQueue, pData, 0);
      }
    }
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
}

static void HandleSetFanSpeed(const GenericMessage *msg)
{
  char speed[16];

  if (JSON_GetStringValue(msg->payload, "speed", speed, sizeof(speed)))
  {
    if (strcmp(speed, "LOW") == 0)
      FanControl_SetSpeed(SPEED_LOW_PERCENT);
    else if (strcmp(speed, "MID") == 0)
      FanControl_SetSpeed(SPEED_MID_PERCENT);
    else if (strcmp(speed, "HIGH") == 0)
      FanControl_SetSpeed(SPEED_HIGH_PERCENT);
    else
      SendNack(p_huart, "setFanSpeed", "INVALID SPEED", -1);
  }
  else
  {
    SendNack(p_huart, "setFanSpeed", "MISSING SPEED", -1);
  }
}

static void HandleIdentity(const GenericMessage *msg)
{
  char tmp[32];

  if (!JSON_GetStringValue(msg->payload, "Id", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.ID", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Serial", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.SERIAL", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Version", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.VERSION", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Mac", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.MAC", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Ip", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.IP", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "IpMask", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.IPMASK", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Gateway", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.GATEWAY", -1);
    return;
  }
  if (!JSON_GetStringValue(msg->payload, "Dhcp", tmp, sizeof(tmp))) {
    SendNack(p_huart, "identity", "MISSING IDENTITY.DHCP", -1);
    return;
  }
}

static void HandleZone(const GenericMessage *msg)
{
  char indexBuf[12];
  char nameBuf[64];
  char gainBuf[12];
  char muteBuf[8];
  int zoneIndex;

  if (!JSON_GetStringValue(msg->payload, "Index", indexBuf, sizeof(indexBuf))) {
    SendNack(p_huart, "zone", "MISSING ZONE.INDEX", -1);
    return;
  }

  zoneIndex = atoi(indexBuf);
  if (zoneIndex < 0) {
    SendNack(p_huart, "zone", "INVALID ZONE.INDEX", zoneIndex);
    return;
  }

  if (!JSON_GetStringValue(msg->payload, "Name", nameBuf, sizeof(nameBuf))) {
    SendNack(p_huart, "zone", "MISSING ZONE.NAME", zoneIndex);
    return;
  }

  // Apply one-by-one zone update and grow the visible zone count.
  set_zone_name_c(zoneIndex, nameBuf);
  if ((zoneIndex + 1) > get_zone_count_c()) {
    set_zone_count_c(zoneIndex + 1);
  }

  if (JSON_GetObjectChildValue(msg->payload, "Gain", "DefMute", muteBuf, sizeof(muteBuf))) {
    int muted = (strcmp(muteBuf, "true") == 0 || strcmp(muteBuf, "1") == 0) ? 1 : 0;
    set_zone_muted_c(zoneIndex, muted);
  }

  if (JSON_GetObjectChildValue(msg->payload, "Gain", "DefGain", gainBuf, sizeof(gainBuf))) {
    set_zone_volume_c(zoneIndex, atoi(gainBuf));
  }

  // sources[] is accepted in payload for future UI binding.
}

static void HandleZoneEnd(const GenericMessage *msg)
{
  char zonesBuf[12];
  int expectedZones;
  int currentZones;
  const char *ackMsg = "{\"action\":\"zoneEndAck\"}\r\n";
  const char *nackMsg = "{\"action\":\"zoneEndNack\"}\r\n";

  if (!JSON_GetStringValue(msg->payload, "zones", zonesBuf, sizeof(zonesBuf))) {
    HAL_UART_Transmit(p_huart, (uint8_t*)nackMsg, strlen(nackMsg), 100);
    return;
  }

  expectedZones = atoi(zonesBuf);
  if (expectedZones < 0) {
    expectedZones = 0;
  }

  currentZones = get_zone_count_c();

  if (currentZones == expectedZones) {
    HAL_UART_Transmit(p_huart, (uint8_t*)ackMsg, strlen(ackMsg), 100);
  } else {
    HAL_UART_Transmit(p_huart, (uint8_t*)nackMsg, strlen(nackMsg), 100);
  }
}

static void HandleSetGain(const GenericMessage *msg)
{
  char zoneBuf[12];
  char normBuf[24];
  char dbBuf[24];
  int  zoneIndex;

  if (!JSON_GetStringValue(msg->payload, "zone", zoneBuf, sizeof(zoneBuf))) {
    SendNack(p_huart, "setGain", "MISSING GAIN.ZONE", -1);
    return;
  }

  zoneIndex = atoi(zoneBuf);
  if (zoneIndex < 0 || zoneIndex >= get_zone_count_c()) {
    SendNack(p_huart, "setGain", "INVALID GAIN.ZONE", zoneIndex);
    return;
  }

  // norm is a direct volume value (0-100); round to nearest integer and clamp
  if (JSON_GetStringValue(msg->payload, "norm", normBuf, sizeof(normBuf))) {
    float norm = (float)atof(normBuf);
    if (norm < 0.0f)   norm = 0.0f;
    if (norm > 100.0f) norm = 100.0f;
    set_zone_volume_c(zoneIndex, (int)(norm + 0.5f));
  } else if (JSON_GetStringValue(msg->payload, "db", dbBuf, sizeof(dbBuf))) {
    // Store dB value directly as volume integer (caller responsibility)
    set_zone_volume_c(zoneIndex, (int)(atof(dbBuf) + 0.5f));
  } else {
    SendNack(p_huart, "setGain", "MISSING GAIN.NORM OR GAIN.DB", zoneIndex);
    return;
  }
}

static void HandleSetMute(const GenericMessage *msg)
{
  char zoneBuf[12];
  char stateBuf[8];
  int  zoneIndex;

  if (!JSON_GetStringValue(msg->payload, "zone", zoneBuf, sizeof(zoneBuf))) {
    SendNack(p_huart, "setMute", "MISSING MUTE.ZONE", -1);
    return;
  }

  zoneIndex = atoi(zoneBuf);
  if (zoneIndex < 0 || zoneIndex >= get_zone_count_c()) {
    SendNack(p_huart, "setMute", "INVALID MUTE.ZONE", zoneIndex);
    return;
  }

  if (!JSON_GetStringValue(msg->payload, "state", stateBuf, sizeof(stateBuf))) {
    SendNack(p_huart, "setMute", "MISSING MUTE.STATE", zoneIndex);
    return;
  }

  set_zone_muted_c(zoneIndex, (strcmp(stateBuf, "true") == 0 || strcmp(stateBuf, "1") == 0) ? 1 : 0);
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
  (void)length;
  GenericMessage msg;

  if (ParseGenericMessage((char*)data, &msg) != 0)
  {
    SendNack(p_huart, "parse", "INVALID PACKET", -1);
    return;
  }

  if (strcmp(msg.action, "setFanSpeed") == 0) {
    HandleSetFanSpeed(&msg);
    return;
  }

  if (strcmp(msg.action, "identity") == 0) {
    HandleIdentity(&msg);
    return;
  }

  if (strcmp(msg.action, "zone") == 0) {
    HandleZone(&msg);
    return;
  }

  if (strcmp(msg.action, "zoneEnd") == 0) {
    HandleZoneEnd(&msg);
    return;
  }

  if (strcmp(msg.action, "setGain") == 0) {
    HandleSetGain(&msg);
    return;
  }

  if (strcmp(msg.action, "setMute") == 0) {
    HandleSetMute(&msg);
    return;
  }

  SendNack(p_huart, msg.action, "FAILED ACTION", -1);
}

void Protocol_SendSetGain(int zone, int norm)
{
  char buffer[128];
  int len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setGain\",\"payload\":{\"zone\":%d,\"db\":0.0,\"norm\":%d}}\r\n",
      zone, norm);
  HAL_UART_Transmit(p_huart, (uint8_t*)buffer, len, 100);
}

void Protocol_SendSetMute(int zone, int state)
{
  char buffer[96];
  int len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setMute\",\"payload\":{\"zone\":%d,\"state\":%s}}\r\n",
      zone, state ? "true" : "false");
  HAL_UART_Transmit(p_huart, (uint8_t*)buffer, len, 100);
}



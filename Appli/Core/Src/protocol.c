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
#include "firmware_updater.h"
#include "ram_functions.h"
#include <string.h>
#include <stdio.h>

extern void set_zone_name_c(int idx, const char* name);
extern void set_zone_count_c(int count);
extern int get_zone_count_c(void);
extern void set_zone_volume_c(int idx, int value);
extern void set_zone_muted_c(int idx, int muted);
extern void set_zone_source_count_c(int zoneIdx, int count);
extern int get_zone_source_count_c(int zoneIdx);
extern void set_zone_source_name_c(int zoneIdx, int srcIdx, const char* name);
extern void set_selected_source_c(int zoneIdx, int srcIdx);
extern void set_ready_received_c(void);
extern void set_go_to_launch_c(void);
extern void set_lcd_brightness_c(int value);

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


/* Forward declaration for framed send helper */
static void Protocol_SendFramed(const char *json, uint16_t jsonLen);

// Send NACK (failure) message only
void SendNack(UART_HandleTypeDef *huart, const char *failedAction, const char *errorMsg, int index) {
  (void)errorMsg;
  (void)huart;
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer),
        "{\"action\":\"nack\",\"payload\":{\"error\":\"%s\",\"index\":%d}}",
        failedAction, index);
    Protocol_SendFramed(buffer, len);
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

/* TUII Packet Framing -------------------------------------------------------*/

/**
  * @brief  Send a JSON string wrapped in a TUII Normal frame over UART
  * @param  json: Pointer to JSON payload string
  * @param  jsonLen: Length of JSON payload
  * @retval None
  */
static void Protocol_SendFramed(const char *json, uint16_t jsonLen)
{
  uint8_t pktBuf[PROTOCOL_MAX_PACKET];
  int pktLen;

  if (jsonLen > PROTOCOL_MAX_PAYLOAD) jsonLen = PROTOCOL_MAX_PAYLOAD;

  pktLen = Protocol_BuildPacket(PACKET_TYPE_NORMAL, (const uint8_t*)json, (uint8_t)jsonLen, pktBuf, sizeof(pktBuf));
  if (pktLen > 0)
    HAL_UART_Transmit(p_huart, pktBuf, (uint16_t)pktLen, 200);
}

/**
  * @brief  CRC16-CCITT-FALSE calculation
  * @param  data: Pointer to data buffer
  * @param  length: Number of bytes
  * @retval CRC16 value
  */
uint16_t Protocol_CRC16_CCITT(uint8_t *data, uint16_t length)
{
  uint16_t crc = PROTOCOL_CRC_INITIAL;

  for (uint16_t i = 0; i < length; i++)
  {
    crc ^= (uint16_t)data[i] << 8;
    for (uint8_t j = 0; j < 8; j++)
    {
      if (crc & PROTOCOL_CRC_MSB_MASK)
        crc = (crc << 1) ^ PROTOCOL_CRC_POLYNOMIAL;
      else
        crc <<= 1;
    }
  }

  return crc;
}

/**
  * @brief  Build a TUII framed packet from a payload
  * @param  type: Packet type (PACKET_TYPE_OTA or PACKET_TYPE_NORMAL)
  * @param  payload: Pointer to payload data (e.g. JSON string)
  * @param  payloadLen: Length of payload (max 255)
  * @param  outBuf: Output buffer (must be at least PROTOCOL_HEADER_SIZE + payloadLen)
  * @param  outBufSize: Size of outBuf
  * @retval Total packet length on success, -1 on error
  *
  * Packet layout:
  *   | SOF (4B) | CRC16_LO CRC16_HI (2B) | LEN (1B) | Payload (LEN bytes) |
  *   CRC is computed over LEN + Payload bytes.
  */
int Protocol_BuildPacket(PacketType_t type, const uint8_t *payload, uint8_t payloadLen, uint8_t *outBuf, uint16_t outBufSize)
{
  uint16_t totalLen = PROTOCOL_HEADER_SIZE + payloadLen;
  uint16_t crc;

  if (payload == NULL || outBuf == NULL)
    return -1;
  if (totalLen > outBufSize)
    return -1;

  /* SOF based on packet type */
  switch (type)
  {
    case PACKET_TYPE_OTA:
      outBuf[0] = PROTOCOL_SOF_OTA_BYTE0;
      outBuf[1] = PROTOCOL_SOF_OTA_BYTE1;
      outBuf[2] = PROTOCOL_SOF_OTA_BYTE2;
      outBuf[3] = PROTOCOL_SOF_OTA_BYTE3;
      break;
    case PACKET_TYPE_NORMAL:
      outBuf[0] = PROTOCOL_SOF_NORM_BYTE3;
      outBuf[1] = PROTOCOL_SOF_NORM_BYTE2;
      outBuf[2] = PROTOCOL_SOF_NORM_BYTE1;
      outBuf[3] = PROTOCOL_SOF_NORM_BYTE0;
      break;
    default:
      return -1;
  }

  /* LEN */
  outBuf[6] = payloadLen;

  /* Copy payload after header */
  memcpy(&outBuf[PROTOCOL_HEADER_SIZE], payload, payloadLen);

  /* CRC16 over LEN + Payload (starts at outBuf[6]) */
  crc = Protocol_CRC16_CCITT(&outBuf[6], 1 + payloadLen);

  /* CRC (little-endian) */
  outBuf[4] = (uint8_t)(crc & 0xFF);         /* CRC16_LO */
  outBuf[5] = (uint8_t)((crc >> 8) & 0xFF);  /* CRC16_HI */

  return (int)totalLen;
}

/**
  * @brief  Parse and validate a TUII framed packet
  * @param  packet: Pointer to raw received packet
  * @param  packetLen: Length of raw data
  * @param  payloadOut: Buffer to receive the extracted payload
  * @param  payloadLenOut: Pointer to receive the payload length
  * @param  packetType: Pointer to receive detected packet type (OTA or NORMAL)
  * @retval 0 on success, -1 on invalid/unknown SOF, -2 on CRC mismatch, -3 on length error
  */
int Protocol_ParsePacket(const uint8_t *packet, uint16_t packetLen, uint8_t *payloadOut, uint8_t *payloadLenOut, PacketType_t *packetType)
{
  uint16_t crcReceived, crcComputed;
  uint8_t len;

  if (packet == NULL || payloadOut == NULL || payloadLenOut == NULL || packetType == NULL)
    return -3;

  *packetType = PACKET_TYPE_UNKNOWN;

  /* Minimum packet is header only (7 bytes) */
  if (packetLen < PROTOCOL_HEADER_SIZE)
    return -3;

  /* Detect SOF type */
  if (packet[0] == PROTOCOL_SOF_OTA_BYTE0 &&
      packet[1] == PROTOCOL_SOF_OTA_BYTE1 &&
      packet[2] == PROTOCOL_SOF_OTA_BYTE2 &&
      packet[3] == PROTOCOL_SOF_OTA_BYTE3)
  {
    *packetType = PACKET_TYPE_OTA;
  }
  else if (packet[0] == PROTOCOL_SOF_NORM_BYTE3 &&
           packet[1] == PROTOCOL_SOF_NORM_BYTE2 &&
           packet[2] == PROTOCOL_SOF_NORM_BYTE1 &&
           packet[3] == PROTOCOL_SOF_NORM_BYTE0)
  {
    *packetType = PACKET_TYPE_NORMAL;
  }
  else
  {
    return -1;  /* Unknown SOF */
  }

  /* Extract CRC (little-endian) */
  crcReceived = (uint16_t)packet[4] | ((uint16_t)packet[5] << 8);

  /* Extract LEN */
  len = packet[6];

  /* Validate total length */
  if ((PROTOCOL_HEADER_SIZE + len) > packetLen)
    return -3;

  /* Compute CRC over LEN + Payload */
  crcComputed = Protocol_CRC16_CCITT((uint8_t *)&packet[6], 1 + len);

  if (crcComputed != crcReceived)
    return -2;

  /* Copy payload out */
  memcpy(payloadOut, &packet[PROTOCOL_HEADER_SIZE], len);
  *payloadLenOut = len;

  return 0;
}

/**
  * @brief  Top-level handler: parse framed packet and route by SOF type
  *         - OTA SOF (0xA1B1C1D1) -> OTA handler
  *         - Normal SOF (0xA2B2C2D2) -> JSON payload processing
  * @param  data: Pointer to raw received packet (header + payload)
  * @param  length: Total number of bytes received
  * @retval None
  */
void Protocol_ProcessReceivedData(uint8_t *data, uint16_t length)
{
  /* Route OTA binary packets first — LE SOF: D1 C1 B1 A1 */
  if (length >= OTA_REQUEST_MIN_SIZE &&
      data[0] == OTA_SOF_REQ_BYTE0 &&
      data[1] == OTA_SOF_REQ_BYTE1 &&
      data[2] == OTA_SOF_REQ_BYTE2 &&
      data[3] == OTA_SOF_REQ_BYTE3)
  {
    OTA_ProcessBinaryCommand(data, length);
    return;
  }

  /* Existing normal protocol path */
  uint8_t payload[PROTOCOL_MAX_PAYLOAD];
  uint8_t payloadLen = 0;
  PacketType_t type;
  int result;

  result = Protocol_ParsePacket(data, length, payload, &payloadLen, &type);

  if (result == -1)
  {
    /* Unknown / invalid SOF */
    SendNack(p_huart, "packet", "INVALID SOF", result);
    return;
  }
  if (result == -2)
  {
    /* CRC mismatch */
    SendNack(p_huart, "packet", "CRC MISMATCH", result);
    return;
  }
  if (result == -3)
  {
    /* Length error */
    SendNack(p_huart, "packet", "LENGTH ERROR", result);
    return;
  }

  switch (type)
  {
    case PACKET_TYPE_OTA:
      /* Should not reach here — OTA is handled above before ParsePacket */
      break;

    case PACKET_TYPE_NORMAL:
      /* Null-terminate for JSON string processing */
      if (payloadLen < PROTOCOL_MAX_PAYLOAD)
        payload[payloadLen] = '\0';
      else
        payload[PROTOCOL_MAX_PAYLOAD - 1] = '\0';
      JSON_ProcessMessage(payload, payloadLen);
      break;

    default:
      SendNack(p_huart, "packet", "UNKNOWN TYPE", -1);
      break;
  }
}


/* Private function prototypes -----------------------------------------------*/
static void HandleSetFanSpeed(const GenericMessage *msg);
static void HandleIdentity(const GenericMessage *msg);
static void HandleZone(const GenericMessage *msg);
static void HandleZoneEnd(const GenericMessage *msg);
static void HandleSetGain(const GenericMessage *msg);
static void HandleSetMute(const GenericMessage *msg);
static void HandleSetSource(const GenericMessage *msg);
static void HandleSetBrightness(const GenericMessage *msg);
static void HandleReady(const GenericMessage *msg);
static void HandleNack(const GenericMessage *msg);

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
  //HAL_UART_Transmit(p_huart, (uint8_t*)"Application\r\n", 13, 100);

  // Start PWM
  HAL_TIM_PWM_Start(p_htim, tim_pwm_channel);
  
  // Start UART receive to idle interrupt for up to 512 bytes
  HAL_UARTEx_ReceiveToIdle_IT(p_huart, uart_rx_buffer, sizeof(uart_rx_buffer));


  // Set initial fan speed to LOW
  FanControl_SetSpeed(SPEED_LOW_PERCENT);

  // Send readyAck on powerup, same as when we receive a ready message
  const char *ack = "{\"action\":\"readyAck\"}";
  Protocol_SendFramed(ack, strlen(ack));
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
  if (huart == p_huart && Size > 0 && Size <= (sizeof(uart_rx_buffer) - 2))
  {
    // Prepend actual size (2 bytes, little-endian) so the receiver knows
    // the true length without relying on strlen (binary packets may contain 0x00)
    uint8_t txBuf[UART_RX_BUFFER_SIZE];
    txBuf[0] = (uint8_t)(Size & 0xFF);
    txBuf[1] = (uint8_t)((Size >> 8) & 0xFF);
    memcpy(&txBuf[2], pData, Size);

    // Only enqueue the received message to the queue for processing in the default task
    extern QueueHandle_t uartRxQueue;
    if (uartRxQueue != NULL)
    {
      xQueueSend(uartRxQueue, txBuf, 0);
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
    const char *nackMsg = "{\"action\":\"zoneEndNack\"}";
    Protocol_SendFramed(nackMsg, strlen(nackMsg));
    set_zone_count_c(0);
    set_go_to_launch_c();
    return;
  }

  zoneIndex = atoi(indexBuf);
  if (zoneIndex < 0) {
    const char *nackMsg = "{\"action\":\"zoneEndNack\"}";
    Protocol_SendFramed(nackMsg, strlen(nackMsg));
    set_zone_count_c(0);
    set_go_to_launch_c();
    return;
  }

  if (!JSON_GetStringValue(msg->payload, "Name", nameBuf, sizeof(nameBuf))) {
    const char *nackMsg = "{\"action\":\"zoneEndNack\"}";
    Protocol_SendFramed(nackMsg, strlen(nackMsg));
    set_zone_count_c(0);
    set_go_to_launch_c();
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

  /* Parse sources[] array if present */
  {
    jsmn_parser srcParser;
    jsmntok_t srcTokens[JSON_MAX_TOKENS];
    int numTokens, i;

    jsmn_init(&srcParser);
    numTokens = jsmn_parse(&srcParser, msg->payload, strlen(msg->payload), srcTokens, JSON_MAX_TOKENS);

    for (i = 1; i < numTokens; i++) {
      if (srcTokens[i].type == JSMN_STRING &&
          (srcTokens[i].end - srcTokens[i].start) == 7 &&
          strncmp(msg->payload + srcTokens[i].start, "sources", 7) == 0) {
        int arrTok = i + 1;
        if (arrTok < numTokens && srcTokens[arrTok].type == JSMN_ARRAY) {
          int srcCount = srcTokens[arrTok].size;
          int si, ti = arrTok + 1;
          if (srcCount > 8) srcCount = 8;
          /* Write all source names BEFORE setting the count,
             so the UI never sees a non-zero count with empty names */
          for (si = 0; si < srcCount && ti < numTokens; si++, ti++) {
            int len = srcTokens[ti].end - srcTokens[ti].start;
            char srcBuf[32];
            if (len > 31) len = 31;
            strncpy(srcBuf, msg->payload + srcTokens[ti].start, len);
            srcBuf[len] = '\0';
            set_zone_source_name_c(zoneIndex, si, srcBuf);
          }
          set_zone_source_count_c(zoneIndex, srcCount);
        }
        break;
      }
    }
  }
}

static void HandleZoneEnd(const GenericMessage *msg)
{
  char zonesBuf[12];
  int expectedZones;
  int currentZones;
  const char *ackMsg = "{\"action\":\"zoneEndAck\"}";
  const char *nackMsg = "{\"action\":\"zoneEndNack\"}";

  if (!JSON_GetStringValue(msg->payload, "zones", zonesBuf, sizeof(zonesBuf))) {
    Protocol_SendFramed(nackMsg, strlen(nackMsg));
    return;
  }

  expectedZones = atoi(zonesBuf);
  if (expectedZones < 0) {
    expectedZones = 0;
  }

  currentZones = get_zone_count_c();

  if (currentZones == expectedZones) {
    Protocol_SendFramed(ackMsg, strlen(ackMsg));
  } else {
    Protocol_SendFramed(nackMsg, strlen(nackMsg));
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

static void HandleSetSource(const GenericMessage *msg)
{
  char zoneBuf[12];
  char indexBuf[12];
  int zoneIndex;
  int sourceIndex;
  int sourceCount;

  if (!JSON_GetStringValue(msg->payload, "zone", zoneBuf, sizeof(zoneBuf))) {
    SendNack(p_huart, "setSource", "MISSING SOURCE.ZONE", -1);
    return;
  }

  zoneIndex = atoi(zoneBuf);
  if (zoneIndex < 0 || zoneIndex >= get_zone_count_c()) {
    SendNack(p_huart, "setSource", "INVALID SOURCE.ZONE", zoneIndex);
    return;
  }

  if (!JSON_GetStringValue(msg->payload, "index", indexBuf, sizeof(indexBuf))) {
    SendNack(p_huart, "setSource", "MISSING SOURCE.INDEX", zoneIndex);
    return;
  }

  sourceIndex = atoi(indexBuf);
  sourceCount = get_zone_source_count_c(zoneIndex);
  if (sourceIndex < 0 || sourceIndex >= sourceCount) {
    SendNack(p_huart, "setSource", "INVALID SOURCE.INDEX", zoneIndex);
    return;
  }

  set_selected_source_c(zoneIndex, sourceIndex);
}

static void HandleSetBrightness(const GenericMessage *msg)
{
  char valueBuf[12];
  int value;

  if (!JSON_GetStringValue(msg->payload, "value", valueBuf, sizeof(valueBuf))) {
    SendNack(p_huart, "setBrightness", "MISSING BRIGHTNESS.VALUE", -1);
    return;
  }

  value = atoi(valueBuf);
  if (value < BRIGHTNESS_MIN || value > BRIGHTNESS_MAX) {
    SendNack(p_huart, "setBrightness", "INVALID BRIGHTNESS.VALUE", -1);
    return;
  }

  set_lcd_brightness_c(value);
}

static void HandleReady(const GenericMessage *msg)
{
  (void)msg;
  const char *ack = "{\"action\":\"readyAck\"}";
  set_zone_count_c(0);
  Protocol_SendFramed(ack, strlen(ack));
  set_ready_received_c();
}

static void HandleNack(const GenericMessage *msg)
{
  (void)msg;
  set_zone_count_c(0);
  set_go_to_launch_c();
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

  if (strcmp(msg.action, "ready") == 0) {
    HandleReady(&msg);
    return;
  }

  if (strcmp(msg.action, "nack") == 0) {
    HandleNack(&msg);
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

  if (strcmp(msg.action, "setSource") == 0) {
    HandleSetSource(&msg);
    return;
  }

  if (strcmp(msg.action, "setBrightness") == 0) {
    HandleSetBrightness(&msg);
    return;
  }

  if (strcmp(msg.action, "otarequest") == 0) {
    // OTA implementation function call here
    return;
  }

  SendNack(p_huart, msg.action, "FAILED ACTION", -1);
}

void Protocol_SendSetGain(int zone, int norm)
{
  char buffer[128];
  int len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setGain\",\"payload\":{\"zone\":%d,\"db\":0.0,\"norm\":%d}}",
      zone, norm);
  Protocol_SendFramed(buffer, len);
}

void Protocol_SendSetMute(int zone, int state)
{
  char buffer[96];
  int len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setMute\",\"payload\":{\"zone\":%d,\"state\":%s}}",
      zone, state ? "true" : "false");
  Protocol_SendFramed(buffer, len);
}

void Protocol_SendSetSource(int zone, int index)
{
  char buffer[96];
  int len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setSource\",\"payload\":{\"zone\":%d,\"index\":%d}}",
      zone, index);
  Protocol_SendFramed(buffer, len);
}

void Protocol_SendSetBrightness(int value)
{
  char buffer[80];
  int len;

  if (value < BRIGHTNESS_MIN) value = BRIGHTNESS_MIN;
  if (value > BRIGHTNESS_MAX) value = BRIGHTNESS_MAX;

  len = snprintf(buffer, sizeof(buffer),
      "{\"action\":\"setBrightness\",\"payload\":{\"value\":%d}}",
      value);
  Protocol_SendFramed(buffer, len);
}


/* OTA Binary Protocol -------------------------------------------------------*/

/**
  * @brief  Send an OTA binary response frame
  *         Response: | SOF(4) | CMD(1) | STATUS(1) | LEN_LO(1) LEN_HI(1) | Payload(LEN) | CRC16_LO(1) CRC16_HI(1) |
  *         All multi-byte fields are little-endian. Uses Normal SOF (A2B2C2D2) for responses
  * @param  cmd: Command ID being responded to
  * @param  status: OTA_STATUS_OK or OTA_STATUS_ERROR
  * @param  payload: Pointer to response payload (can be NULL if payloadLen == 0)
  * @param  payloadLen: Length of payload
  * @retval None
  */
static void OTA_SendResponse(uint8_t cmd, uint8_t status,
                             const uint8_t *payload, uint16_t payloadLen)
{
  uint8_t buf[64];
  uint16_t idx = 0;
  uint16_t crc;

  /* SOF — OTA response SOF, little-endian: D2 C2 B2 A2 */
  buf[idx++] = OTA_SOF_RSP_BYTE0;
  buf[idx++] = OTA_SOF_RSP_BYTE1;
  buf[idx++] = OTA_SOF_RSP_BYTE2;
  buf[idx++] = OTA_SOF_RSP_BYTE3;

  /* CMD */
  buf[idx++] = cmd;

  /* STATUS */
  buf[idx++] = status;

  /* LEN (2 bytes, little-endian) */
  buf[idx++] = (uint8_t)(payloadLen & 0xFF);
  buf[idx++] = (uint8_t)((payloadLen >> 8) & 0xFF);

  /* Payload */
  if (payload != NULL && payloadLen > 0)
  {
    if (payloadLen > (sizeof(buf) - idx - PROTOCOL_CRC_SIZE))
      return;  /* overflow guard */
    memcpy(&buf[idx], payload, payloadLen);
  }
  idx += payloadLen;

  /* CRC16 over everything after SOF (CMD + STATUS + LEN + Payload) */
  crc = Protocol_CRC16_CCITT(&buf[4], idx - 4);
  buf[idx++] = (uint8_t)(crc & 0xFF);
  buf[idx++] = (uint8_t)((crc >> 8) & 0xFF);

  HAL_UART_Transmit(p_huart, buf, idx, 200);
}

/**
  * @brief  Process an OTA binary command received with OTA SOF (0xA1B1C1D1)
  *         Request: | SOF(4) | CMD(1) | LEN_LO(1) LEN_HI(1) | CRC16_LO(1) CRC16_HI(1) | Payload(LEN) |
  * @param  data: Pointer to raw received data including SOF
  * @param  length: Total number of bytes received
  * @retval None
  */
void OTA_ProcessBinaryCommand(uint8_t *data, uint16_t length)
{
  if (length < OTA_REQUEST_MIN_SIZE)
    return;

  uint8_t cmd = data[4];
  uint16_t payloadLen = (uint16_t)data[5] | ((uint16_t)data[6] << 8);

  /* CRC sits right after LEN when payloadLen == 0, or after payload */
  uint16_t crcOffset = 7 + payloadLen;
  if ((crcOffset + PROTOCOL_CRC_SIZE) > length)
    return;  /* truncated packet */

  uint16_t crcReceived = (uint16_t)data[crcOffset] | ((uint16_t)data[crcOffset + 1] << 8);
  /* CRC over CMD(1) + LEN(2) + Payload(payloadLen) */
  uint16_t crcComputed = Protocol_CRC16_CCITT(&data[4], 3 + payloadLen);
  if (crcComputed != crcReceived)
    return;  /* CRC mismatch — silently drop */

  switch (cmd)
  {
    case OTA_CMD_IDENTIFY:
    {
      OTA_IdentifyResponse_t resp;
      resp.mode      = OTA_MODE_APPLICATION;
      resp.version   = ((uint32_t)FW_VERSION_MAJOR << 16) |
                       ((uint32_t)FW_VERSION_MINOR << 8)  |
                       (uint32_t)FW_VERSION_PATCH;
      resp.device_id = DEVICE_ID;

      OTA_SendResponse(OTA_CMD_IDENTIFY, OTA_STATUS_OK,
                       (const uint8_t *)&resp, sizeof(resp));
      break;
    }

    case OTA_CMD_ENTER_BOOTLOADER:
    {
      /* ACK first, then write flag and reset */
      OTA_SendResponse(OTA_CMD_ENTER_BOOTLOADER, OTA_STATUS_OK, NULL, 0);
      /* Short delay for UART TX to flush */
      HAL_Delay(50);
      /* Refresh watchdog before flash op (erase+program takes ~100ms) */
      extern IWDG_HandleTypeDef hiwdg;
      HAL_IWDG_Refresh(&hiwdg);
      FW_WriteUpdateFlag(FW_UPDATE_FLAG_ADDRESS, FW_UPDATE_FLAG_VALUE);
      NVIC_SystemReset();
      break;  /* unreachable */
    }

    default:
      /* Unknown OTA command */
      OTA_SendResponse(cmd, OTA_STATUS_ERROR, NULL, 0);
      break;
  }
}



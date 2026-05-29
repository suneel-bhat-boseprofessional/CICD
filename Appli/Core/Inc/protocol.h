/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : protocol.h
  * @brief          : Header for protocol.c file.
  *                   UART JSON protocol handler
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
#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported defines ----------------------------------------------------------*/
#define UART_RX_BUFFER_SIZE RX_BUFFER_SIZE
#define PWM_PERIOD 1279
#define JSON_MAX_TOKENS 32  // Maximum number of JSON tokens to parse

/* Fan speed percentages */
#define SPEED_LOW_PERCENT   30
#define SPEED_MID_PERCENT   60
#define SPEED_HIGH_PERCENT  100

/* Brightness limits */
#define BRIGHTNESS_MIN      10
#define BRIGHTNESS_MAX      100

/* TUII Packet Framing -------------------------------------------------------*/
/* SOF markers (4 bytes each, big-endian on wire for JSON protocol) */
/* OTA SOF:    0xA1B1C1D1 → bytes: A1 B1 C1 D1 */
#define PROTOCOL_SOF_OTA_BYTE0   0xA1
#define PROTOCOL_SOF_OTA_BYTE1   0xB1
#define PROTOCOL_SOF_OTA_BYTE2   0xC1
#define PROTOCOL_SOF_OTA_BYTE3   0xD1
#define PROTOCOL_SOF_OTA_WORD    0xA1B1C1D1U

/* Normal SOF: 0xA2B2C2D2 → bytes: A2 B2 C2 D2 */
#define PROTOCOL_SOF_NORM_BYTE0  0xA5
#define PROTOCOL_SOF_NORM_BYTE1  0xB5
#define PROTOCOL_SOF_NORM_BYTE2  0xC5
#define PROTOCOL_SOF_NORM_BYTE3  0xD5
#define PROTOCOL_SOF_NORM_WORD   0xA5B5C5D5U

/* OTA binary SOF bytes (little-endian on wire) */
/* OTA request SOF:  0xA1B1C1D1 LE → D1 C1 B1 A1 */
#define OTA_SOF_REQ_BYTE0  0xD1
#define OTA_SOF_REQ_BYTE1  0xC1
#define OTA_SOF_REQ_BYTE2  0xB1
#define OTA_SOF_REQ_BYTE3  0xA1
/* OTA response SOF: 0xA2B2C2D2 LE → D2 C2 B2 A2 */
#define OTA_SOF_RSP_BYTE0  0xD2
#define OTA_SOF_RSP_BYTE1  0xC2
#define OTA_SOF_RSP_BYTE2  0xB2
#define OTA_SOF_RSP_BYTE3  0xA2

#define PROTOCOL_SOF_SIZE        4   /* bytes */
#define PROTOCOL_CRC_SIZE        2   /* bytes (little-endian) */
#define PROTOCOL_LEN_SIZE        1   /* bytes */
#define PROTOCOL_HEADER_SIZE     (PROTOCOL_SOF_SIZE + PROTOCOL_CRC_SIZE + PROTOCOL_LEN_SIZE)  /* 7 bytes */
#define PROTOCOL_MAX_PAYLOAD     255
#define PROTOCOL_MAX_PACKET      (PROTOCOL_HEADER_SIZE + PROTOCOL_MAX_PAYLOAD)  /* 262 bytes */

/* CRC16-CCITT-FALSE constants */
#define PROTOCOL_CRC_INITIAL     0xFFFF
#define PROTOCOL_CRC_POLYNOMIAL  0x1021
#define PROTOCOL_CRC_MSB_MASK    0x8000

/* Exported types ------------------------------------------------------------*/

/* Packet type returned by Protocol_ParsePacket */
typedef enum {
  PACKET_TYPE_UNKNOWN = 0,
  PACKET_TYPE_OTA,       /* SOF = 0xA1B1C1D1 */
  PACKET_TYPE_NORMAL     /* SOF = 0xA2B2C2D2 */
} PacketType_t;


/* Exported variables --------------------------------------------------------*/
extern uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];

/* Exported functions prototypes ---------------------------------------------*/
void FanControl_Init(TIM_HandleTypeDef *htim, UART_HandleTypeDef *huart, uint32_t tim_channel);
void FanControl_SetSpeed(uint8_t percent);
/* Incoming message model: {"action":"string","payload":{...}} */
typedef struct {
  char action[32];
  char payload[256]; // raw JSON string of payload
} GenericMessage;

int ParseGenericMessage(const char *json, GenericMessage *msg);
void JSON_ProcessMessage(uint8_t *data, uint16_t length);
void SendNack(UART_HandleTypeDef *huart, const char *failedAction, const char *errorMsg, int errorCode);
void FanControl_UART_RxIdleCallback(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);

/* TUII Packet Framing API ---------------------------------------------------*/
uint16_t Protocol_CRC16_CCITT(uint8_t *data, uint16_t length);
int Protocol_BuildPacket(PacketType_t type, const uint8_t *payload, uint8_t payloadLen, uint8_t *outBuf, uint16_t outBufSize);
int Protocol_ParsePacket(const uint8_t *packet, uint16_t packetLen, uint8_t *payloadOut, uint8_t *payloadLenOut, PacketType_t *packetType);
void Protocol_ProcessReceivedData(uint8_t *data, uint16_t length);

/* UI → Device outgoing message helpers */
void Protocol_SendSetGain(int zone, int norm);
void Protocol_SendSetMute(int zone, int state);
void Protocol_SendSetSource(int zone, int index);
void Protocol_SendSetBrightness(int value);

/* Request device info from server: sends {"action":"deviceInfo","payload":{}} */
void Protocol_RequestDeviceInfo(void);
/* Send a generic action with empty payload: {"action":"<action>","payload":{}} */
void Protocol_SendAction(const char* action);

/* OTA Binary Protocol -------------------------------------------------------*/
/* OTA binary frame layout (all multi-byte fields are LITTLE-ENDIAN):
 * Request:  | SOF(4) | CMD(1) | LEN_LO(1) LEN_HI(1) | CRC16_LO(1) CRC16_HI(1) | Payload(LEN) |
 * Response: | SOF(4) | CMD(1) | STATUS(1) | LEN_LO(1) LEN_HI(1) | Payload(LEN) | CRC16_LO(1) CRC16_HI(1) |
 */
#define OTA_CMD_IDENTIFY         0x01
#define OTA_CMD_ENTER_BOOTLOADER 0x02

#define OTA_STATUS_OK            0x00
#define OTA_STATUS_ERROR         0x01

#define OTA_MODE_APPLICATION     0x01
#define OTA_MODE_BOOTLOADER      0x02

/* OTA request minimum size: SOF(4) + CMD(1) + LEN(2) + CRC(2) = 9 */
#define OTA_REQUEST_MIN_SIZE     9
/* OTA response header: SOF(4) + CMD(1) + STATUS(1) + LEN(2) = 8 */
#define OTA_RESPONSE_HEADER_SIZE 8

typedef struct __attribute__((packed)) {
    uint8_t  mode;       /* OTA_MODE_APPLICATION or OTA_MODE_BOOTLOADER */
    uint32_t version;    /* (major<<16) | (minor<<8) | patch */
    uint32_t device_id;  /* DEVICE_ID (0x00000486) */
} OTA_IdentifyResponse_t;  /* 9 bytes */

void OTA_ProcessBinaryCommand(uint8_t *data, uint16_t length);

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

#endif /* __PROTOCOL_H */

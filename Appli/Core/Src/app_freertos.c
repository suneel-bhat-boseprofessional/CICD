/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : FreeRTOS applicative file
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
#include "app_freertos.h"
#include "main.h"
#include "timers.h"

extern int notifyTouch;

// Fix: Add required includes for FreeRTOS queue APIs and string functions
#include <string.h>
#include "FreeRTOS.h"
#include "queue.h"

// Fix: Declare uartRxQueue as extern (defined in main.c)
extern QueueHandle_t uartRxQueue;
extern IWDG_HandleTypeDef hiwdg;

// Fix: Define rxBuffer for queue receive
uint8_t rxBuffer[RX_BUFFER_SIZE];

TimerHandle_t wdogMonPeriodicTimer = NULL;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WDOG_MON_PERIOD_MS   500u       // 500ms
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for TouchGFXTask */
osThreadId_t TouchGFXTaskHandle;
const osThreadAttr_t TouchGFXTask_attributes = {
  .name = "TouchGFXTask",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 4096 * 4
};

#ifdef FUSION_WDOG_ENABLE
// Task & Semaphore for watchdog pet task
osThreadId_t WdogPetTaskHandle;
const osThreadAttr_t wdogPetTask_attributes = {
  .name = "wdogPetTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 1024
};
#endif

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void MX_IWDG_Init(void);
void WdogPet_Task(void *argument);

/* USER CODE END FunctionPrototypes */

/* USER CODE BEGIN 2 */
//
//  This is the Watchdog Pet periodic timer callback.
//  This will unblock the task that PETs the watchdog
//

void vApplicationIdleHook( void )
{
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFXTask */
  TouchGFXTaskHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFXTask_attributes);

#ifdef FUSION_WDOG_ENABLE
  WdogPetTaskHandle = osThreadNew(WdogPet_Task, NULL, &wdogPetTask_attributes);
#endif

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  // Periodic timer for Petting watchdog.

  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */

#ifdef FUSION_WDOG_ENABLE
      // Start Watchdog
      MX_IWDG_Init();
#endif

  /* Infinite loop */
  for(;;)
  {
      if (uxQueueMessagesWaiting(uartRxQueue) > 0)
      {
          xQueueReceive(
                  uartRxQueue,
                  rxBuffer,
                  0
                  );
          // Extract actual size from first 2 bytes (little-endian)
          uint16_t rxLen = (uint16_t)rxBuffer[0] | ((uint16_t)rxBuffer[1] << 8);
          // Process the received framed packet (header + payload)
          extern void Protocol_ProcessReceivedData(uint8_t *data, uint16_t length);
          Protocol_ProcessReceivedData(&rxBuffer[2], rxLen);
      }
      osDelay(100);
  }
  /* USER CODE END defaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
//
// THis is low priority task that is responsible for petting the watchdog.
//
#ifdef FUSION_WDOG_ENABLE
void WdogPet_Task(void *argument)
{

    while (1)
    {
        //osSemaphoreAcquire(wdogPetSemaphoreId, osWaitForever);

        ///// Should not get here if FUSION_WDOG_ENABLE is not defined.

        /* Refresh the IWDG to prevent watchdog reset */
        HAL_IWDG_Refresh(&hiwdg);
        vTaskDelay(pdMS_TO_TICKS(WDOG_MON_PERIOD_MS));
    }
}
#endif

/* USER CODE END Application */


/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.26.0. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
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

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>

#include "main.h"

volatile bool doSampleTouch = false;
static uint32_t lastTouchTime = 0;
static const uint32_t DEBOUNCE_TIME_MS = 50;  // 50ms debounce period

extern "C" 
{
    extern I2C_HandleTypeDef hi2c1;
    extern struct coop_data finger[MAX_NUM_TOUCHES];
    void process_touch_data(void);
    
    /**
      * @brief  GPIO EXTI Falling Edge callback for touch interrupt
      * @param  GPIO_Pin: Specifies the pins connected to the EXTI line
      * @retval None
      */
    void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
    {
        if (GPIO_Pin == GPIO_PIN_8)
        {
            uint32_t currentTime = HAL_GetTick();
            
            // Debounce: Only accept interrupt if enough time has passed since last one
            if ((currentTime - lastTouchTime) >= DEBOUNCE_TIME_MS)
            {
                /* Touch interrupt detected - set flag for TouchGFX to sample */
                doSampleTouch = true;
                lastTouchTime = currentTime;
            }
        }
    }
}

using namespace touchgfx;

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    bool touchDetected = false;
    
    NVIC_DisableIRQ(EXTI8_IRQn);  // Changed from EXTI4_IRQn to match GPIO_PIN_8
    
    if (doSampleTouch)
    {
        // Call your custom I2C driver to read touch data from device at 0x55
        // This reads 40 bytes from register 0x12 and populates finger[] array
        process_touch_data();
        
        // Check if first touch point is valid
        if (finger[0].per_valuebit == 1 && finger[0].status != NO_TOUCH)
        {
            // Get coordinates from first touch point
            x = finger[0].x;
            y = finger[0].y;
            touchDetected = true;
        }
        else
        {
            // No valid touch detected
            x = 0;
            y = 0;
            touchDetected = false;
        }
        
        doSampleTouch = false;  // Reset flag after processing
    }
    
    NVIC_EnableIRQ(EXTI8_IRQn);  // Changed from EXTI4_IRQn to match GPIO_PIN_8
    
    return touchDetected;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

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

extern "C" I2C_HandleTypeDef hi2c2;

using namespace touchgfx;

extern "C"

{
    void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)

    {
        if (GPIO_Pin == GPIO_PIN_8)

        {
            /* Communication with TS is done via I2C.
            Often the sw requires ISRs (interrupt service routines) to be quick while communication
            with I2C can be considered relatively long (depending on SW requirements).
            Considering that the TS feature don't need immediate reaction,
            it is suggested to use polling mode instead of EXTI mode,
            in order to avoid blocking I2C communication on interrupt service routines */
            /* Here an example of implementation is proposed which is a mix between pooling and exit mode:
            On ISR a flag is set (exti4_received), the main loop polls on the flag rather then polling the TS;
            Mcu communicates with TS only when the flag has been set by ISR. This is just an example:
            the users should choose they strategy depending on their application needs.*/
            doSampleTouch = true;
            return;
        }

    }

}

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}

bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */
    return false;
}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

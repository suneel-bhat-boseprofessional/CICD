################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/simulator/src/mainBase.cpp 

OBJS += \
./TouchGFX/generated/simulator/src/mainBase.o 

CPP_DEPS += \
./TouchGFX/generated/simulator/src/mainBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/simulator/src/%.o TouchGFX/generated/simulator/src/%.su TouchGFX/generated/simulator/src/%.cyclo: ../TouchGFX/generated/simulator/src/%.cpp TouchGFX/generated/simulator/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/simulator/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target/generated" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target" -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Secure_nsclib" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/fonts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/gui_generated/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/images/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/texts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/videos/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/gui/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-simulator-2f-src

clean-TouchGFX-2f-generated-2f-simulator-2f-src:
	-$(RM) ./TouchGFX/generated/simulator/src/mainBase.cyclo ./TouchGFX/generated/simulator/src/mainBase.d ./TouchGFX/generated/simulator/src/mainBase.o ./TouchGFX/generated/simulator/src/mainBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-simulator-2f-src


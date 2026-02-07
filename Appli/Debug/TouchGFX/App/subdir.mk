################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TouchGFX/App/app_touchgfx.c 

C_DEPS += \
./TouchGFX/App/app_touchgfx.d 

OBJS += \
./TouchGFX/App/app_touchgfx.o 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/App/%.o TouchGFX/App/%.su TouchGFX/App/%.cyclo: ../TouchGFX/App/%.c TouchGFX/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N645xx -c -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/lib/core/cortex_m55/gcc" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/Drivers/i2cCustomeDriver/inc" -I"C:/git-repo/touch_UI_Debug/Appli/Drivers/i2cCustomeDriver/src" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target/generated" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target" -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Secure_nsclib" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/fonts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/gui_generated/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/images/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/texts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/videos/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/gui/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-App

clean-TouchGFX-2f-App:
	-$(RM) ./TouchGFX/App/app_touchgfx.cyclo ./TouchGFX/App/app_touchgfx.d ./TouchGFX/App/app_touchgfx.o ./TouchGFX/App/app_touchgfx.su

.PHONY: clean-TouchGFX-2f-App


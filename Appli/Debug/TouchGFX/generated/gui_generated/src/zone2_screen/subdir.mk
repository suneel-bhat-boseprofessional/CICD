################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/zone2_screen/%.o TouchGFX/generated/gui_generated/src/zone2_screen/%.su TouchGFX/generated/gui_generated/src/zone2_screen/%.cyclo: ../TouchGFX/generated/gui_generated/src/zone2_screen/%.cpp TouchGFX/generated/gui_generated/src/zone2_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/simulator/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Core/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Secure_nsclib" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-zone2_screen

clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-zone2_screen:
	-$(RM) ./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.cyclo ./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.d ./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.o ./TouchGFX/generated/gui_generated/src/zone2_screen/zone2ViewBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-zone2_screen


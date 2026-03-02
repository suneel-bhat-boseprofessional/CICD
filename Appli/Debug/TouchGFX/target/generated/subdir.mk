################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/target/generated/HardwareMJPEGDecoder.cpp \
../TouchGFX/target/generated/OSWrappers.cpp \
../TouchGFX/target/generated/STM32DMA.cpp \
../TouchGFX/target/generated/TouchGFXConfiguration.cpp \
../TouchGFX/target/generated/TouchGFXGeneratedHAL.cpp 

C_SRCS += \
../TouchGFX/target/generated/nema_hal.c 

C_DEPS += \
./TouchGFX/target/generated/nema_hal.d 

OBJS += \
./TouchGFX/target/generated/HardwareMJPEGDecoder.o \
./TouchGFX/target/generated/OSWrappers.o \
./TouchGFX/target/generated/STM32DMA.o \
./TouchGFX/target/generated/TouchGFXConfiguration.o \
./TouchGFX/target/generated/TouchGFXGeneratedHAL.o \
./TouchGFX/target/generated/nema_hal.o 

CPP_DEPS += \
./TouchGFX/target/generated/HardwareMJPEGDecoder.d \
./TouchGFX/target/generated/OSWrappers.d \
./TouchGFX/target/generated/STM32DMA.d \
./TouchGFX/target/generated/TouchGFXConfiguration.d \
./TouchGFX/target/generated/TouchGFXGeneratedHAL.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/target/generated/%.o TouchGFX/target/generated/%.su TouchGFX/target/generated/%.cyclo: ../TouchGFX/target/generated/%.cpp TouchGFX/target/generated/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/simulator/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Core/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Secure_nsclib" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
TouchGFX/target/generated/%.o TouchGFX/target/generated/%.su TouchGFX/target/generated/%.cyclo: ../TouchGFX/target/generated/%.c TouchGFX/target/generated/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N645xx -c -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Core/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/lib/core/cortex_m55/gcc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/src" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Core/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Secure_nsclib" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-target-2f-generated

clean-TouchGFX-2f-target-2f-generated:
	-$(RM) ./TouchGFX/target/generated/HardwareMJPEGDecoder.cyclo ./TouchGFX/target/generated/HardwareMJPEGDecoder.d ./TouchGFX/target/generated/HardwareMJPEGDecoder.o ./TouchGFX/target/generated/HardwareMJPEGDecoder.su ./TouchGFX/target/generated/OSWrappers.cyclo ./TouchGFX/target/generated/OSWrappers.d ./TouchGFX/target/generated/OSWrappers.o ./TouchGFX/target/generated/OSWrappers.su ./TouchGFX/target/generated/STM32DMA.cyclo ./TouchGFX/target/generated/STM32DMA.d ./TouchGFX/target/generated/STM32DMA.o ./TouchGFX/target/generated/STM32DMA.su ./TouchGFX/target/generated/TouchGFXConfiguration.cyclo ./TouchGFX/target/generated/TouchGFXConfiguration.d ./TouchGFX/target/generated/TouchGFXConfiguration.o ./TouchGFX/target/generated/TouchGFXConfiguration.su ./TouchGFX/target/generated/TouchGFXGeneratedHAL.cyclo ./TouchGFX/target/generated/TouchGFXGeneratedHAL.d ./TouchGFX/target/generated/TouchGFXGeneratedHAL.o ./TouchGFX/target/generated/TouchGFXGeneratedHAL.su ./TouchGFX/target/generated/nema_hal.cyclo ./TouchGFX/target/generated/nema_hal.d ./TouchGFX/target/generated/nema_hal.o ./TouchGFX/target/generated/nema_hal.su

.PHONY: clean-TouchGFX-2f-target-2f-generated


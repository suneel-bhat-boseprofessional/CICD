################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Core/Src/system_stm32n6xx_s.c 

C_DEPS += \
./Drivers/CMSIS/system_stm32n6xx_s.d 

OBJS += \
./Drivers/CMSIS/system_stm32n6xx_s.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/system_stm32n6xx_s.o: C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Core/Src/system_stm32n6xx_s.c Drivers/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N645xx -c -I../../../Appli/TouchGFX/App -I../../../Appli/TouchGFX/target/generated -I../../../Appli/TouchGFX/target -I../../../Appli/Core/Inc -I../../../Secure_nsclib -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I../../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Appli/../../Appli/Middlewares/ST/touchgfx/framework/include -I../../Appli/../../Appli/TouchGFX/generated/fonts/include -I../../Appli/../../Appli/TouchGFX/generated/gui_generated/include -I../../Appli/../../Appli/TouchGFX/generated/images/include -I../../Appli/../../Appli/TouchGFX/generated/texts/include -I../../Appli/../../Appli/TouchGFX/generated/videos/include -I../../Appli/../../Appli/TouchGFX/gui/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS

clean-Drivers-2f-CMSIS:
	-$(RM) ./Drivers/CMSIS/system_stm32n6xx_s.cyclo ./Drivers/CMSIS/system_stm32n6xx_s.d ./Drivers/CMSIS/system_stm32n6xx_s.o ./Drivers/CMSIS/system_stm32n6xx_s.su

.PHONY: clean-Drivers-2f-CMSIS


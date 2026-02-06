################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/User/Startup/startup_stm32n645l0hxq.s 

S_DEPS += \
./Application/User/Startup/startup_stm32n645l0hxq.d 

OBJS += \
./Application/User/Startup/startup_stm32n645l0hxq.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Startup/%.o: ../Application/User/Startup/%.s Application/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m55 -g3 -DDEBUG -c -I../../../Appli/Core/Inc -I../../../Appli/TouchGFX/App -I../../../Appli/TouchGFX/target/generated -I../../../Appli/TouchGFX/target -I../../../Secure_nsclib -I../../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I../../Appli/../../Appli/Core/Inc -I../../../Appli/AZURE_RTOS/App -I../../../Middlewares/ST/threadx/common/inc -I../../../Middlewares/ST/threadx/ports/cortex_m55/gnu/inc -I../../Appli/../../Appli/Middlewares/ST/touchgfx/framework/include -I../../Appli/../../Appli/TouchGFX/generated/fonts/include -I../../Appli/../../Appli/TouchGFX/generated/gui_generated/include -I../../Appli/../../Appli/TouchGFX/generated/images/include -I../../Appli/../../Appli/TouchGFX/generated/texts/include -I../../Appli/../../Appli/TouchGFX/generated/videos/include -I../../Appli/../../Appli/TouchGFX/gui/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Startup

clean-Application-2f-User-2f-Startup:
	-$(RM) ./Application/User/Startup/startup_stm32n645l0hxq.d ./Application/User/Startup/startup_stm32n645l0hxq.o

.PHONY: clean-Application-2f-User-2f-Startup


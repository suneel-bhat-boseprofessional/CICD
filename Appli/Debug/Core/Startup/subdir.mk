################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32n645l0hxq.s 

S_DEPS += \
./Core/Startup/startup_stm32n645l0hxq.d 

OBJS += \
./Core/Startup/startup_stm32n645l0hxq.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m55 -g3 -DDEBUG -c -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target/generated" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target" -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Secure_nsclib" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I../../Appli/../../Appli/Core/Inc -I../../../Appli/TouchGFX/App -I../../../Appli/TouchGFX/target/generated -I../../../Appli/TouchGFX/target -I../../../Appli/Core/Inc -I../../../Secure_nsclib -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/ST/threadx/common/inc -I../../../Middlewares/ST/threadx/ports/cortex_m55/gnu/inc -I../../../Drivers/CMSIS/Include -I../../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Appli/../../Appli/Middlewares/ST/touchgfx/framework/include -I../../Appli/../../Appli/TouchGFX/generated/fonts/include -I../../Appli/../../Appli/TouchGFX/generated/gui_generated/include -I../../Appli/../../Appli/TouchGFX/generated/images/include -I../../Appli/../../Appli/TouchGFX/generated/texts/include -I../../Appli/../../Appli/TouchGFX/generated/videos/include -I../../Appli/../../Appli/TouchGFX/gui/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32n645l0hxq.d ./Core/Startup/startup_stm32n645l0hxq.o

.PHONY: clean-Core-2f-Startup


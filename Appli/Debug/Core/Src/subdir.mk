################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/app_freertos.c \
../Core/Src/main.c \
../Core/Src/secure_nsc.c \
../Core/Src/stm32n6xx_hal_msp.c \
../Core/Src/stm32n6xx_hal_timebase_tim.c \
../Core/Src/stm32n6xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32n6xx_s.c 

C_DEPS += \
./Core/Src/app_freertos.d \
./Core/Src/main.d \
./Core/Src/secure_nsc.d \
./Core/Src/stm32n6xx_hal_msp.d \
./Core/Src/stm32n6xx_hal_timebase_tim.d \
./Core/Src/stm32n6xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32n6xx_s.d 

OBJS += \
./Core/Src/app_freertos.o \
./Core/Src/main.o \
./Core/Src/secure_nsc.o \
./Core/Src/stm32n6xx_hal_msp.o \
./Core/Src/stm32n6xx_hal_timebase_tim.o \
./Core/Src/stm32n6xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32n6xx_s.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N645xx -c -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Core/Inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/lib/core/cortex_m55/gcc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/src" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Core/Inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Secure_nsclib" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/app_freertos.cyclo ./Core/Src/app_freertos.d ./Core/Src/app_freertos.o ./Core/Src/app_freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/secure_nsc.cyclo ./Core/Src/secure_nsc.d ./Core/Src/secure_nsc.o ./Core/Src/secure_nsc.su ./Core/Src/stm32n6xx_hal_msp.cyclo ./Core/Src/stm32n6xx_hal_msp.d ./Core/Src/stm32n6xx_hal_msp.o ./Core/Src/stm32n6xx_hal_msp.su ./Core/Src/stm32n6xx_hal_timebase_tim.cyclo ./Core/Src/stm32n6xx_hal_timebase_tim.d ./Core/Src/stm32n6xx_hal_timebase_tim.o ./Core/Src/stm32n6xx_hal_timebase_tim.su ./Core/Src/stm32n6xx_it.cyclo ./Core/Src/stm32n6xx_it.d ./Core/Src/stm32n6xx_it.o ./Core/Src/stm32n6xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32n6xx_s.cyclo ./Core/Src/system_stm32n6xx_s.d ./Core/Src/system_stm32n6xx_s.o ./Core/Src/system_stm32n6xx_s.su

.PHONY: clean-Core-2f-Src


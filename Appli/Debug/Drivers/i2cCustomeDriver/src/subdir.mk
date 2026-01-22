################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/i2cCustomeDriver/src/LCD_Touch.c \
../Drivers/i2cCustomeDriver/src/ft6x06.c \
../Drivers/i2cCustomeDriver/src/stx_getraw.c 

OBJS += \
./Drivers/i2cCustomeDriver/src/LCD_Touch.o \
./Drivers/i2cCustomeDriver/src/ft6x06.o \
./Drivers/i2cCustomeDriver/src/stx_getraw.o 

C_DEPS += \
./Drivers/i2cCustomeDriver/src/LCD_Touch.d \
./Drivers/i2cCustomeDriver/src/ft6x06.d \
./Drivers/i2cCustomeDriver/src/stx_getraw.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/i2cCustomeDriver/src/%.o Drivers/i2cCustomeDriver/src/%.su Drivers/i2cCustomeDriver/src/%.cyclo: ../Drivers/i2cCustomeDriver/src/%.c Drivers/i2cCustomeDriver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m55 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32N645xx -c -I../Core/Inc -I"C:/CurrentDevelopment/touchUIPCB/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/inc" -I"C:/CurrentDevelopment/touchUIPCB/touchUI_Bringup/Appli/Drivers/i2cCustomeDriver/src" -I../../Secure_nsclib -I../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-i2cCustomeDriver-2f-src

clean-Drivers-2f-i2cCustomeDriver-2f-src:
	-$(RM) ./Drivers/i2cCustomeDriver/src/LCD_Touch.cyclo ./Drivers/i2cCustomeDriver/src/LCD_Touch.d ./Drivers/i2cCustomeDriver/src/LCD_Touch.o ./Drivers/i2cCustomeDriver/src/LCD_Touch.su ./Drivers/i2cCustomeDriver/src/ft6x06.cyclo ./Drivers/i2cCustomeDriver/src/ft6x06.d ./Drivers/i2cCustomeDriver/src/ft6x06.o ./Drivers/i2cCustomeDriver/src/ft6x06.su ./Drivers/i2cCustomeDriver/src/stx_getraw.cyclo ./Drivers/i2cCustomeDriver/src/stx_getraw.d ./Drivers/i2cCustomeDriver/src/stx_getraw.o ./Drivers/i2cCustomeDriver/src/stx_getraw.su

.PHONY: clean-Drivers-2f-i2cCustomeDriver-2f-src


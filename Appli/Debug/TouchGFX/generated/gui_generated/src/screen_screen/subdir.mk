################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.cpp 

OBJS += \
./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.o 

CPP_DEPS += \
./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/gui_generated/src/screen_screen/%.o TouchGFX/generated/gui_generated/src/screen_screen/%.su TouchGFX/generated/gui_generated/src/screen_screen/%.cyclo: ../TouchGFX/generated/gui_generated/src/screen_screen/%.cpp TouchGFX/generated/gui_generated/src/screen_screen/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -c -I../../../Appli/TouchGFX/App -I../../../Appli/TouchGFX/target/generated -I../../../Appli/TouchGFX/target -I../../../Appli/Core/Inc -I../../../Secure_nsclib -I../../../Drivers/STM32N6xx_HAL_Driver/Inc -I../../../Drivers/CMSIS/Device/ST/STM32N6xx/Include -I../../../Drivers/STM32N6xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Include -I../../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure/ -I../../Appli/../../Appli/Middlewares/ST/touchgfx/framework/include -I../../Appli/../../Appli/TouchGFX/generated/fonts/include -I../../Appli/../../Appli/TouchGFX/generated/gui_generated/include -I../../Appli/../../Appli/TouchGFX/generated/images/include -I../../Appli/../../Appli/TouchGFX/generated/texts/include -I../../Appli/../../Appli/TouchGFX/generated/videos/include -I../../Appli/../../Appli/TouchGFX/gui/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-screen_screen

clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-screen_screen:
	-$(RM) ./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.cyclo ./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.d ./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.o ./TouchGFX/generated/gui_generated/src/screen_screen/screenViewBase.su

.PHONY: clean-TouchGFX-2f-generated-2f-gui_generated-2f-src-2f-screen_screen


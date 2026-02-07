################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/texts/src/LanguageGb.cpp \
../TouchGFX/generated/texts/src/Texts.cpp \
../TouchGFX/generated/texts/src/TypedTextDatabase.cpp 

OBJS += \
./TouchGFX/generated/texts/src/LanguageGb.o \
./TouchGFX/generated/texts/src/Texts.o \
./TouchGFX/generated/texts/src/TypedTextDatabase.o 

CPP_DEPS += \
./TouchGFX/generated/texts/src/LanguageGb.d \
./TouchGFX/generated/texts/src/Texts.d \
./TouchGFX/generated/texts/src/TypedTextDatabase.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/texts/src/%.o TouchGFX/generated/texts/src/%.su TouchGFX/generated/texts/src/%.cyclo: ../TouchGFX/generated/texts/src/%.cpp TouchGFX/generated/texts/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/simulator/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target/generated" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target" -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Secure_nsclib" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/fonts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/gui_generated/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/images/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/texts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/videos/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/gui/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-texts-2f-src

clean-TouchGFX-2f-generated-2f-texts-2f-src:
	-$(RM) ./TouchGFX/generated/texts/src/LanguageGb.cyclo ./TouchGFX/generated/texts/src/LanguageGb.d ./TouchGFX/generated/texts/src/LanguageGb.o ./TouchGFX/generated/texts/src/LanguageGb.su ./TouchGFX/generated/texts/src/Texts.cyclo ./TouchGFX/generated/texts/src/Texts.d ./TouchGFX/generated/texts/src/Texts.o ./TouchGFX/generated/texts/src/Texts.su ./TouchGFX/generated/texts/src/TypedTextDatabase.cyclo ./TouchGFX/generated/texts/src/TypedTextDatabase.d ./TouchGFX/generated/texts/src/TypedTextDatabase.o ./TouchGFX/generated/texts/src/TypedTextDatabase.su

.PHONY: clean-TouchGFX-2f-generated-2f-texts-2f-src


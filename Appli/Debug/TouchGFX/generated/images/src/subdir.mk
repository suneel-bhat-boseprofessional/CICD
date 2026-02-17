################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/SVGDatabase.cpp \
../TouchGFX/generated/images/src/image_boseLogo.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/SVGDatabase.o \
./TouchGFX/generated/images/src/image_boseLogo.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/SVGDatabase.d \
./TouchGFX/generated/images/src/image_boseLogo.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/%.o TouchGFX/generated/images/src/%.su TouchGFX/generated/images/src/%.cyclo: ../TouchGFX/generated/images/src/%.cpp TouchGFX/generated/images/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/simulator/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Core/Inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Secure_nsclib" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/CurrentDevelopment/sudhaTouchUICode/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src

clean-TouchGFX-2f-generated-2f-images-2f-src:
	-$(RM) ./TouchGFX/generated/images/src/BitmapDatabase.cyclo ./TouchGFX/generated/images/src/BitmapDatabase.d ./TouchGFX/generated/images/src/BitmapDatabase.o ./TouchGFX/generated/images/src/BitmapDatabase.su ./TouchGFX/generated/images/src/SVGDatabase.cyclo ./TouchGFX/generated/images/src/SVGDatabase.d ./TouchGFX/generated/images/src/SVGDatabase.o ./TouchGFX/generated/images/src/SVGDatabase.su ./TouchGFX/generated/images/src/image_boseLogo.cyclo ./TouchGFX/generated/images/src/image_boseLogo.d ./TouchGFX/generated/images/src/image_boseLogo.o ./TouchGFX/generated/images/src/image_boseLogo.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/images/src/BitmapDatabase.cpp \
../TouchGFX/generated/images/src/SVGDatabase.cpp \
../TouchGFX/generated/images/src/image_Bluetooth_image.cpp \
../TouchGFX/generated/images/src/image_Down.cpp \
../TouchGFX/generated/images/src/image_Ellipse_1954.cpp \
../TouchGFX/generated/images/src/image_Ellipse_1955.cpp \
../TouchGFX/generated/images/src/image_Footer_100.cpp \
../TouchGFX/generated/images/src/image_Footer_Text.cpp \
../TouchGFX/generated/images/src/image_Frame.cpp \
../TouchGFX/generated/images/src/image_Grabber.cpp \
../TouchGFX/generated/images/src/image_Group_1.cpp \
../TouchGFX/generated/images/src/image_Inout_image.cpp \
../TouchGFX/generated/images/src/image_Logo.cpp \
../TouchGFX/generated/images/src/image_Meters_image.cpp \
../TouchGFX/generated/images/src/image_Notifications_image.cpp \
../TouchGFX/generated/images/src/image_Rectangle_1.cpp \
../TouchGFX/generated/images/src/image_Rectangle_2.cpp \
../TouchGFX/generated/images/src/image_Settings_image.cpp \
../TouchGFX/generated/images/src/image_Setup_image.cpp \
../TouchGFX/generated/images/src/image_Slider.cpp \
../TouchGFX/generated/images/src/image_Up.cpp \
../TouchGFX/generated/images/src/image_Vector.cpp \
../TouchGFX/generated/images/src/image_Volume_green.cpp \
../TouchGFX/generated/images/src/image_Volumeslider_bg.cpp \
../TouchGFX/generated/images/src/image_Zone.cpp \
../TouchGFX/generated/images/src/image_left.cpp \
../TouchGFX/generated/images/src/image_right.cpp \
../TouchGFX/generated/images/src/image_volume-off.cpp \
../TouchGFX/generated/images/src/image_zones.cpp 

OBJS += \
./TouchGFX/generated/images/src/BitmapDatabase.o \
./TouchGFX/generated/images/src/SVGDatabase.o \
./TouchGFX/generated/images/src/image_Bluetooth_image.o \
./TouchGFX/generated/images/src/image_Down.o \
./TouchGFX/generated/images/src/image_Ellipse_1954.o \
./TouchGFX/generated/images/src/image_Ellipse_1955.o \
./TouchGFX/generated/images/src/image_Footer_100.o \
./TouchGFX/generated/images/src/image_Footer_Text.o \
./TouchGFX/generated/images/src/image_Frame.o \
./TouchGFX/generated/images/src/image_Grabber.o \
./TouchGFX/generated/images/src/image_Group_1.o \
./TouchGFX/generated/images/src/image_Inout_image.o \
./TouchGFX/generated/images/src/image_Logo.o \
./TouchGFX/generated/images/src/image_Meters_image.o \
./TouchGFX/generated/images/src/image_Notifications_image.o \
./TouchGFX/generated/images/src/image_Rectangle_1.o \
./TouchGFX/generated/images/src/image_Rectangle_2.o \
./TouchGFX/generated/images/src/image_Settings_image.o \
./TouchGFX/generated/images/src/image_Setup_image.o \
./TouchGFX/generated/images/src/image_Slider.o \
./TouchGFX/generated/images/src/image_Up.o \
./TouchGFX/generated/images/src/image_Vector.o \
./TouchGFX/generated/images/src/image_Volume_green.o \
./TouchGFX/generated/images/src/image_Volumeslider_bg.o \
./TouchGFX/generated/images/src/image_Zone.o \
./TouchGFX/generated/images/src/image_left.o \
./TouchGFX/generated/images/src/image_right.o \
./TouchGFX/generated/images/src/image_volume-off.o \
./TouchGFX/generated/images/src/image_zones.o 

CPP_DEPS += \
./TouchGFX/generated/images/src/BitmapDatabase.d \
./TouchGFX/generated/images/src/SVGDatabase.d \
./TouchGFX/generated/images/src/image_Bluetooth_image.d \
./TouchGFX/generated/images/src/image_Down.d \
./TouchGFX/generated/images/src/image_Ellipse_1954.d \
./TouchGFX/generated/images/src/image_Ellipse_1955.d \
./TouchGFX/generated/images/src/image_Footer_100.d \
./TouchGFX/generated/images/src/image_Footer_Text.d \
./TouchGFX/generated/images/src/image_Frame.d \
./TouchGFX/generated/images/src/image_Grabber.d \
./TouchGFX/generated/images/src/image_Group_1.d \
./TouchGFX/generated/images/src/image_Inout_image.d \
./TouchGFX/generated/images/src/image_Logo.d \
./TouchGFX/generated/images/src/image_Meters_image.d \
./TouchGFX/generated/images/src/image_Notifications_image.d \
./TouchGFX/generated/images/src/image_Rectangle_1.d \
./TouchGFX/generated/images/src/image_Rectangle_2.d \
./TouchGFX/generated/images/src/image_Settings_image.d \
./TouchGFX/generated/images/src/image_Setup_image.d \
./TouchGFX/generated/images/src/image_Slider.d \
./TouchGFX/generated/images/src/image_Up.d \
./TouchGFX/generated/images/src/image_Vector.d \
./TouchGFX/generated/images/src/image_Volume_green.d \
./TouchGFX/generated/images/src/image_Volumeslider_bg.d \
./TouchGFX/generated/images/src/image_Zone.d \
./TouchGFX/generated/images/src/image_left.d \
./TouchGFX/generated/images/src/image_right.d \
./TouchGFX/generated/images/src/image_volume-off.d \
./TouchGFX/generated/images/src/image_zones.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/images/src/%.o TouchGFX/generated/images/src/%.su TouchGFX/generated/images/src/%.cyclo: ../TouchGFX/generated/images/src/%.cpp TouchGFX/generated/images/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/App" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/simulator/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target/generated" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/target" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Core/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Secure_nsclib" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/ST/touchUI_Development/touchUI_Bringup/Drivers/CMSIS/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/fonts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/gui_generated/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/images/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/texts/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/generated/videos/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/TouchGFX/gui/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/ST/touchUI_Development/touchUI_Bringup/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-images-2f-src

clean-TouchGFX-2f-generated-2f-images-2f-src:
	-$(RM) ./TouchGFX/generated/images/src/BitmapDatabase.cyclo ./TouchGFX/generated/images/src/BitmapDatabase.d ./TouchGFX/generated/images/src/BitmapDatabase.o ./TouchGFX/generated/images/src/BitmapDatabase.su ./TouchGFX/generated/images/src/SVGDatabase.cyclo ./TouchGFX/generated/images/src/SVGDatabase.d ./TouchGFX/generated/images/src/SVGDatabase.o ./TouchGFX/generated/images/src/SVGDatabase.su ./TouchGFX/generated/images/src/image_Bluetooth_image.cyclo ./TouchGFX/generated/images/src/image_Bluetooth_image.d ./TouchGFX/generated/images/src/image_Bluetooth_image.o ./TouchGFX/generated/images/src/image_Bluetooth_image.su ./TouchGFX/generated/images/src/image_Down.cyclo ./TouchGFX/generated/images/src/image_Down.d ./TouchGFX/generated/images/src/image_Down.o ./TouchGFX/generated/images/src/image_Down.su ./TouchGFX/generated/images/src/image_Ellipse_1954.cyclo ./TouchGFX/generated/images/src/image_Ellipse_1954.d ./TouchGFX/generated/images/src/image_Ellipse_1954.o ./TouchGFX/generated/images/src/image_Ellipse_1954.su ./TouchGFX/generated/images/src/image_Ellipse_1955.cyclo ./TouchGFX/generated/images/src/image_Ellipse_1955.d ./TouchGFX/generated/images/src/image_Ellipse_1955.o ./TouchGFX/generated/images/src/image_Ellipse_1955.su ./TouchGFX/generated/images/src/image_Footer_100.cyclo ./TouchGFX/generated/images/src/image_Footer_100.d ./TouchGFX/generated/images/src/image_Footer_100.o ./TouchGFX/generated/images/src/image_Footer_100.su ./TouchGFX/generated/images/src/image_Footer_Text.cyclo ./TouchGFX/generated/images/src/image_Footer_Text.d ./TouchGFX/generated/images/src/image_Footer_Text.o ./TouchGFX/generated/images/src/image_Footer_Text.su ./TouchGFX/generated/images/src/image_Frame.cyclo ./TouchGFX/generated/images/src/image_Frame.d ./TouchGFX/generated/images/src/image_Frame.o ./TouchGFX/generated/images/src/image_Frame.su ./TouchGFX/generated/images/src/image_Grabber.cyclo ./TouchGFX/generated/images/src/image_Grabber.d ./TouchGFX/generated/images/src/image_Grabber.o ./TouchGFX/generated/images/src/image_Grabber.su ./TouchGFX/generated/images/src/image_Group_1.cyclo ./TouchGFX/generated/images/src/image_Group_1.d ./TouchGFX/generated/images/src/image_Group_1.o ./TouchGFX/generated/images/src/image_Group_1.su ./TouchGFX/generated/images/src/image_Inout_image.cyclo ./TouchGFX/generated/images/src/image_Inout_image.d ./TouchGFX/generated/images/src/image_Inout_image.o ./TouchGFX/generated/images/src/image_Inout_image.su ./TouchGFX/generated/images/src/image_Logo.cyclo ./TouchGFX/generated/images/src/image_Logo.d ./TouchGFX/generated/images/src/image_Logo.o ./TouchGFX/generated/images/src/image_Logo.su ./TouchGFX/generated/images/src/image_Meters_image.cyclo ./TouchGFX/generated/images/src/image_Meters_image.d ./TouchGFX/generated/images/src/image_Meters_image.o ./TouchGFX/generated/images/src/image_Meters_image.su ./TouchGFX/generated/images/src/image_Notifications_image.cyclo ./TouchGFX/generated/images/src/image_Notifications_image.d ./TouchGFX/generated/images/src/image_Notifications_image.o ./TouchGFX/generated/images/src/image_Notifications_image.su ./TouchGFX/generated/images/src/image_Rectangle_1.cyclo ./TouchGFX/generated/images/src/image_Rectangle_1.d ./TouchGFX/generated/images/src/image_Rectangle_1.o ./TouchGFX/generated/images/src/image_Rectangle_1.su ./TouchGFX/generated/images/src/image_Rectangle_2.cyclo ./TouchGFX/generated/images/src/image_Rectangle_2.d ./TouchGFX/generated/images/src/image_Rectangle_2.o ./TouchGFX/generated/images/src/image_Rectangle_2.su ./TouchGFX/generated/images/src/image_Settings_image.cyclo ./TouchGFX/generated/images/src/image_Settings_image.d ./TouchGFX/generated/images/src/image_Settings_image.o ./TouchGFX/generated/images/src/image_Settings_image.su ./TouchGFX/generated/images/src/image_Setup_image.cyclo ./TouchGFX/generated/images/src/image_Setup_image.d ./TouchGFX/generated/images/src/image_Setup_image.o ./TouchGFX/generated/images/src/image_Setup_image.su ./TouchGFX/generated/images/src/image_Slider.cyclo ./TouchGFX/generated/images/src/image_Slider.d ./TouchGFX/generated/images/src/image_Slider.o ./TouchGFX/generated/images/src/image_Slider.su ./TouchGFX/generated/images/src/image_Up.cyclo ./TouchGFX/generated/images/src/image_Up.d ./TouchGFX/generated/images/src/image_Up.o ./TouchGFX/generated/images/src/image_Up.su ./TouchGFX/generated/images/src/image_Vector.cyclo ./TouchGFX/generated/images/src/image_Vector.d ./TouchGFX/generated/images/src/image_Vector.o ./TouchGFX/generated/images/src/image_Vector.su ./TouchGFX/generated/images/src/image_Volume_green.cyclo ./TouchGFX/generated/images/src/image_Volume_green.d ./TouchGFX/generated/images/src/image_Volume_green.o ./TouchGFX/generated/images/src/image_Volume_green.su ./TouchGFX/generated/images/src/image_Volumeslider_bg.cyclo ./TouchGFX/generated/images/src/image_Volumeslider_bg.d ./TouchGFX/generated/images/src/image_Volumeslider_bg.o ./TouchGFX/generated/images/src/image_Volumeslider_bg.su ./TouchGFX/generated/images/src/image_Zone.cyclo ./TouchGFX/generated/images/src/image_Zone.d ./TouchGFX/generated/images/src/image_Zone.o ./TouchGFX/generated/images/src/image_Zone.su ./TouchGFX/generated/images/src/image_left.cyclo ./TouchGFX/generated/images/src/image_left.d ./TouchGFX/generated/images/src/image_left.o ./TouchGFX/generated/images/src/image_left.su ./TouchGFX/generated/images/src/image_right.cyclo ./TouchGFX/generated/images/src/image_right.d ./TouchGFX/generated/images/src/image_right.o ./TouchGFX/generated/images/src/image_right.su ./TouchGFX/generated/images/src/image_volume-off.cyclo ./TouchGFX/generated/images/src/image_volume-off.d ./TouchGFX/generated/images/src/image_volume-off.o ./TouchGFX/generated/images/src/image_volume-off.su ./TouchGFX/generated/images/src/image_zones.cyclo ./TouchGFX/generated/images/src/image_zones.d ./TouchGFX/generated/images/src/image_zones.o ./TouchGFX/generated/images/src/image_zones.su

.PHONY: clean-TouchGFX-2f-generated-2f-images-2f-src


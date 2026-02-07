################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TouchGFX/generated/fonts/src/ApplicationFontProvider.cpp \
../TouchGFX/generated/fonts/src/CachedFont.cpp \
../TouchGFX/generated/fonts/src/CompressedFontCache.cpp \
../TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.cpp \
../TouchGFX/generated/fonts/src/FontCache.cpp \
../TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.cpp \
../TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.cpp \
../TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.cpp \
../TouchGFX/generated/fonts/src/GeneratedFont.cpp \
../TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.cpp \
../TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.cpp \
../TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.cpp \
../TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.cpp \
../TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.cpp \
../TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.cpp \
../TouchGFX/generated/fonts/src/UnmappedDataFont.cpp \
../TouchGFX/generated/fonts/src/VectorFontRendererBuffers.cpp 

OBJS += \
./TouchGFX/generated/fonts/src/ApplicationFontProvider.o \
./TouchGFX/generated/fonts/src/CachedFont.o \
./TouchGFX/generated/fonts/src/CompressedFontCache.o \
./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.o \
./TouchGFX/generated/fonts/src/FontCache.o \
./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.o \
./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.o \
./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.o \
./TouchGFX/generated/fonts/src/GeneratedFont.o \
./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.o \
./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.o \
./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.o \
./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.o \
./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.o \
./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.o \
./TouchGFX/generated/fonts/src/UnmappedDataFont.o \
./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.o 

CPP_DEPS += \
./TouchGFX/generated/fonts/src/ApplicationFontProvider.d \
./TouchGFX/generated/fonts/src/CachedFont.d \
./TouchGFX/generated/fonts/src/CompressedFontCache.d \
./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.d \
./TouchGFX/generated/fonts/src/FontCache.d \
./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.d \
./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.d \
./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.d \
./TouchGFX/generated/fonts/src/GeneratedFont.d \
./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.d \
./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.d \
./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.d \
./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.d \
./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.d \
./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.d \
./TouchGFX/generated/fonts/src/UnmappedDataFont.d \
./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.d 


# Each subdirectory must supply rules for building sources it contributes
TouchGFX/generated/fonts/src/%.o TouchGFX/generated/fonts/src/%.su TouchGFX/generated/fonts/src/%.cyclo: ../TouchGFX/generated/fonts/src/%.cpp TouchGFX/generated/fonts/src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m55 -std=gnu++14 -g3 -DSTM32N645xx -DUSE_HAL_DRIVER -c -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/App" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/simulator/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target/generated" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/target" -I"C:/git-repo/touch_UI_Debug/Appli/Core/Inc" -I"C:/git-repo/touch_UI_Debug/Secure_nsclib" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Device/ST/STM32N6xx/Include" -I"C:/git-repo/touch_UI_Debug/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy" -I"C:/git-repo/touch_UI_Debug/Drivers/CMSIS/Include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM55_NTZ/non_secure" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/fonts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/gui_generated/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/images/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/texts/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/generated/videos/include" -I"C:/git-repo/touch_UI_Debug/Appli/TouchGFX/gui/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/framework/include/platform/hal/simulator/sdl2/vendor" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include" -I"C:/git-repo/touch_UI_Debug/Middlewares/Third_Party/CMSIS/RTOS2/Include" -I"C:/git-repo/touch_UI_Debug/Appli/Middlewares/ST/touchgfx/3rdparty/libjpeg/include" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-TouchGFX-2f-generated-2f-fonts-2f-src

clean-TouchGFX-2f-generated-2f-fonts-2f-src:
	-$(RM) ./TouchGFX/generated/fonts/src/ApplicationFontProvider.cyclo ./TouchGFX/generated/fonts/src/ApplicationFontProvider.d ./TouchGFX/generated/fonts/src/ApplicationFontProvider.o ./TouchGFX/generated/fonts/src/ApplicationFontProvider.su ./TouchGFX/generated/fonts/src/CachedFont.cyclo ./TouchGFX/generated/fonts/src/CachedFont.d ./TouchGFX/generated/fonts/src/CachedFont.o ./TouchGFX/generated/fonts/src/CachedFont.su ./TouchGFX/generated/fonts/src/CompressedFontCache.cyclo ./TouchGFX/generated/fonts/src/CompressedFontCache.d ./TouchGFX/generated/fonts/src/CompressedFontCache.o ./TouchGFX/generated/fonts/src/CompressedFontCache.su ./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.cyclo ./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.d ./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.o ./TouchGFX/generated/fonts/src/CompressedUnmappedFontCache.su ./TouchGFX/generated/fonts/src/FontCache.cyclo ./TouchGFX/generated/fonts/src/FontCache.d ./TouchGFX/generated/fonts/src/FontCache.o ./TouchGFX/generated/fonts/src/FontCache.su ./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.cyclo ./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.d ./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.o ./TouchGFX/generated/fonts/src/Font_verdana_10_4bpp_0.su ./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.cyclo ./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.d ./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.o ./TouchGFX/generated/fonts/src/Font_verdana_20_4bpp_0.su ./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.cyclo ./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.d ./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.o ./TouchGFX/generated/fonts/src/Font_verdana_40_4bpp_0.su ./TouchGFX/generated/fonts/src/GeneratedFont.cyclo ./TouchGFX/generated/fonts/src/GeneratedFont.d ./TouchGFX/generated/fonts/src/GeneratedFont.o ./TouchGFX/generated/fonts/src/GeneratedFont.su ./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.cyclo ./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.d ./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.o ./TouchGFX/generated/fonts/src/Kerning_verdana_10_4bpp.su ./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.cyclo ./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.d ./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.o ./TouchGFX/generated/fonts/src/Kerning_verdana_20_4bpp.su ./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.cyclo ./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.d ./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.o ./TouchGFX/generated/fonts/src/Kerning_verdana_40_4bpp.su ./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.cyclo ./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.d ./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.o ./TouchGFX/generated/fonts/src/Table_verdana_10_4bpp.su ./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.cyclo ./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.d ./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.o ./TouchGFX/generated/fonts/src/Table_verdana_20_4bpp.su ./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.cyclo ./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.d ./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.o ./TouchGFX/generated/fonts/src/Table_verdana_40_4bpp.su ./TouchGFX/generated/fonts/src/UnmappedDataFont.cyclo ./TouchGFX/generated/fonts/src/UnmappedDataFont.d ./TouchGFX/generated/fonts/src/UnmappedDataFont.o ./TouchGFX/generated/fonts/src/UnmappedDataFont.su ./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.cyclo ./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.d ./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.o ./TouchGFX/generated/fonts/src/VectorFontRendererBuffers.su

.PHONY: clean-TouchGFX-2f-generated-2f-fonts-2f-src


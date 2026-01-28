################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/RTOS2/CMSIS/RTOS2/Heap/Heap_4/subdir.mk
-include Middlewares/RTOS2/CMSIS/RTOS2/Core/TZ_Secure_Only/subdir.mk
-include Drivers/STM32N6xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/gui/subdir.mk
-include Application/User/generated/subdir.mk
-include Application/User/TouchGFX/target/generated/subdir.mk
-include Application/User/TouchGFX/target/subdir.mk
-include Application/User/TouchGFX/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CCM_DEPS)),)
-include $(CCM_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CXXM_DEPS)),)
-include $(CXXM_DEPS)
endif
ifneq ($(strip $(C++M_DEPS)),)
-include $(C++M_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := touchUI_BringUP_Appli
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
touchUI_BringUP_Appli.elf \

MAP_FILES += \
touchUI_BringUP_Appli.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
touchUI_BringUP_Appli.list \

OBJCOPY_BIN += \
touchUI_BringUP_Appli.bin \


# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: touchUI_BringUP_Appli.elf secondary-outputs

# Tool invocations
touchUI_BringUP_Appli.elf touchUI_BringUP_Appli.map: $(OBJS) $(USER_OBJS) C:\CurrentDevelopment\touchUIPCB\touchUI_Bringup\STM32CubeIDE\Appli\STM32N645L0HXQ_LRUN.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-g++ -o "touchUI_BringUP_Appli.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m55 -T"C:\CurrentDevelopment\touchUIPCB\touchUI_Bringup\STM32CubeIDE\Appli\STM32N645L0HXQ_LRUN.ld" --specs=nosys.specs -Wl,-Map="touchUI_BringUP_Appli.map" -Wl,--gc-sections -static -Wl,--cmse-implib -Wl,--out-implib=./secure_nsclib.o -L../../../Appli/Middlewares/ST/touchgfx/lib/core/cortex_m55/gcc -L../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/lib/core/cortex_m55/gcc -L../../Appli/../../Appli/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/lib/cortex_m55/gcc --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

touchUI_BringUP_Appli.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "touchUI_BringUP_Appli.list"
	@echo 'Finished building: $@'
	@echo ' '

touchUI_BringUP_Appli.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "touchUI_BringUP_Appli.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout touchUI_BringUP_Appli.bin touchUI_BringUP_Appli.elf touchUI_BringUP_Appli.list touchUI_BringUP_Appli.map
	-@echo ' '

post-build:
	arm-none-eabi-objcopy.exe -O binary --remove-section=ExtFlashSection --remove-section=FontFlashSection --remove-section=TextFlashSection touchUI_BringUP_Appli.elf touchUI_BringUP_Appli.bin&arm-none-eabi-objcopy.exe -O ihex --only-section=FontFlashSection --only-section=TextFlashSection --only-section=ExtFlashSection touchUI_BringUP_Appli.elf touchUI_BringUP_Appli_assets.hex
	cd "C:/CurrentDevelopment/touchUIPCB/touchUI_Bringup/STM32CubeIDE/Appli/Debug"
	echo y | "C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_SigningTool_CLI.exe" -bin "touchUI_BringUP_Appli.bin" -nk -of 0x80000000 -t fsbl -o "Project-trusted.bin" -hv 2.3 -dump "Project-trusted.bin"
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified post-build

-include ../makefile.targets

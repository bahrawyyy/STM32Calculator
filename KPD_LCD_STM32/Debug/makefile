################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Stm32_F103C6_Drivers/Lcd/subdir.mk
-include Stm32_F103C6_Drivers/KPD/subdir.mk
-include Stm32_F103C6_Drivers/GPIO/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
KPD_LCD_STM32.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
KPD_LCD_STM32.list \

OBJCOPY_HEX += \
KPD_LCD_STM32.hex \

OBJCOPY_BIN += \
KPD_LCD_STM32.bin \


# All Target
all: KPD_LCD_STM32.elf secondary-outputs

# Tool invocations
KPD_LCD_STM32.elf: $(OBJS) $(USER_OBJS) C:\Users\Abdallah\STM32CubeIDE\workspace_1.4.0\KPD_LCD_STM32\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "KPD_LCD_STM32.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Abdallah\STM32CubeIDE\workspace_1.4.0\KPD_LCD_STM32\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="KPD_LCD_STM32.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

KPD_LCD_STM32.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "KPD_LCD_STM32.list"
	@echo 'Finished building: $@'
	@echo ' '

KPD_LCD_STM32.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "KPD_LCD_STM32.hex"
	@echo 'Finished building: $@'
	@echo ' '

KPD_LCD_STM32.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "KPD_LCD_STM32.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

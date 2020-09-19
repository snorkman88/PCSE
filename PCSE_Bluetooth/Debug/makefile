################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include example/src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PCSE_Bluetooth.elf

# Tool invocations
PCSE_Bluetooth.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/snorkman/LPCXpresso/borra/lpc_chip_43xx/Debug" -L"/home/snorkman/LPCXpresso/borra/lpc_board_nxp_lpcxpresso_4337/Debug" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -T monitor_bat_Debug.ld -o "PCSE_Bluetooth.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) PCSE_Bluetooth.elf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "PCSE_Bluetooth.elf";  arm-none-eabi-objcopy -v -O binary "PCSE_Bluetooth.elf" "PCSE_Bluetooth.bin" ; # checksum -p LPC4337 -d "PCSE_Bluetooth.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

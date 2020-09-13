################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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
LSS += \
send_location_sms.lss \

FLASH_IMAGE += \
send_location_sms.hex \

EEPROM_IMAGE += \
send_location_sms.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: send_location_sms.elf secondary-outputs

# Tool invocations
send_location_sms.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,send_location_sms.map -mmcu=atmega32 -o "send_location_sms.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

send_location_sms.lss: send_location_sms.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S send_location_sms.elf  >"send_location_sms.lss"
	@echo 'Finished building: $@'
	@echo ' '

send_location_sms.hex: send_location_sms.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex send_location_sms.elf  "send_location_sms.hex"
	@echo 'Finished building: $@'
	@echo ' '

send_location_sms.eep: send_location_sms.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex send_location_sms.elf  "send_location_sms.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: send_location_sms.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 send_location_sms.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) send_location_sms.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

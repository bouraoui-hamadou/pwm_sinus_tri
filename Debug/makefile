################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Libraries/subdir.mk
-include Dave/Generated/TIMER/subdir.mk
-include Dave/Generated/PWM_CCU8/subdir.mk
-include Dave/Generated/PIN_INTERRUPT/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_CCU8/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_ADC/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/ADC_MEASUREMENT/subdir.mk
-include Dave/Generated/subdir.mk
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
SECONDARY_FLASH += \
PWM_display.hex \

SECONDARY_LIST += \
PWM_display.lst \

SECONDARY_SIZE += \
PWM_display.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "PWM_display.map"

TOOLCHAIN_ROOT=D:/4.5.0.202105191637/eclipse/ARM-GCC-49
PROJECT_LOC=D:/4.5.0.202105191637/eclipse/workspace/PWM_display

# All Target
all: PWM_display.elf secondary-outputs

# Tool invocations
PWM_display.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -u _printf_float -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "PWM_display.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
PWM_display.hex: PWM_display.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "PWM_display.elf" "PWM_display.hex"
	@echo 'Finished building: $@'
	@echo.
PWM_display.lst: PWM_display.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "PWM_display.elf" > "PWM_display.lst"
	@echo 'Finished building: $@'
	@echo.
PWM_display.siz: PWM_display.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "PWM_display.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/ADC_MEASUREMENT/adc_measurement.o Dave/Generated/ADC_MEASUREMENT/adc_measurement_conf.o Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/GLOBAL_ADC/global_adc.o Dave/Generated/GLOBAL_ADC/global_adc_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/GLOBAL_CCU8/global_ccu8.o Dave/Generated/GLOBAL_CCU8/global_ccu8_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/PIN_INTERRUPT/pin_interrupt.o Dave/Generated/PIN_INTERRUPT/pin_interrupt_conf.o Dave/Generated/PWM_CCU8/pwm_ccu8.o Dave/Generated/PWM_CCU8/pwm_ccu8_conf.o Dave/Generated/TIMER/timer.o Dave/Generated/TIMER/timer_conf.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o 
	-$(RM) Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o Libraries/lcd-routines.o Startup/startup_XMC4500.o Startup/system_XMC4500.o main.o  PWM_display.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

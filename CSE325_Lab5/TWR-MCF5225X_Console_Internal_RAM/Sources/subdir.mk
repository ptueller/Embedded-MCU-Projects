################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LED.c" \
"../Sources/TWR-MCF5225X_sysinit.c" \
"../Sources/console_io_cf.c" \
"../Sources/dip.c" \
"../Sources/exceptions.c" \
"../Sources/i2c.c" \
"../Sources/main.c" \
"../Sources/oct_ledm.c" \
"../Sources/oct_nunchuk.c" \
"../Sources/pit.c" \
"../Sources/pot.c" \
"../Sources/pwm.c" \
"../Sources/qspi.c" \
"../Sources/rng.c" \
"../Sources/switch.c" \
"../Sources/timer.c" \
"../Sources/uart_support.c" \

C_SRCS += \
../Sources/LED.c \
../Sources/TWR-MCF5225X_sysinit.c \
../Sources/console_io_cf.c \
../Sources/dip.c \
../Sources/exceptions.c \
../Sources/i2c.c \
../Sources/main.c \
../Sources/oct_ledm.c \
../Sources/oct_nunchuk.c \
../Sources/pit.c \
../Sources/pot.c \
../Sources/pwm.c \
../Sources/qspi.c \
../Sources/rng.c \
../Sources/switch.c \
../Sources/timer.c \
../Sources/uart_support.c \

S_SRCS += \
../Sources/int.s \

S_SRCS_QUOTED += \
"../Sources/int.s" \

OBJS += \
./Sources/LED_c.obj \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dip_c.obj \
./Sources/exceptions_c.obj \
./Sources/i2c_c.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/oct_ledm_c.obj \
./Sources/oct_nunchuk_c.obj \
./Sources/pit_c.obj \
./Sources/pot_c.obj \
./Sources/pwm_c.obj \
./Sources/qspi_c.obj \
./Sources/rng_c.obj \
./Sources/switch_c.obj \
./Sources/timer_c.obj \
./Sources/uart_support_c.obj \

OBJS_QUOTED += \
"./Sources/LED_c.obj" \
"./Sources/TWR-MCF5225X_sysinit_c.obj" \
"./Sources/console_io_cf_c.obj" \
"./Sources/dip_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/i2c_c.obj" \
"./Sources/int_s.obj" \
"./Sources/main_c.obj" \
"./Sources/oct_ledm_c.obj" \
"./Sources/oct_nunchuk_c.obj" \
"./Sources/pit_c.obj" \
"./Sources/pot_c.obj" \
"./Sources/pwm_c.obj" \
"./Sources/qspi_c.obj" \
"./Sources/rng_c.obj" \
"./Sources/switch_c.obj" \
"./Sources/timer_c.obj" \
"./Sources/uart_support_c.obj" \

C_DEPS += \
./Sources/LED_c.d \
./Sources/TWR-MCF5225X_sysinit_c.d \
./Sources/console_io_cf_c.d \
./Sources/dip_c.d \
./Sources/exceptions_c.d \
./Sources/i2c_c.d \
./Sources/main_c.d \
./Sources/oct_ledm_c.d \
./Sources/oct_nunchuk_c.d \
./Sources/pit_c.d \
./Sources/pot_c.d \
./Sources/pwm_c.d \
./Sources/qspi_c.d \
./Sources/rng_c.d \
./Sources/switch_c.d \
./Sources/timer_c.d \
./Sources/uart_support_c.d \

OBJS_OS_FORMAT += \
./Sources/LED_c.obj \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dip_c.obj \
./Sources/exceptions_c.obj \
./Sources/i2c_c.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/oct_ledm_c.obj \
./Sources/oct_nunchuk_c.obj \
./Sources/pit_c.obj \
./Sources/pot_c.obj \
./Sources/pwm_c.obj \
./Sources/qspi_c.obj \
./Sources/rng_c.obj \
./Sources/switch_c.obj \
./Sources/timer_c.obj \
./Sources/uart_support_c.obj \

C_DEPS_QUOTED += \
"./Sources/LED_c.d" \
"./Sources/TWR-MCF5225X_sysinit_c.d" \
"./Sources/console_io_cf_c.d" \
"./Sources/dip_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/i2c_c.d" \
"./Sources/main_c.d" \
"./Sources/oct_ledm_c.d" \
"./Sources/oct_nunchuk_c.d" \
"./Sources/pit_c.d" \
"./Sources/pot_c.d" \
"./Sources/pwm_c.d" \
"./Sources/qspi_c.d" \
"./Sources/rng_c.d" \
"./Sources/switch_c.d" \
"./Sources/timer_c.d" \
"./Sources/uart_support_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/LED_c.obj: ../Sources/LED.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/LED.args" -o "Sources/LED_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/TWR-MCF5225X_sysinit_c.obj: ../Sources/TWR-MCF5225X_sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/TWR-MCF5225X_sysinit.args" -o "Sources/TWR-MCF5225X_sysinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/console_io_cf_c.obj: ../Sources/console_io_cf.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/console_io_cf.args" -o "Sources/console_io_cf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dip_c.obj: ../Sources/dip.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/dip.args" -o "Sources/dip_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/i2c_c.obj: ../Sources/i2c.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/i2c.args" -o "Sources/i2c_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/int_s.obj: ../Sources/int.s
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Assembler'
	"$(CF_ToolsDirEnv)/mwasmmcf" @@"Sources/int.args" -o "Sources/int_s.obj" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/oct_ledm_c.obj: ../Sources/oct_ledm.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/oct_ledm.args" -o "Sources/oct_ledm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/oct_nunchuk_c.obj: ../Sources/oct_nunchuk.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/oct_nunchuk.args" -o "Sources/oct_nunchuk_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_c.obj: ../Sources/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pit.args" -o "Sources/pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pot_c.obj: ../Sources/pot.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pot.args" -o "Sources/pot_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pwm_c.obj: ../Sources/pwm.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pwm.args" -o "Sources/pwm_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/qspi_c.obj: ../Sources/qspi.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/qspi.args" -o "Sources/qspi_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rng_c.obj: ../Sources/rng.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/rng.args" -o "Sources/rng_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/switch_c.obj: ../Sources/switch.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/switch.args" -o "Sources/switch_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/timer_c.obj: ../Sources/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #17 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/timer.args" -o "Sources/timer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_support_c.obj: ../Sources/uart_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #18 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart_support.args" -o "Sources/uart_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '



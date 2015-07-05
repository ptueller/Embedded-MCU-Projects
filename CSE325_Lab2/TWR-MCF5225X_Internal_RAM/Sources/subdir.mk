################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/LED.c" \
"../Sources/TWR-MCF5225X_sysinit.c" \
"../Sources/dip.c" \
"../Sources/exceptions.c" \
"../Sources/main.c" \
"../Sources/rng.c" \
"../Sources/switch.c" \
"../Sources/timer.c" \
"../Sources/uart_support.c" \

C_SRCS += \
../Sources/LED.c \
../Sources/TWR-MCF5225X_sysinit.c \
../Sources/dip.c \
../Sources/exceptions.c \
../Sources/main.c \
../Sources/rng.c \
../Sources/switch.c \
../Sources/timer.c \
../Sources/uart_support.c \

OBJS += \
./Sources/LED_c.obj \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/dip_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/rng_c.obj \
./Sources/switch_c.obj \
./Sources/timer_c.obj \
./Sources/uart_support_c.obj \

OBJS_QUOTED += \
"./Sources/LED_c.obj" \
"./Sources/TWR-MCF5225X_sysinit_c.obj" \
"./Sources/dip_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/main_c.obj" \
"./Sources/rng_c.obj" \
"./Sources/switch_c.obj" \
"./Sources/timer_c.obj" \
"./Sources/uart_support_c.obj" \

C_DEPS += \
./Sources/LED_c.d \
./Sources/TWR-MCF5225X_sysinit_c.d \
./Sources/dip_c.d \
./Sources/exceptions_c.d \
./Sources/main_c.d \
./Sources/rng_c.d \
./Sources/switch_c.d \
./Sources/timer_c.d \
./Sources/uart_support_c.d \

OBJS_OS_FORMAT += \
./Sources/LED_c.obj \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/dip_c.obj \
./Sources/exceptions_c.obj \
./Sources/main_c.obj \
./Sources/rng_c.obj \
./Sources/switch_c.obj \
./Sources/timer_c.obj \
./Sources/uart_support_c.obj \

C_DEPS_QUOTED += \
"./Sources/LED_c.d" \
"./Sources/TWR-MCF5225X_sysinit_c.d" \
"./Sources/dip_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/main_c.d" \
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

Sources/dip_c.obj: ../Sources/dip.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/dip.args" -o "Sources/dip_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/rng_c.obj: ../Sources/rng.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/rng.args" -o "Sources/rng_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/switch_c.obj: ../Sources/switch.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/switch.args" -o "Sources/switch_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/timer_c.obj: ../Sources/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/timer.args" -o "Sources/timer_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_support_c.obj: ../Sources/uart_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart_support.args" -o "Sources/uart_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/general.c \
../src/h_bridge.c \
../src/main.c \
../src/pwm_expander.c \
../src/pwm_expander_working.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/uart.c 

OBJS += \
./src/ADC.o \
./src/general.o \
./src/h_bridge.o \
./src/main.o \
./src/pwm_expander.o \
./src/pwm_expander_working.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/uart.o 

C_DEPS += \
./src/ADC.d \
./src/general.d \
./src/h_bridge.d \
./src/main.d \
./src/pwm_expander.d \
./src/pwm_expander_working.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103RBTx -DNUCLEO_F103RB -DDEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"F:/STM_projects/Yasha/Utilities/STM32F1xx-Nucleo" -I"F:/STM_projects/Yasha/StdPeriph_Driver/inc" -I"F:/STM_projects/Yasha/inc" -I"F:/STM_projects/Yasha/CMSIS/device" -I"F:/STM_projects/Yasha/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



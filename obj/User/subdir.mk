################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/isr.c \
../User/main.c 

OBJS += \
./User/isr.o \
./User/main.o 

C_DEPS += \
./User/isr.d \
./User/main.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@	@	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -mno-save-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized  -g -I"../User" -I"../Libraries/Code" -I"../CODE" -I"../Libraries/board" -I"../Libraries/seekfree_peripheral" -I"../Libraries/seekfree_libraries" -I"../Libraries/wch_libraries/Startup" -I"../Libraries/wch_libraries/Peripheral" -I"../Libraries/wch_libraries/Core" -I"../Libraries/Motor" -I"../TYIOT" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@


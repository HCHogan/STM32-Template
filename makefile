#工程的名称及最后生成文件的名字
TARGET = STM32-Template

#设定临时性环境变量
export CC             = arm-none-eabi-g++
export AS             = arm-none-eabi-as
export LD             = arm-none-eabi-ld
export OBJCOPY        = arm-none-eabi-objcopy

#读取当前工作目录
TOP=$(shell pwd)

#设定包含文件目录
INC_FLAGS= -I /usr/arm-none-eabi/include/c++/12.2.0 \
		   -I /usr/arm-none-eabi/include/c++/12.2.0/arm-none-eabi \
		   -I $(TOP)/Start 			\
           -I $(TOP)/User 			\
		   -I $(TOP)/Library/inc 	\
		   -I $(TOP)/Library/src 	\
		   -I $(TOP)/Hardware 		\
		   -I $(TOP)/System

CFLAGS =  -W -Wall -g -mcpu=cortex-m3 -mthumb -D STM32F10X_MD -D USE_STDPERIPH_DRIVER $(INC_FLAGS) -O0 -std=c++11 -mfloat-abi=soft -fsigned-char -ffreestanding -nostartfiles -fdata-sections -ffunction-sections
C_SRC=$(shell find ./ -name '*.c')  
C_OBJ=$(C_SRC:%.c=%.o)          

CXX_SRC=$(shell find ./ -name '*.cpp')
CXX_OBJ=$(CXX_SRC:%.cpp=%.o)

ASFLAGS = -W -Wall -g -mcpu=cortex-m3 -mthumb
ASM_SRC = $(shell find ./ -name '*.s')
ASM_OBJ = $(ASM_SRC:%.s=%.o)

.PHONY: all clean update flash

all:$(C_OBJ) $(CXX_OBJ)
	$(CC) $(C_OBJ) $(CXX_OBJ) -T stm32_flash.ld -o $(TARGET).elf   -mthumb -mcpu=cortex-m3 -Wl,--start-group -lc -lm -Wl,--end-group -specs=nano.specs -specs=nosys.specs -static -Wl,-cref,-u,Reset_Handler -Wl,-Map=Project.map -Wl,--gc-sections -Wl,--defsym=malloc_getpagesize_P=0x80 
	$(OBJCOPY) $(TARGET).elf  $(TARGET).bin -Obinary 
	$(OBJCOPY) $(TARGET).elf  $(TARGET).hex -Oihex

$(C_OBJ):%.o:%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(CXX_OBJ):%.o:%.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(shell find ./ -name '*.o')
	rm -f $(shell find ./ -name '*.d')
	rm -f $(shell find ./ -name '*.map')
	rm -f $(shell find ./ -name '*.elf')
	rm -f $(shell find ./ -name '*.bin')
	rm -f $(shell find ./ -name '*.hex')

update:
	openocd -f /usr/share/openocd/scripts/interface/stlink-v2.cfg  -f /usr/share/openocd/scripts/target/stm32f1x_stlink.cfg -c init -c halt -c "flash write_image erase $(TOP)/LED_project.hex" -c reset -c shutdown

flash: $(TARGET).bin
	st-flash write $<0x8000000
 


 











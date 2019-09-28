.PHONY: default size flash flash-dfu flash-jtag flash-uart release new clean mrproper

SRC_FILES:=$(wildcard *.c)

# build tests? (comment out = yes)
SRC_FILES:=$(filter-out tests.c,$(SRC_FILES))

TMP_DIR:=.tmp
OBJ_FILES:=$(patsubst %.c,$(TMP_DIR)/%.o,$(SRC_FILES))
DEP_FILES:=$(patsubst %.c,$(TMP_DIR)/%.d,$(SRC_FILES))

STARTUP_FILE:=startup_stm32f103x6.s
LINKER_SCRIPT:=STM32F103X6_FLASH.ld

CMSIS_DIRS:=
CMSIS_DIRS+=STM32Cube_FW_F1_V1.7.0/Drivers/CMSIS/Include/
CMSIS_DIRS+=STM32Cube_FW_F1_V1.7.0/Drivers/CMSIS/Device/ST/STM32F1xx/Include/

DEFS:=
DEFS+=STM32F10X_CL

VERSION_SHORT:=$(shell git describe --dirty=+       2>/dev/null || echo "unknown")
VERSION_LONG:=$(shell git describe --dirty=+ --long 2>/dev/null || echo "unknown")
TIMESTAMP:=$(shell date +'%d %b %Y %I:%M:%S %p')

CFLAGS:=
CFLAGS+=-std=gnu99 -g -O0 -Wall
CFLAGS+=-mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m3
CFLAGS+=-fsingle-precision-constant -Wdouble-promotion
CFLAGS+=$(addprefix -I,$(CMSIS_DIRS))
CFLAGS+=$(addprefix -D,$(DEFS))

LDFLAGS:=
LDFLAGS+=-z max-page-size=1024
LDFLAGS+=-T $(LINKER_SCRIPT)

TMP_FILES:=main.elf main.map main.hex main.bin $(OBJ_FILES) $(DEP_FILES)

default: main.bin size

size: main.elf
	arm-none-eabi-size -tA $^

flash: flash-jtag

flash-dfu: main.bin
	dfu-util -a 0 -s 0x08000000:leave -D main.bin

flash-jtag: main.bin
	st-flash --reset write $^ 0x08000000

flash-uart: main.hex
	stm32flash -w $^ -R $(UART_DEV)

gdb: main.elf
	gdb-multiarch -ex 'source scripts/startup.gdb'

release: main.hex
	tar -caf led_chain_binary_$(VERSION_SHORT).tgz --xform 's!^!led_chain_$(VERSION_SHORT)/!' main.elf main.hex main.map
	git archive HEAD --format tar.gz --prefix led_chain_$(VERSION_SHORT)/ > led_chain_$(VERSION_SHORT).tgz

new: clean default

clean:
	rm -f $(TMP_FILES)

mrproper: clean
	rm -rf $(TMP_DIR) .$(TMP_DIR).dir


$(TMP_DIR): %:
	mkdir $@

ifneq ($(wildcard $(TMP_DIR)/.),)
# if $(TMP_DIR) already exists, then don't depend on it
$(patsubst %,.%.dir,$(TMP_DIR)): .%.dir:
else
# if $(TMP_DIR) doesn't exist, then depend on it too
$(patsubst %,.%.dir,$(TMP_DIR)): .%.dir: %
endif
	touch $@

main.bin: main.elf Makefile
	arm-none-eabi-objcopy -O binary $(filter %.elf,$^) $@

main.hex: main.elf Makefile
	arm-none-eabi-objcopy -O ihex $(filter %.elf,$^) $@

main.elf: $(OBJ_FILES) $(STARTUP_FILE) $(LINKER_SCRIPT) Makefile
	arm-none-eabi-gcc -MD $(CFLAGS) $(addprefix -Xlinker ,$(LDFLAGS) -Map=$(patsubst %.elf,%.map,$@)) $(filter %.s %.o,$^) -o $@

$(TMP_DIR)/%.o: %.c Makefile .$(TMP_DIR).dir
	arm-none-eabi-gcc -MD $(CFLAGS) $(filter %.c,$^) -c -o $@

-include $(DEP_FILES)

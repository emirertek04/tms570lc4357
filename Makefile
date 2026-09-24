CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

CFLAGS  = -mcpu=cortex-r5 -marm -Wall -O0 -g -Iinclude
LDFLAGS = -Tlinker/tms570lc4357.ld -nostartfiles -Wl,-Map=build/output.map

SRCS_C  = src/system.c src/gio.c src/main.c
SRCS_S  = src/startup.s

OBJS    = build/startup.o build/system.o build/gio.o build/main.o

TARGET  = build/firmware

all: $(TARGET).bin

build:
	mkdir -p build

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.s | build
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf build

.PHONY: all clean
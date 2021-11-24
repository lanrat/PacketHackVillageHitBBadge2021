###############################################################################
# Makefile for the project OLEDi2C
###############################################################################

## General Flags
PROJECT = OLEDi2C
MCU = atmega32
TARGET = OLEDi2C.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=OLEDi2C.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = OLEDi2C.o

## Objects explicitly added by the user
LINKONLYOBJECTS =

## Build
all: $(TARGET) OLEDi2C.hex OLEDi2C.eep OLEDi2C.lss

## Compile
OLEDi2C.o: OLEDi2C.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ #|| exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

flash: OLEDi2C.hex
	avrdude -p m32 -C +tigard.conf -c tigard -B 8 -v -e -U flash:w:OLEDi2C.hex:i

dump:
		avrdude -p m32 -C +tigard.conf -c tigard -B 8 -v -e -U flash:r:OLEDi2C.read.hex:i

fuse-read:
		avrdude -p m32 -C +tigard.conf -c tigard -B 8 -v -e -U lfuse:r:lfuse:r -U hfuse:r:hfuse:r

fuse-write:
		avrdude -p m32 -C +tigard.conf -c tigard -B 8 -v -e -U lfuse:w:lfuse:r -U hfuse:w:hfuse:r


dump-usbasp:
		avrdude -p m32 -c usbasp -B 8 -v -e -U eeprom:r:OLEDi2C.read.hex:i

flash-usbasp: OLEDi2C.hex
	avrdude -p m32 -c usbasp -B 8 -v -e -U flash:w:OLEDi2C.hex:i


## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) OLEDi2C.elf dep/* OLEDi2C.hex OLEDi2C.eep OLEDi2C.lss OLEDi2C.map

flash: dep/OLEDi2C.hex

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

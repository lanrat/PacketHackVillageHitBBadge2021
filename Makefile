###############################################################################
# Makefile for the project OLEDi2C
###############################################################################

## General Flags
PROJECT = OLEDi2C
MCU = atmega32
TARGET = dep/OLEDi2C.elf
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
LDFLAGS +=  -Wl,-Map=dep/OLEDi2C.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = OLEDi2C.o

HEX = dep/OLEDi2C.hex

## Objects explicitly added by the user
LINKONLYOBJECTS =

## Build
all: $(TARGET) $(HEX)

## Compile
OLEDi2C.o: OLEDi2C.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

flash: flash-tigard

flash-usbasp: $(HEX)
	avrdude -p m32 -c usbasp -B 8 -v -e -U flash:w:$(HEX):i

flash-tigard: $(HEX)
	avrdude -p m32 -C +conf/tigard.conf -c tigard -B 8 -v -e -U flash:w:$(HEX):i

fuse-read-tigard:
		avrdude -p m32 -C +conf/tigard.conf -c tigard -B 8 -v -e -U lfuse:r:conf/lfuse:r -U hfuse:r:conf/hfuse:r

fuse-write-tigard:
		avrdude -p m32 -C +conf/tigard.conf -c tigard -B 8 -v -e -U lfuse:w:conf/lfuse:r -U hfuse:w:conf/hfuse:r

## Clean target
.PHONY: clean flash
clean:
	-rm -rf $(OBJECTS) dep/*

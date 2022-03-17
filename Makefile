TARGET=ampduino
AMPDUINO_VERSION=0.1
ARDUINO_LIBS = EEPROM SPI Wire

# Linux tends to put it at /usr/share/arduino, check there
ifneq ("$(wildcard /usr/share/arduino/revisions.txt)","")
ARDUINO_DIR = /usr/share/arduino
endif

# If user has installed arduino into /opt, it's probably
# because the host OS has a broken version, prefer it.
ifneq ("$(wildcard /opt/arduino/arduino)","")
ARDUINO_DIR = /opt/arduino
endif

ifneq ("$(wildcard /usr/bin/avrdude)", "")
AVRDUDE          = /usr/bin/avrdude
AVR_TOOLS_DIR    = /usr
endif

# If the host avrdude is broken, it can be put into /opt/arduino
ifneq ("$(wildcard /opt/arduino/bin/avrdude)", "")
AVRDUDE          = /opt/arduino/bin/avrdude
AVR_TOOLS_DIR    = /opt/arduino
endif

PROJECT_DIR = .
ARDMK_DIR = ./mk
USER_LIB_PATH    :=  ${PROJECT_DIR}/lib
BUILDFLAGS = -DAMPDUINO=1
COMM_CFLAGS = ${BUILDFLAGS}-I./include -Wall -pedantic -Wno-error
CFLAGS_STD       = ${COMM_CFLAGS} -std=gnu11 -Os
CXXFLAGS_STD     = ${COMM_CFLAGS} -std=gnu++11 -Os -fno-rtti 
CURRENT_DIR      = $(shell basename ${CURDIR})
OBJDIR           = ${PROJECT_DIR}/bin/${BOARD_TAG}/${CURRENT_DIR}

CXXFLAGS_STD += -I./ext/RF24

# Bring in board configuration
include ./board.mk
include $(ARDMK_DIR)/Arduino.mk
include mk/customization.mk
include mk/firmware.mk
include mk/esp-serial.mk
include mk/gen-eeprom.mk
include mk/indent.mk
include mk/clean.mk
include mk/install.mk

# Build firmwares, if needed before our source
world: firmware esp-serial-world all

TARBALL_DATE=$(date +%Y-%m-%d)

# Roll a distribution tarball
dist tarball: distclean
	tar -C .. -jcvf ../ampduino-${AMPDUINO_VERSION}-${TARBALL_DATE}.tar.bz2 ampduino

symlinks:
	[ ! -L atu-100-mplab.production.elf ] && ln -s atu-100/dist/default/production/atu-100-mplab.production.elf .
	[ ! -L atu-100-mplab.production.hex ] && ln -s atu-100/dist/default/production/atu-100-mplab.production.hex .
	[ ! -L ubitx.hex ] && ln -s ubitx/bin/nano/ubitx/ubitx.hex .
	[ ! -L ubitx.elf ] && ln -s ubitx/bin/nano/ubitx/ubitx.bin .
	[ ! -L esp-serial.elf ] && ln -s esp-serial/esp-serial.elf .

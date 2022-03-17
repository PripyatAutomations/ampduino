#
# Here you should define your Radio and it's components
#
# The build system will figure out the rest...

# If using a mega
BOARD_TAG         = mega
BOARD_SUB = atmega2560
FLASH_PROTO=atmega328p

# If using a nano
#BOARD_TAG = nano
#BOARD_SUB = atmega328
#FLASH_PROTO=atmega328p

# Is it an avr type board?
TARGET_AVR = y

# Serial monitor port
MONITOR_PORT      = /dev/ttyUSB0
# Serial monitor (and CAT) baudrate
MONITOR_BAUDRATE  = 115200

FLASH_BAUDRATE  = 57600

RADIO_TYPE = ubitx

#########
# XXX: Move this stuff into configs!
#########

#######################
# Set the color theme #
#######################
# N/A here?
THEME := night

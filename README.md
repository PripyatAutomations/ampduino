Be sure to git submodule init; git submodule update before trying to build

*********************
** USE make world ***
*********************
If you do not want to use the prebuilt firmware for atu-100 or ubitx,
use 'make all', otherwise use 'make world' to build them!



------

Building atu-100 firmware requires microchip xc8 compiler in /opt/microchip/xc8.

Building ubitx requires the same toolchain needed for ampduino.

This is a bit rough but it's what i use to run my amplifier.

Protocol will change as we discover flaws, so try to keep up-to-date.

Edit ampduino_config.h to configure power-on defaults until EEPROM code is added.


Eventually most all things will be configured from a small text file converted to
a source file that will connect all the bits in the device to the CAT interface...


This is still very much a work in progress and things will change. There is no
working API yet, so you'll need to make sure you have the latest version and
dig through the source as needed.

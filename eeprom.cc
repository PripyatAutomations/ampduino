//
// EEPROM settings support
//
// For now, we load compile-time defaults and in the near future
// will support saving and loading configuration from EEPROM.

#include <string.h>
#include <EEPROM.h>
#define	EEPROM_C
#include "eeprom-data.h"
#include "ampduino.h"
// create data array

AmpduinoConfig cfg;

// Load configuration (XXX: move to eeprom)
bool config_load(void) {
    // Clear our in-memory structure
    memset(&cfg, 0, sizeof(AmpduinoConfig));
    memset(&cfg.status, 0, sizeof(cfg.status));

    // Initialize some hard-coded default configuration
    //
    cfg.max_swr = MAX_SWR;
    cfg.max_power = MAX_POWER;
    cfg.monitor_atten = MONITOR_ATTEN;
    cfg.max_finals_temp = MAX_TEMP_FINALS;
    cfg.max_system_temp = MAX_TEMP_SYSTEM;
    cfg.max_current = MAX_CURRENT;
    cfg.min_voltage = MIN_VOLTAGE;
    cfg.fan_speed = FAN_SPEED_IDLE;
    return true;
}

bool EEPROMConfig::FactoryDefaults(void) {
    this->LoadConfig(factory_defaults);
    return true;
}

bool EEPROMConfig::LoadConfig(const char *cdata) {
    if (cdata == NULL)
       return false;

    unsigned int offset = 0, eeprom_sz = CF_EEPROM_SZ;
    unsigned int fd_sz = strlen(factory_defaults);
    unsigned int version = AMPDUINO_VERSION;

    // Set software version
    EEPROM.put(0, (unsigned char)(version & 0xff));
    EEPROM.put(1, (unsigned char)(version >> 8));

    // Skip past version
    offset = 2;
    for (unsigned int i = 0; ((i < fd_sz) && i++); i++) {
       EEPROM.put(i + 2, factory_defaults[i]);
       offset++;
    }

    // Clear the remaining eeprom contents up to last 2 bytes (sum)
    for (; offset < (EEPROM.length() - 2); offset++) {
        EEPROM.write(offset, 0);
    }

    // Calculate checksum and store it in EEPROM
    unsigned int sum = this->CRC();
    EEPROM.write(EEPROM.length() - 1, (unsigned char)(sum & 0xff));
    EEPROM.write(EEPROM.length(), (unsigned char)(sum >> 8));
    return true;
}

bool EEPROMConfig::SaveConfig(void) {
    return true;
}

// Create Checksum from EEPROM contents, excluding last two bytes where sum is stored
unsigned long EEPROMConfig::CRC(void) {
    const unsigned long crc_table[16] = {
      0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
      0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
      0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
      0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
    };

    unsigned long crc = ~0L;

    // Checksum is stored in last 2 bytes, so ignore them...
    for (unsigned int index = 0; index < EEPROM.length() - 2; ++index) {
       crc = crc_table[(crc ^ EEPROM[index]) & 0x0f] ^ (crc >> 4);
       crc = crc_table[(crc ^ (EEPROM[index] >> 4)) & 0x0f] ^ (crc >> 4);
       crc = ~crc;
    }
    return crc;
}

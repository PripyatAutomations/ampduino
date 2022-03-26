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

// Place the builtin ('factory' default) configuration into eeprom and reboot
bool EEPROMConfig::FactoryDefaults(void) {
    /////////////////////
    // Verify checksum //
    /////////////////////
//    unsigned int read_sum = 0;
//    unsigned char lsb, msb;

    // Read MSB
//    msb = EEPROM.read(EEPROM.length() - 1);

    // Read LSB
//    lsb = EEPROM.read(EEPROM.length());

    // combine
//    read_sum = (unsigned)lsb << 8 | msb;

    // compare stored and calculated CRCs
//    if (this->CRC() != read_sum) {
//       // Alert("Invalid EEPROM config");
//       return false;
//    }

    // Load the EEPROM
    this->LoadConfig(factory_defaults);
    reboot();
    return true;
}

bool EEPROMConfig::LoadConfig(const char *cdata) {
    // We can't load empty config...
    if (cdata == NULL)
       return false;

    // XXX: Validation
    // XXX: Parser
    return true;
}

bool EEPROMConfig::SaveConfig(void) {
    unsigned int offset = 0;
    unsigned int fd_sz = strlen(factory_defaults);
    unsigned int version = AMPDUINO_VERSION;

    // Set software version
    // Write LSB
    EEPROM.put(0, (unsigned char)(version & 0xff));
    // Write MSB
    EEPROM.put(1, (unsigned char)(version >> 8));

    // Skip past version bytes
    offset = 2;
    for (unsigned int i = 0; ((i < fd_sz) && i++); i++) {
       EEPROM.put(i + 2, factory_defaults[i]);
       offset++;
    }

    // Write terminating byte (255);
    offset++;
    EEPROM.write(offset, 0xff);

    // Clear the remaining eeprom contents up to last 2 bytes (sum)
    for (; offset < (EEPROM.length() - 2); offset++) {
        EEPROM.write(offset, 0);
    }

    // Calculate checksum and store it in EEPROM
    unsigned int sum = this->CRC();

    // Write MSB
    EEPROM.write(EEPROM.length() -1, (unsigned char)(sum >> 8));

    // Write LSB
    EEPROM.write(EEPROM.length(), (unsigned char)(sum & 0xff));
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

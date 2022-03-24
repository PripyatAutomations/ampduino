//
// Configuration support
//
#include "ampduino.h"
#include <EEPROM.h>

bool Config::FreePtr(void) {
    if (this->ptr != NULL && this->alloced) {
       free(this->ptr);
       this->alloced = false;
    }

    return true;
}

bool Config::LoadFromString(const char *data) {
    if (data == NULL)
       return false;

    this->FreePtr();
    this->ptr = data;
    this->Parse();

    return true;
}

bool Config::LoadFromEEPROM(void) {
    char *eeprom_data = NULL;

    this->FreePtr();

    if (EEPROM.length() == 0)
       return false;

    if ((eeprom_data = malloc(EEPROM.length())) == NULL)
       return false;

    // set flag so we can free this later...
    this->alloced = true;
    this->ptr = eeprom_data;

    // Read in EEPROM data...

    // Confirm checksum
    this->Parse();

    return true;
}


bool Config::Parse(void) {
    if (this->ptr == NULL)
       return false;

    // State
    int depth = 0;
    char *section = NULL;

    return true;
}

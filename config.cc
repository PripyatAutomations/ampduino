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

bool Config::LoadFromString(char *data) {
    if (data == NULL)
       return false;

    this->FreePtr();
    this->ptr = (char *)data;
    this->Parse();

    return true;
}

bool Config::LoadFromEEPROM(void) {
    char *eeprom_data = NULL;

    this->FreePtr();

    if (EEPROM.length() == 0)
       return false;

    if ((eeprom_data = (char *)malloc(EEPROM.length())) == NULL)
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

// Load configuration (XXX: move to eeprom)
Config::Config(void) {
    this->max_swr = MAX_SWR;
    this->max_power = MAX_POWER;
    this->monitor_atten = MONITOR_ATTEN;
    this->max_finals_temp = MAX_TEMP_FINALS;
    this->max_system_temp = MAX_TEMP_SYSTEM;
    this->max_current = MAX_CURRENT;
    this->min_voltage = MIN_VOLTAGE;
    this->fan_speed = FAN_SPEED_IDLE;
}

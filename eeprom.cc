//
// EEPROM settings support
//
// For now, we load compile-time defaults and in the near future
// will support saving and loading configuration from EEPROM.

#include <string.h>
#include <EEPROM.h>
#include "ampduino.h"
#include "eeprom-data.h"

AmpduinoConfig cfg;

// Load configuration (XXX: move to eeprom)
bool config_load(void) {
    // Clear our in-memory structure
    memset(&cfg, 0, sizeof(AmpduinoConfig));
    memset(&cfg.status, 0, sizeof(cfg.status));

    // Initialize some hard-coded default configuration
    cfg.max_swr = MAX_SWR;
    cfg.max_power = MAX_POWER;
    cfg.monitor_atten = MONITOR_ATTEN;
    cfg.max_finals_temp = MAX_TEMP_FINALS;
    cfg.max_system_temp = MAX_TEMP_SYSTEM;
    cfg.max_current = MAX_CURRENT;
    cfg.min_voltage = MIN_VOLTAGE;
    cfg.fan_speed = FAN_SPEED_IDLE;
}

bool EEPROMConfig::LoadConfig(void) {
    return true;
}

bool EEPROMConfig::SaveConfig(void) {
    return true;
}

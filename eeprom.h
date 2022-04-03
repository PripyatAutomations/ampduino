//
// Support for storing our configuration in the EEPROM
//
#if	!defined(_eeprom_h)
#define	__eeprom_h
class EEPROMConfig {
    public:
        // Load factory defaults into EEPROM
        bool FactoryDefaults(void);

        // Load the configuration from EEPROM
        bool LoadConfig(void);

        // Save configuration to EEPROM
        bool SaveConfig(void);

        // Generate a CRC of the flash (excluding checksum bytes)
        unsigned long CRC(void);
};

////////////////////////
// EEPROM Data Layout //
////////////////////////

////////////
// Struct //
////////////

#endif

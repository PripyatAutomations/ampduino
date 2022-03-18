#if	!defined(_eeprom_h)
#define	__eeprom_h
class EEPROMConfig {
    public:
        // Load factory defaults into EEPROM
        bool FactoryDefaults(void);

        // Load the configuration from EEPROM
        bool LoadConfig(const char *cdata);

        // Save configuration to EEPROM
        bool SaveConfig(void);
        unsigned long CRC(void);
};
extern AmpduinoConfig cfg;
extern bool config_load(void);

////////////////////////
// EEPROM Data Layout //
////////////////////////

////////////
// Struct //
////////////

#endif

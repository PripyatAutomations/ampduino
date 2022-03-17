#if	!defined(_eeprom_h)
#define	__eeprom_h
class EEPROMConfig {
    public:
        bool LoadConfig(void);
        bool SaveConfig(void);
};
extern AmpduinoConfig cfg;
extern bool config_load(void);

////////////////////////
// EEPROM Data Layout //
////////////////////////

////////////
// Struct //
////////////

/////////////
// Offsets //
/////////////
//	name		offset	// description
#define	EE_VERSION	0	// 4 bytes for version
#define	EE_MY_ADDR	4	// 2 bytes for my address
#define	EE_LPF_BANDS	5	// 1b # LPF filters
#define	EE_BPF_BANDS	6	// 1b # BPF filters
#define	EE_TRANSVERTERS	7	// 1b # transverters
#define	EE_AMPLIFIERS	8	// 1b # amplifiers
#define	EE_SWITCHES	9	// 1b # switches
#define	EE_ANTENNAS	10	// 1b # antennas
#define	EE_ROTORS	11	// 1b # rotors
#define	EE_MAX_SWR	12	// 2b maximum SWR allowed at amp output
#define	EE_MAX_POWER	14	// 2b maximum power output allowed
#define	EE_MON_ATTEN	16	// 2b monitor attenuation
#define	EE_MAX_TEMP_FINAL 18	// 2b maximum temp (C) of finals
#define EE_MAX_TEMP_SYS	20	// 2b maximum temp (C) of system
#define	EE_BATTERY_TYPE	22	// 2b battery type
#define EE_MAX_CURRENT	24	// 2b maximum current before system shutdown
#define	EE_MIN_VOLTAGE	26	// 2b minimum voltage to allow TX
#define	EE_HAVE_FAN	28	// 1b have fan?
#define	EE_FAN_IDLE	29	// 2b idle fan RPM
#define	EE_FAN_TX	31	// 2b TX fan min. RPM
#define	EE_FAN_MAX	33	// 2b max speed fan supports
#define	EE_CRYPT_KEY	35	// 8b encryption key for RF protocol
// XXX: Reserved for future expansion: 43-127 [84b free]
#define	EE_CFG_DATA	128	// 2364b configuration blob
#define	EE_TUNER_NEXT_SLOT 2492	// 1b next slot to store memories in
#define	EE_TUNER_MEMORY	2493	// 1600b Tuner Memories
#define	EE_CHECKSUM	4093	// 2b checksum

#endif

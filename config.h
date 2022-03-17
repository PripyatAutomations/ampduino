//
// Here we handle all build-time configration.
//
// Only things that affect the generated code
// and default settings should end up here.
//
// All other configuration should be stored
// in eeprom configuration

#if	!defined(_config_h)
#define	_config_h

// Set my address (usually 0x02)
////////////////////////////////
#define	CF_RAN_ADDRESS	0x02

// for now, we support direct serial only
#define	CF_SERIAL

// we will support nrf24l01 initially
//ZZ
#define CF_NRF24

// and eventually support LoRa
//ZZ
#define CF_LORA

// LPF bands
#define	MAX_LPF_BANDS	6

// BPF (RX) bands
#define	MAX_BPF_BANDS	10

// Receiver Support
//////////////////////
#define CF_RECEIVERS

// Transmitter Support
//////////////////////
#define CF_TRANSMITTERS

// Transverter support
//////////////////////
//#define CF_TRANVERTERS
#define	MAX_TRANSVERTERS 0

// Amplifier Support
////////////////////
#define CF_AMPLIFIERS

// Filters Support
//////////////////
#define CF_FILTERS

// Tuners Support
/////////////////
#define CF_TUNERS

// Memory slots in auto tuner
#define	MAX_TUNER_MEMORIES 100

// Antenna Switcher Support
//ZZ
#define CF_SWITCHES

// Antennae Switches
#define	MAX_SWITCHES	1
#define	SWITCH_INPUTS	2
#define	SWITCH_OUTPUTS	4

// Antennas Support
///////////////////
#define	MAX_ANTENNAS	4

// Antenna Rotor Support
////////////////////////
//ZZ
#define CF_ROTORS
#define	MAX_ROTORS 1

/////////////////////
// Safety Settings //
/////////////////////
// These need to go into eeprom...
#define	MAX_SWR		2.0	// Maximum SWR to allow (for amp protection)
#define	MAX_POWER	100	// Maximum output power allowed (watts)
#define	MONITOR_ATTEN	31	// Monitor attenuation (db)
#define	MAX_TEMP_FINALS	70	// final temperature in degC
#define	MAX_TEMP_SYSTEM	35	// enclosure temperature in degC

/////////////
// Battery //
/////////////
// #define BATTERY_LIFEPO4
#define	BATTERY_LEADACID

#define	MAX_CURRENT	8	// 8 amps max (~110W @ 13.8V)

#if	defined(BATTERY_LEADACID)
#define	MIN_VOLTAGE	12.2
#endif

#if	defined(BATTERY_LIFEPO4)
#define	MIN_VOLTAGE	13.1
#endif

/////////////
// Thermal //
/////////////
#undef	HAVE_FAN		// we don't have a fan
#define	FAN_SPEED_IDLE	300	// when not transmitting but above ambient
#define	FAN_SPEED_TX	800	// speed when transmitting
#define	FAN_SPEED_MAX	800	// maximum supported speed (RPM)

// !defined(_config_h)
#endif

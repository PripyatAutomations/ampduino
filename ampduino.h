// ampduino.h: API for Ampduino
//
// This file should be included in your project to
// talk to ampduino and you need to copy/symlink protocol.cc
// into your project.
#if	!defined(_ampduino_h)
#define	_ampduino_h
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#if	defined(AMPDUINO)
#include "config.h"
#else
#include <ampduino/config.h>
#endif

#include <time.h>

/////////////////////////////////////////////
// Defines the version of protocol we speak.
// No backwards or forwards compatibility will be provided.
/////////////////////////////////////////////
#define	AMPDUINO_PROTOCOL	0x0001

//////////////////
// Device Types //
//////////////////
#define	DEVTYPE_ANY		0x00	// (*)
#define	DEVTYPE_RADIO		0x01	// (RAD)
#define	DEVTYPE_AMPLIFIER	0x02	// (AMP)
#define	DEVTYPE_TUNER		0x04	// (TNR)
#define	DEVTYPE_SWITCH		0x08	// (SW)
#define	DEVTYPE_TRANSVERTER	0x10	// (TV)
#define	DEVTYPE_FILTER		0x20	// (FLT)
#define	DEVTYPE_ROTOR		0x40	// (ROT)

//////////////
// Commands //
//////////////
enum ad_cmd_type {
    CMD_NONE = 0,		// No side effects
    CMD_STATUS = 1,		// No side effects, status message
    CMD_ACTION,		// Action request, side effects
    CMD_MODAL		// System management, with side effects
};

struct ad_noun {
    char	noun[8];
    uint8_t 	token;
};
typedef struct ad_noun AmpduinoNoun;

struct ad_command {
    char verb[8];		// Verb (4 bytes)
    enum ad_cmd_type cmd_type;	// Command type (side effects?)
    int (*hook)(const char *);	// Function hook
    uint8_t valid_verbs;	// Valid verbs
};
typedef struct ad_command AmpduinoCommand;

//////////////////////////
// Radio Specifications //
//////////////////////////
struct ad_radio {
    // Type of radio
    enum {
        RADIO_NONE = 0,
        RADIO_RECEIVER = 1,
        RADIO_TRANSMITTER,
        RADIO_TRANSCEIVER
    } type;
};
typedef struct ad_radio AmpduinoRadio;

/////////////
// Packets //
/////////////
struct ad_packet{
    uint8_t	src;
    uint8_t	dest;
    uint16_t	seqno;
    uint16_t	flags;		// Flags for the packet
    uint8_t	cmd_noun;	// What device function (amp/filter/etc)?
    uint8_t	cmd_verb;	// Selected command
    uint32_t	value_1,	// allow passing 8 values
                value_2,
                value_3,
                value_4,
                value_5,
                value_6,
                value_7,
                value_8;
    uint8_t	checksum;	// checksum of the packet
};
typedef struct ad_packet AmpduinoPacket;

///////////////////
// Configuration //
///////////////////
struct ad_config {
    // Amplifier Configuration
    //////////////////////////
    float	tx_power;	// Desired transmit power
    float	rx_gain;	// Desired LNA gain level
    float	max_swr;	// Maximum allowed swr
    float	max_power;	// Maximum allowed power output
    float	monitor_atten;	// Monitor attenuation
    float	fan_speed;	// Fan speed (RPM)
    int		antenna;	// Selected antenna ID
    int		band;		// Band selection (for tranverters/LPFs)

    // Thermal Management
    /////////////////////
    float	max_finals_temp;
    float	max_system_temp;

    // Power Management
    ///////////////////
    float	max_current;
    float	min_voltage;

    // Current status
    /////////////////
    struct {
        bool	transmitting;	// Are we transmitting?
        float	tx_power;	// Measured Transmit Power
        float	swr;		// SWR

        // Thermals
        ///////////
        float	temp_finals;	// transistor temperature
        float	temp_system;	// temperature inside box

        // Power Management
        ///////////////////
        float	voltage_idle,
                voltage_last_tx;
        float	current_idle,
                current_last_tx;
    } status;
};
typedef struct ad_config	AmpduinoConfig;

enum ShutdownReason {
    SHUTDOWN_UNKNOWN = 0,
    SHUTDOWN_LOWVOLTS,
    SHUTDOWN_OVERCURRENT,	// Overcurrent protection
    SHUTDOWN_THERMAL,		// Subsystem overheated
    SHUTDOWN_QUOTA		// nyi: max watts/day quota
};

#if	defined(AMPDUINO)
// core.cc: Main configuration + status registers
extern AmpduinoConfig cfg;
extern time_t now;

///////////////////////
// Functions for API //
///////////////////////
extern int ampduino_parse(const char *buf);
extern void Log(const char *msg);
extern void Alert(const char *msg);
extern int ampduino_send_msg(const unsigned int src, const unsigned int dest, const char *msg);
extern void reboot(void);

///////////////
// Utilities //
///////////////
#include "frequency.h"
#include "thermal.h"

/////////////////
// Sub-modules //
/////////////////
#include "serial.h"
#include "amplifier.h"
#include "filters.h"
#include "eeprom.h"
#include "transmitter.h"
#include "switch.h"
#include "rotator.h"
#include "transverter.h"
#include "tuner.h"
#include "safety.h"
#include "display.h"
#include "lora.h"
#include "receiver.h"
#include "antenna.h"
#include "battery.h"
#endif

// defined(AMPDUINO)
// !defined(_ampduino_h)
#endif

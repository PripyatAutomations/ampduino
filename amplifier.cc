/*
 * Control of amplifiers
 *
 * Any amplifier which can have an optocoupler interfaced
 * PTT can be used. The developer uses $20 MiniPA kit...
 *
 * Here we interface heavily with the safety.cc code to ensure
 * the amplifier is protected from various bad conditions:
 *	* High SWR
 *	* Battery Voltage Low
 *	* Transmit Overcurrent
 *	* Idle Overcurrent
 *	* Improper LPF selection
 *	* Killswitch
 *
 * Keep code fast as it's called from main loop often
 */
#include "ampduino.h"

#if	defined(CF_AMPLIFIERS)
// Turn on PTT on amplifier
bool ad_Amplifier::SetPTT(bool state) {
    return false;
}

// Get temperature of finals on device
float ad_Amplifier::GetFinalsTemp(void) {
    // Sample the ADC pin
    // Scale the value
    return (cfg.status.temp_finals);
}

// Get enclosure temperature of device
float ad_Amplifier::GetSystemTemp(void) {
    // Sample the ADC pin
    // Scale the value
    return (cfg.status.temp_system);
}

// defined(CF_AMPLIFIERS)
#endif

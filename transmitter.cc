//
// Support for transmitter controls
//
// This code will run on transmitter type devices
#include "ampduino.h"

#if	defined(CF_TRANSMITTER)
bool ad_Transmitter::Enabled(void) {
    return this->enabled;
}

bool ad_Transmitter::Enable(void) {
    this->enabled = true;
    return true;
}

bool ad_Transmitter::Disable(void) {
    this->enabled = false;
    return true;
}

// Set the frequency of a VFO on this transmitter
bool ad_Transmitter::Tune(int vfo, float frequency) {
    return true;
}
// defined(CF_TRANSMITTER)
#endif

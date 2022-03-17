//
// filters
//
// Here we support selectable Low/Band/High pass filters for RX and TX RF paths.
//
// 74hc595 shift registers are used to minimize GPIO pins used on the host.
//
// Our filter kit works via +12V switched power to relay coil to select the
// correct input and output paths for the desired filter.
//
// All efforts have been made to keep this as generic as possible for the sake
// of future experimenters! ;)
#include "ampduino.h"

#if	defined(CF_FILTERS)
bool ad_Filter::Enable(void) {
    this->enabled = true;
    return true;
}

bool ad_Filter::Bypass(void) {
    this->enabled = false;
    return true;
}

float ad_Filter::GetPassbandStart(void) {
    return this->passband_start;
}

float ad_Filter::GetPassbandEnd(void) {
    return this->passband_end;
}

bool ad_Filter::Setup(enum ad_FilterType type, float start, float end, int pin, int bit) {
//    ad_Filter *lp = new Filter;
    // This should be a new, uninitialized object, if i understand this correctly...
    this->passband_start = start;
    this->passband_end = end;
    this->if_pin = pin;
    this->if_bit = bit;

    return true;
}

// defined(CF_FILTERS)
#endif

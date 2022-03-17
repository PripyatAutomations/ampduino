//
// Support for text based console on OLED or LCD displays
//
// This code will probably not happen for a long time as I
// use my amplifier remotely....
#include "ampduino.h"

#if	defined(CF_DISPLAY)
// Display an important alert without blocking
void print_alert(const char *msg) {
     // NYI
}

void print_log(const char *msg) {
    // NYI
}

bool ad_Display::Enable(void) {
    this->enabled = true;
    return true;
}

bool ad_Display::Disable(void) {
    this->enabled = false;
    return true;
}

// defined(CF_DISPLAY)
#endif

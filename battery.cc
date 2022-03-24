/*
 * Support for battery power management
 *
 * Here we handle keeping track of battery statistics
 * and shutting down the system
 */
#include "ampduino.h"

bool Battery::Shutdown(enum ShutdownReason reason) {
    // From safety.cc
    
    return true;
}

bool Battery::SelfTest(void) {
    return true;
}

// During me main loop, we are called to update
// battery statistics (volts, 
bool Battery::UpdateStatistics(void) {
    // A full second has past, update user display info
    if (now > this->State.last_update) {
       //
    }

    // Set our last updated time
    this->State.last_update = now;

    // XXX: Update things that need to happen every loop
    
    return true;
}

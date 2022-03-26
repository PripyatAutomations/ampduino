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

float Battery::GetVoltage(void) {
    return 0;
}

float Battery::GetCurrent(void) {
    return 0;
}

// During me main loop, we are called to update
// battery statistics (volts, current, etc).
// Once per second...
bool Battery::UpdateStatistics(void) {
    // A full second hasn't past, skip this cycle
    if (now <= this->State.last_update) {
       return false;
    }


    // Update things that need to happen every loop
    float tmp;

    // Battery Voltage
    /////////////////////////
    tmp = this->GetVoltage();

    // is this a historic high?
    if (this->State.max_volts < tmp)
       this->State.max_volts = tmp;
    // is this a historic low?
    if (this->State.min_volts > tmp)
       this->State.min_volts = tmp;
    // current voltage
    this->State.curr_volts = tmp;

    // Battery Current
    //////////////////
    tmp = this->GetCurrent();
    // is this historic high?
    if (this->State.max_current < tmp)
       this->State.max_current = tmp;

    // XXX: This needs to be averaged over non-TX time...
    if (this->State.idle_current < tmp)
       this->State.idle_current = tmp;

    // set current current
    this->State.curr_current = tmp;

    // Calculate our current power usage
    float watts = this->State.curr_volts * this->State.curr_current;

    // Add this second's usage...
    this->State.watts_used += watts;    

    // Set our last updated time
    this->State.last_update = now;
    return true;
}

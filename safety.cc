/*
 * Safety mechanisms to protect the amplifier and it's
 * sections.
 */
#include "ampduino.h"

// are things in a state where we can safely transmit?
bool Safety::CanTransmit(void) {
    // Something has asserted that TX is not safe right now...
    if (this->tx_ok == false)
       return false;

    this->PendingTransmission = true;

    return true;
}

// is there a pending transmit request?
bool Safety::PendingTransmit(void) {
    return this->PendingTransmission;
}

// SWR protection
bool Safety::SWR_Lockout(void) {
   if (cfg->status.swr < cfg->max_swr)
      return false;

   return true;
}

////////////////////////
// Thermal Management //
////////////////////////
// CheckThermals: Returns true if temperatures OK
bool Safety::CheckThermals(void) {
     if (cfg->status.temp_finals >= cfg->max_finals_temp)
        return false;

     if (cfg->status.temp_system >= cfg->max_system_temp)
        return false;

     return true;
}

//////////////////////
// Power management //
//////////////////////
// Are voltages above threshold
bool Safety::CheckVoltages(void) {
     if (cfg->status.voltage_idle < cfg->min_voltage) {
        Alert("LOW VOLT");
        // halt_tx(HALT_LOWVOLTS);
        // schedule_shutdown(HALT_LOWVOLTS);
        return false;
     }

     if (cfg->status.voltage_last_tx < cfg->min_voltage) {
        Alert("LOW VOLT LAST_TX");
        // halt_tx(HALT_LOWVOLTS);
        // schedule_shutdown(HALT_LOWVOLTS);
        return false;
     }

     return true;
}

// Are exceeding maximum current allowed RIGHT NOW?
bool Safety::CheckCurrents(void) {
     if (cfg->status.current_idle < cfg->max_current) {
        Alert("OVERCURRENT");
        // halt_tx(HALT_OVERCURRENT);
        return false;
     }
     return true;
}

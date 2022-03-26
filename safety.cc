/*
 * Safety mechanisms to protect the amplifier and it's
 * sections.
 */
#include "ampduino.h"

// Is transmitting OK?
bool tx_ok = false;

// Are we transmitting?
bool Transmitting = false;

// Do we have a pending transmission?
bool PendingTransmission = false;

// are things in a state where we can safely transmit?
bool CanTransmit(void) {
    // Something has asserted that TX is not safe right now...
    if (tx_ok == false)
       return false;

    PendingTransmission = true;

    return true;
}

// is there a pending transmit request?
bool PendingTransmit(void) {
    return PendingTransmission;
}

// SWR protection
bool SWR_Lockout(void) {
   if (cfg->status.swr < cfg->max_swr)
      return false;

   return true;
}

////////////////////////
// Thermal Management //
////////////////////////
// CheckThermals: Returns true if temperatures OK
bool CheckThermals(void) {
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
bool CheckVoltages(void) {
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
bool CheckCurrents(void) {
     if (cfg->status.current_idle < cfg->max_current) {
        Alert("OVERCURRENT");
        // halt_tx(HALT_OVERCURRENT);
        return false;
     }
     return true;
}

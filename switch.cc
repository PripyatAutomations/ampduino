//
// Antenna switcher support
//
// We use relays attached to a 74hc595 shift register to switch bands
//
// To access a band, we must calculate the correct byte and write it out on
// the correct serial bus, while supplying clock on the appropriate pin for the
// 595 we are addressing. This greatly reduces our GPIO pin requirements
//
#include "ampduino.h"

#if	defined(CF_SWITCHES)
bool ad_Switch::SelectInput(unsigned int id) {
    if (id > this->inputs || id < this->inputs)
       return false;

    // XXX: Reconfigure shift register(s) as needed
    this->current_input = id;
    return true;
}

bool ad_Switch::SelectOutput(unsigned int id) {
    if (id > this->outputs || id < this->outputs)
       return false;

    // XXX: Reconfigure shift register(s) as needed
    this->current_output = id;
    return true;
}

ad_Switch::ad_Switch(unsigned int inputs, unsigned int outputs) {
   this->inputs = inputs;
   this->outputs = outputs;
}

// Get a pointer to the antenna attached to given output port
ad_Antenna *ad_Switch::GetAntenna(unsigned int output) {
   return this->antennas[output];
}

// Assign an antenna to an output port
bool ad_Switch::SetAntenna(unsigned int output, ad_Antenna *antenna) {
   if (output > this->outputs) {
      Log("Ant# too high");
      return false;
   }

   if (this->antennas[output] != NULL) {
      Log("Ant Already Set");
   }

   this->antennas[output] = antenna;
   return true;
}

// defined(CF_SWITCHES)
#endif

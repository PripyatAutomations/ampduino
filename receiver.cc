//
// Implement control of receive-only radios
//
#include "ampduino.h"

#if	defined(CF_RECEIVERS)

bool ad_Receiver::Enable(void) {
    return (this->enabled = true);
}

bool ad_Receiver::Disable(void) {
    return (this->enabled = false);
}

// Set the frequency of one of the receiver's VFOs
bool ad_Receiver::Tune(unsigned int vfo, float frequency) {
    return true;
}

// Sele
bool ad_Receiver::SelectVFO(unsigned int vfo) {
    if (vfo > this->num_vfo) {
       Alert("No such VFO on this radio");
       return false;
    }
    this->active_vfo = vfo;

    return true;
}

// defined(CF_RECEIVERS)
#endif

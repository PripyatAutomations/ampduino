//
// Implement control of receive-only radios (NYI)
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
bool ad_Receiver::Tune(int vfo, float frequency) {
    return true;
}

// defined(CF_RECEIVERS)
#endif

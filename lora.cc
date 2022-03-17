//
// Eventual support for LoRa communication will be here
//
#include "ampduino.h"

#if	defined(CF_LORA)
bool ad_LoRa::Enabled(void) {
    return this->enabled;
}

// defined(CF_LORA)
#endif

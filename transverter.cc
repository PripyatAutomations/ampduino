//
// Support for transverter boards
//
// Right now, there's little reason for me to develop this bit
//
// Feel free to donate transverter kits (or solid state units)
//
// rustytaco@istabpeople.com
//
#include "ampduino.h"

#if	defined(CF_TRANSVERTERS)

bool ad_Transverter::SetActive(void) {
    this->enabled = true;
    return true;
}

bool ad_Transverter::SetBypass(void) {
    this->enabled = false;
    return true;
}

// defined(CF_TRANSVERTERS)
#endif

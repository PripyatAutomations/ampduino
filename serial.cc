//
// Support for AmpDuino protocol over serial
//
#include "ampduino.h"

#if	defined(CF_SERIAL)
bool ad_Serial::Write(const char *pkt) {
    return true;
}

// defined(CF_SERIAL)
#endif

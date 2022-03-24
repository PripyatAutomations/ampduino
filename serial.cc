//
// Support for AmpDuino protocol over serial
//
#include "ampduino.h"

#if	defined(CF_SERIAL)
bool ad_Serial::Write(const char *pkt) {
    return true;
}

bool ad_Serial::Read(char *buf, int size) {
    return true;
}

// defined(CF_SERIAL)
#endif

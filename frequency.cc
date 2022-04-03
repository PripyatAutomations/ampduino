//
// Frequency/Wavelength Conversion utility functions
//
#include "ampduino.h"

float MHzToWavelength(float val) {
    float wl = 0;
    
    if (val <= 0)
       return 0;

    wl = (CONV_C / val);
    return wl;
}

float WavelengthToMHz(float val) {
    float khz = 0;

    if (val <= 0)
       return 0;

    // return this in mhz
    khz = (CONV_C / val);
    return khz;
}

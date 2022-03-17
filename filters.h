//
// Pass Filter support
//
#include "config.h"

#if	defined(CF_FILTERS)
enum ad_FilterType {
    FILTER_NONE	= 0,
    FILTER_LPF,
    FILTER_BPF,
    FILTER_HPF,
    FILTER_REJECT,
    FILTER_NOTCH
};

class ad_Filter {
    private:
        bool	enabled;	// Enabled or bypass?

        // Physical interface to the LPF
        int	if_pin;		// GPIO pin associated with LPF
        int	if_bit;		// bit within the byte (for shift reg I/Fs)
        // Band
        float	passband_start;	// passband start in khz
        float	passband_end;	// passband end in khz
        float 	transition_width;
        float 	atten_passband;

    public:
        bool Setup(enum ad_FilterType type, float start, float end, int pin, int bit);
        float	GetPassbandStart(void);
        float	GetPassbandEnd(void);
        bool Enable(void);
        bool Bypass(void);
};

///////////////
// LPF Bands //
///////////////
// 24 - 28 mhz
// 18 - 21 mhz
//      14 mhz
//  7 - 10 mhz
//     3.5 mhz
//     1.9 mhz

// defined(CF_FILTERS)
#endif

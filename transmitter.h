//
#if	!defined(_transmitter_h)
#define	_transmitter_h
#include "ampduino.h"

#if	defined(CF_TRANSMITTERS)
enum TX_RADIO_TYPE {
    TX_RADIO_NONE	= 0,			// No radio configured yet
    TX_RADIO_UBITX				// ubitx (v6?) running modified version of N8ME's firmware
};

class ad_Transmitter {
    private:
        bool enabled;
        enum TX_RADIO_TYPE radio_type;

    public:
        bool Enabled(void);
        bool Enable(void);
        bool Disable(void);
        bool Tune(int vfo, float frequency);
};

// defined(CF_TRANSMITTERS)
#endif

// !defined(_transmitter_h)
#endif

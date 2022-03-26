//
#if	!defined(_transmitter_h)
#define	_transmitter_h
#include "ampduino.h"

#if	defined(CF_TRANSMITTERS)
enum TX_RADIO_TYPE {
    TX_RADIO_NONE	= 0,			// No radio configured yet
    TX_RADIO_UBITX				// ubitx (v6?) running modified version of N8ME's firmware
};

enum TX_RADIO_STATE {
    TX_BLOCKED = 0,				// Transmit not allowed
    TX_PENDING,					// Preparing to allow TX
    TX_ALLOWED					// Transmission is allowed
};

class ad_Transmitter {
    private:
        bool enabled;

    public:
        enum TX_RADIO_TYPE radio_type;
        enum TX_RADIO_STATE radio_state;
        bool Enabled(void);
        bool Enable(void);
        bool Disable(void);
        bool Tune(int vfo, float frequency);
};

// defined(CF_TRANSMITTERS)
#endif

// !defined(_transmitter_h)
#endif

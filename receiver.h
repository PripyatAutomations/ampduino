#if	!defined(_receiver_h)
#define	_receiver_h

#if	defined(CF_RECEIVERS)
enum RX_RADIO_TYPE {
    RX_RADIO_NONE = 0,			// None radio selected
    RX_RADIO_UBITX			// uBITX (v6?) running modified version of N8ME's firmware
};

class ad_Receiver {
    private:
        bool enabled;
        enum RX_RADIO_TYPE radio_type;

    public:
        bool Enable(void);
        bool Disable(void);
        bool Tune(int vfo, float frequency);
};

// defined(CF_RECEIVERS)
#endif

// !defined(_receiver_h)
#endif

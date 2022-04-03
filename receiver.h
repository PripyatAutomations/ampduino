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
        unsigned int num_vfo;		// how many VFOs does it have?
        unsigned int active_vfo;	// which VFO is active?

    public:
        bool Enable(void);
        bool Disable(void);
        bool Tune(unsigned int vfo, float frequency);
        bool SelectVFO(unsigned int vfo);
};

// defined(CF_RECEIVERS)
#endif

// !defined(_receiver_h)
#endif

//
// Support for transverters
#if	!defined(_transverter_h)
#define	_transverter_h

#if	defined(CF_TRANSVERTERS)
class ad_Transverter {
    private:
        bool	enabled;		// Enabled or bypassed
        unsigned int radio_band;	// Radio (internal) band in meters
        unsigned int output_band;	// Output band in meters
    public:
        bool SetBypass(void);		// BYPASS (disable) this transverter
        bool SetActive(void);		// ACTIVATE (enable) this transverter
};
// defined(CF_TRANSVERTERS)
#endif

// !defined(_TRANSVERTERS_H)
#endif

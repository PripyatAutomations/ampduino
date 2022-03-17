#if	!defined(_amplifier_h)
#define	_amplifier_h

#if	defined(CF_AMPLIFIERS)
// This class defines a single amplifier unit
class ad_Amplifier {
    private:
        float min_freq;		// Lowest supported frequency
        float max_freq;		// Highest supported frequency
        float max_power_in;
        float max_power_out;
        float target_power;
        float current_power;
        float swr;
        enum {
            AMP_NONE = 0,
            AMP_TRANSMIT = 1,	// Transmit amp
            AMP_RECEIVER		// RX only amp (LNA)
        } type;
    public:
        bool SetPTT(bool state);
        float GetFinalsTemp(void);
        float GetSystemTemp(void);
};

// defined(CF_AMPLIFIERS)
#endif

// !defined(_amplifier_h)
#endif

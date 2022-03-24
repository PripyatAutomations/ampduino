#if	!defined(_battery_h)
#define	_battery_h

#include <time.h>

class Battery {
    private:
        // running battery statistics
        struct {
            float	battery_temp;	// Temperatures
            float	max_volts;	// Maximum voltage observed
            float	curr_volts;	// Current voltage
            float	min_volts;	// Minimum voltage observed
            float	max_current;	// Maximum current observed
            float	curr_current;	// Current current
            float	idle_current;	// Calculated average idle current
            float	watts_used;	// Total watts used since reboot
            time_t	last_update;	// Last time updated
        } State;
    public:
        // Shut down due to various reasons
        bool Shutdown(enum ShutdownReason reason);

        // Self-test
        bool SelfTest(void);

        // Update statistics (called from main loop)
        bool UpdateStatistics(void);
};

#endif	// !defined(_battery_h)

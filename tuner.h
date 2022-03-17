// Basic interface to ATU-100's PIC firmware
//
// You MUST load the modified firmware in atu-100/ onto your device
// before this code will be able to work.
//
// After loading the custom firmware, connect the atu-100 to mega2560 as follows:
//
//	ATU-100			Mega
//	-------			----
//	   RX			 D1
//	   TX			 D2

#if	!defined(_tuner_h)
#define	_tuner_h
#include "antenna.h"

#if	defined(CF_TUNERS)
class ad_AutoTuner {
    private:
        unsigned int AppendMemory(struct ad_TunerMemory *mp);
        struct ad_TunerMemory *memories[MAX_TUNER_MEMORIES];

    public:
        // Switch tuner section to AUTO mode
        bool SetAuto(void);
        // Switch tuner section to MANUAL mode
        bool SetManual(void);
        // Switch tuner section to BYPASS mode
        bool SetBypass(void);
        // manually set the l/c values
        bool SetConfig(float l, float c);
        // trigger auto tuning
        bool Tune(void);
        // Store a new memory entry
        unsigned int SaveMemory(ad_Antenna *antenna, float frequency, float l, float c);
        // Find memory ptr by id
        struct ad_TunerMemory *FindMemoryById(unsigned int id);
        // Load a memory by slot Id
        bool LoadMemoryBySlot(unsigned int id);
        // Load a memory by pointer
        bool LoadMemoryByPtr(struct ad_TunerMemory *mp);
};

//////////////////////////
// Tuner Specifications //
//////////////////////////
struct ad_tuner {
    float min_freq;
    float max_freq;
    float min_tune_power;
    float max_tune_power;
};
typedef struct ad_tuner AmpduinoTuner;

struct ad_TunerMemory {
    ad_Antenna *antenna;	// Which antenna is being used?
    float	l;		// Total added inductance
    float	c;		// Total added capacitance
    float	frequency;	// Frequency (hz)
};

// defined(CF_TUNERS)
#endif

// !defined(_tuner_h)
#endif

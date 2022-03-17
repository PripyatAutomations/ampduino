// Support antenna switching
#if	!defined(_switch_h)
#define	_switch_h

#if	defined(CF_SWITCHES)
#include "antenna.h"

class ad_Switch {
    private:
        unsigned int inputs;		// how many inputs do we have?
        unsigned int outputs;		// how many outputs do we have?
        unsigned int current_input,	// Selected input
            current_output;	// Selected output

        // The output port is the index within this array and must not be > outputs
        ad_Antenna *antennas[MAX_ANTENNAS];	// Link to appropriate antenna

    public:
        ad_Switch(unsigned int inputs, unsigned int outputs);
        bool SelectInput(unsigned int id);
        bool SelectOutput(unsigned int id);

        //
        ad_Antenna *GetAntenna(unsigned int output);
        bool SetAntenna(unsigned int output, ad_Antenna *antenna);
};

///////////////////////////
// Switch Specifications //
///////////////////////////
struct ad_switch {
    uint8_t inputs;
    uint8_t outputs;
};
typedef struct ad_switch AmpduinoSwitch;

// defined(CF_SWITCHES)
#endif

// !defined(_switch_h)
#endif

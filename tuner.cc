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
#include <string.h>
#include "ampduino.h"

#if	defined(CF_TUNERS)
bool ad_AutoTuner::SetAuto(void) {
    // send_serial(ATU_SERIAL, "AUTO");
    return true;
}

bool ad_AutoTuner::SetManual(void) {
    // send_serial(ATU_SERIAL, "MANUAL");
    return true;
}

bool ad_AutoTuner::SetBypass(void) {
    // send_serial(ATU_SERIAL, "BYPASS");
    return true;
}

// Load a memory based on desired capacitance and inductance
bool ad_AutoTuner::SetConfig(float l, float c) {
    char bcast_msg[24];

    memset(&bcast_msg, 0, 24);
    snprintf(bcast_msg, 24, "SET %.2f %.2f", c, l);
    // send_serial(ATU_SERIAL, bcast_msg);
    return true;
}

// Request TUNE (when in manual or auto) mode
bool ad_AutoTuner::Tune(void) {
    // send_serial(ATU_SERIAL, "TUNE");
    return true;
}

//////////////
// Memories //
//////////////
// Turn a handful of options into a saved memory and return the slot ID
unsigned int ad_AutoTuner::SaveMemory(ad_Antenna *antenna, float frequency, float l, float c) {
     struct ad_TunerMemory *mp;
     unsigned int id;
     mp = (struct ad_TunerMemory *)malloc(sizeof(struct ad_TunerMemory));
     memset(mp, 0, sizeof(struct ad_TunerMemory));

     mp->antenna = antenna;
     mp->frequency = frequency;
     mp->l = l;
     mp->c = c;
     id = this->AppendMemory(mp);

     return id;
}

// Private function to actually append the new memory
unsigned int ad_AutoTuner::AppendMemory(struct ad_TunerMemory *mp) {
     unsigned int id = 255;

     // XXX: Find last entry in memories array and store mp there
     for (unsigned int i = 0; i < MAX_TUNER_MEMORIES; i++) {
        // Is the entry empty?
        if (this->memories[i] == NULL) {
           this->memories[i] = mp;
           return i;
        }
     }
     // If we end up here, we're out of slots.
     Log("ERROR in AppendMemory: FULL");
     return id;
}

// Find the pointer to a memory slot
struct ad_TunerMemory *ad_AutoTuner::FindMemoryById(unsigned int id) {
     struct ad_TunerMemory *mp = NULL;

     if (id > MAX_TUNER_MEMORIES) {
        Alert("Cant that tuner memory");
        return mp;
     }

     if (this->memories[id] != NULL) {
        mp = this->memories[id];
     }
     return mp;
}

// Apply a memory by slot ID
bool ad_AutoTuner::LoadMemoryBySlot(unsigned int id) {
     struct ad_TunerMemory *mp = this->FindMemoryById(id);
     return this->LoadMemoryByPtr(mp);
}

// Apply a memory, by pointer
bool ad_AutoTuner::LoadMemoryByPtr(struct ad_TunerMemory *mp) {
     return this->SetConfig(mp->l, mp->c);
}
// defined(CF_TUNERS)
#endif

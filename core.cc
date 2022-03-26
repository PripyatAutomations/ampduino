#include <SPI.h>
#include "nrf24.h"
#include "ampduino.h"

const char txt_ok[] = "\n+OK\n";

// Uptime in seconds, maintained in loop()
time_t now = 0;

Battery *battery;
Config *cfg;
EEPROMConfig *eeprom;
Safety *safety;

// These bits need to be dynamic from config...
#if	defined(CF_AMPLIFIERS)
ad_Amplifier *amps[MAX_AMPLIFIERS];
#endif
ad_Antenna *ants[MAX_ANTENNAS];
#if	defined(CF_DISPLAY)
ad_Display *display;
#endif
ad_Filter *filters[MAX_FILTERS];
#if	defined(CF_LORA)
ad_LoRa *lora;
#endif
#if	defined(CF_RECEIVERS)
ad_Receiver *receivers[MAX_RECEIVERS];
#endif
#if	defined(CF_TRANSMITTERS)
ad_Transmitter *transmitters[MAX_TRANSMITTERS];
#endif
#if	defined(CF_ROTORS)
ad_Rotator *rotors[MAX_ROTORS];
#endif
#if	defined(CF_SWITCHES)
ad_Switch *switches[MAX_SWITCHES];
#endif
#if	defined(CF_TUNERS)
ad_AutoTuner *tuners[MAX_TUNERS];
#endif

// IMMEDIATELY stop all transmissions
void halt_tx(void) {
    // XXX:
}

void setup() {
    eeprom = new EEPROMConfig();
    cfg = new Config();

    // Loading configuration from EEPROM failed, restore factory default
    if (cfg->LoadFromEEPROM() == false) {
       eeprom->FactoryDefaults();
    }

#if	defined(CF_DISPLAY)
    // Setup LCD, if present
    display = new ad_Display();
#endif

    // Serial configuration SHOULD be in eeprom...
    Serial.begin(9600);
#if	defined(CF_LORA)
    lora = new ad_LoRa;
#endif
#if	defined(CF_NRF24)
    nrf24_radio_init();
#endif

    // Bring up battery and power management systems
    battery = new Battery();
    safety = new Safety();

#if	defined(CF_AMPLIFIERS)
    // Initialize amplifiers
    int nr_amps = MAX_AMPLIFIERS;
    for (int i = 0; i < (nr_amps - 1); i++) {
       amps[i] = new ad_Amplifier();
    }
#endif

    // Initialize antennas
    int nr_ants = MAX_ANTENNAS;
    for (int i = 0; i < (nr_ants - 1); i++) {
       ants[i] = new ad_Antenna();
    }

#if	defined(CF_FILTERS)
    // Initialize filters
    int nr_filters = MAX_FILTERS;
    for (int i = 0; i < (nr_filters - 1); i++) {
       filters[i] = new ad_Filter();
    }
#endif

#if	defined(CF_RECEIVERS)
    // Initialize receivers
    int nr_receivers = MAX_RECEIVERS;
    for (int i = 0; i < (nr_receivers - 1); i++) {
       receivers[i] = new ad_Receiver();
    }
#endif

#if	defined(CF_TRANSMITTERS)
    // Initialize transmitters
    int nr_transmitters = MAX_TRANSMITTERS;
    for (int i = 0; i < (nr_transmitters - 1); i++) {
       transmitters[i] = new ad_Transmitter();
    }
#endif

#if	defined(CF_ROTORS)
    // Initialize rotors
    int nr_rotors = MAX_ROTORS;
    for (int i = 0; i < (nr_rotors - 1); i++) {
       rotors[i] = new ad_Rotator();
    }
#endif

#if	defined(CF_SWITCHES)
    // Initialize rotors
    int nr_switches = MAX_SWITCHES;
    for (int i = 0; i < (nr_switches - 1); i++) {
       switches[i] = new ad_Switch(1, 2);
    }
#endif

#if	defined(CF_TUNERS)
    // Initialize rotors
    int nr_tuners = MAX_TUNERS;
    for (int i = 0; i < (nr_tuners - 1); i++) {
       tuners[i] = new ad_AutoTuner();
    }
#endif
}

// Main loop
void loop() {
#if	defined(CF_NRF24)
    radio.startListening();
#endif

    // XXX: update clock tick?
    // if (second))
    now++;

    // Update battery stats
    battery->UpdateStatistics();

    // Power Management
    if (!CheckVoltages()) {
       halt_tx();
    }

    if (!CheckCurrents()) {
       halt_tx();
    }

#if	defined(CF_NRF24)
    if (radio.available()) {
       while(radio.available()) {
          char rd_buf[120];
          memset(rd_buf, 0, sizeof(rd_buf));
          radio.read(&rd_buf, sizeof(rd_buf));

          // Do stuff
          ampduino_parse(rd_buf);
       }
       delay(5);
       radio.stopListening();
       radio.write(&txt_ok, sizeof(txt_ok));
    } 
#endif
}

// Display a normal priority log message (or send it 
void Log(const char *msg) {
    // Print to display if present
#if	defined(CF_DISPLAY)
    print_log(msg);
#endif
}

void Alert(const char *msg) {
    // Let us hope it will not explode...
    char bcast_msg[sizeof(msg)+6];

#if	defined(CF_DISPLAY)
    // Print to display if present
    print_alert(msg);
#endif
    memset(&bcast_msg, 0, sizeof(msg)+6);
    snprintf(bcast_msg, sizeof(msg)+6, "ALERT %s", msg);

    // Send over serial to broadcast
    ampduino_send_msg((const unsigned int)CF_RAN_ADDRESS, (const unsigned int)0, (const char *)bcast_msg);
}

bool PTT_On(void) {
    // Confirm TX is allowed
    if (!tx_ok) {
       halt_tx();
       Alert("PTT blocked, TX_OK != true");
    }

    // Make sure appropriate filter is selected before allowing TX
    // if (selected_lpf(
    return false;
}

// Allow rebooting the arduino
void(*resetFunc)(void) = 0;

void reboot(void) {
     resetFunc();
}

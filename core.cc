#include <SPI.h>
#include "nrf24.h"
#include "ampduino.h"

const char txt_ok[] = "\n+OK\n";

/////////////
// Objects //
/////////////
// XXX: this all needs to be dynamically created from config
#if	defined(CF_LORA)
ad_LoRa *lora = new ad_LoRa;
#endif
#if	defined(CF_TRANSMITTERS)
ad_Transmitter *transmitter = new ad_Transmitter;	// Transmitters
#endif
#if	defined(CF_RECEIVERS)
ad_Receiver *receiver = new ad_Receiver;		// Receivers
#endif
#if	defined(CF_TRANVERTERS)
ad_Transverter *transverter[MAX_TRANSVERTERS];		// Band transverters
#endif
#if	defined(CF_AMPLIFERS)
ad_Amplifier *tx_amp = new ad_Amplifier;		// TX Power Amplifier
ad_Amplifier *rx_amp = new ad_Amplifier;		// RX Low Noise Amplifier
#endif
#if	defined(CF_FILTERS)
ad_Filter *lpf[MAX_LPF_BANDS];				// TX Low Pass Filters
ad_Filter *bpf[MAX_BPF_BANDS];				// RX Band Pass Filters
#endif
#if	defined(CF_TUNERS)
ad_AutoTuner *tuner = new ad_AutoTuner;			// Antenna Tuners
#endif
#if	defined(CF_SWITCHES)
ad_Switch *switches[MAX_SWITCHES];			// Antenna Switchers
#endif
#if	defined(CF_ROTORS)
ad_Rotator *rotator[MAX_ROTORS];			// Rotators for antennaes
#endif
ad_Antenna *antennas[MAX_ANTENNAS];			// Antennas

// IMMEDIATELY stop all transmissions
void halt_tx(void) {
    // XXX:
}

void setup() {
    // Load configuration blob from eeprom
    config_load();

    // Serial configuration SHOULD be in eeprom...
    Serial.begin(9600);
#if	defined(CF_NRF24)
    nrf24_radio_init();
#endif
#if	defined(CF_SWITCHES)
    //////
    // XXX: All this needs to be in eeprom...
    //////
    switches[0] = new ad_Switch(SWITCH_INPUTS, SWITCH_OUTPUTS);
#endif

    /////////////////
    // Transmitter //
    /////////////////
#if	defined(CF_FILTERS)
    // Create LPF objects
    for (int i = 0; i < MAX_LPF_BANDS; i++)
        lpf[i] = new ad_Filter;

    // XXX: This needs to be moved to configuration
    lpf[0]->Setup(FILTER_LPF, 1900.0, 2000.0, 1, 0);
    lpf[1]->Setup(FILTER_LPF, 3500.0, 4000.0, 1, 1);
    lpf[2]->Setup(FILTER_LPF, 7000.0, 11000.0, 1, 2);
    lpf[3]->Setup(FILTER_LPF, 14000.0, 15000.0, 1, 3);
    lpf[4]->Setup(FILTER_LPF, 18000.0, 21500.0, 1, 4);
    lpf[5]->Setup(FILTER_LPF, 23000.0, 28500.0, 1, 5);
#endif
}

// Main loop
void loop() {
#if	defined(CF_NRF24)
    radio.startListening();
#endif

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

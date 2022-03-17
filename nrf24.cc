#include "config.h"
#if	defined(CF_NRF24)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "ampduino.h"
#include "nrf24.h"

RF24 radio(7, 8);	// CE, CSN

const byte addresses[][6] = { "00001", "00001" };

void nrf24_radio_init(void) {
    radio.begin();
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();
}

// defined(CF_NRF24)
#endif

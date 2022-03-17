#include "config.h"

#if	defined(CF_NRF24)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
extern const byte addresses[][6];
extern RF24 radio;

extern void nrf24_radio_init(void);

// defined(CF_NRF24)
#endif

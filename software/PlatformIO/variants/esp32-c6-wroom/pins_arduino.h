#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include "soc/soc_caps.h"
#include <stdint.h>

// UART
static const uint8_t TX = 25;
static const uint8_t RX = 24;

// I2C
static const uint8_t SDA = 20;
static const uint8_t SCL = 21;

// SPI
static const uint8_t SCK      = 6;   
static const uint8_t MOSI     = 7;   
static const uint8_t MISO     = 27;  
static const uint8_t SS       = 19;  
static const uint8_t FLASH_CS = 19;

// USB
static const uint8_t USB_D_MINUS = 13; 
static const uint8_t USB_D_PLUS  = 14;

// DIGITAL
static const uint8_t S0 = 9;
static const uint8_t S1 = 10;
static const uint8_t S2 = 12;
static const uint8_t O1 = 11;
static const uint8_t O2 = 23;
static const uint8_t O3 = 18;
static const uint8_t O4 = 17;
static const uint8_t O5 = 16; 
static const uint8_t O6 = 15;

// GPIO
static const uint8_t GPIO0  = 0;
static const uint8_t GPIO1  = 1;
static const uint8_t GPIO2  = 2;
static const uint8_t GPIO3  = 3;
static const uint8_t GPIO4  = 4;
static const uint8_t GPIO5  = 5;
static const uint8_t GPIO6  = 6;
static const uint8_t GPIO7  = 7;
static const uint8_t GPIO8  = 8;
static const uint8_t GPIO9  = 9;
static const uint8_t GPIO10 = 10;
static const uint8_t GPIO11 = 11;
static const uint8_t GPIO12 = 12;
static const uint8_t GPIO13 = 13;
static const uint8_t GPIO14 = 14;
static const uint8_t GPIO15 = 15;
static const uint8_t GPIO16 = 16;
static const uint8_t GPIO17 = 17;
static const uint8_t GPIO18 = 18;
static const uint8_t GPIO19 = 19;
static const uint8_t GPIO20 = 20;
static const uint8_t GPIO21 = 21;
static const uint8_t GPIO22 = 22;
static const uint8_t GPIO23 = 23;

#endif /* Pins_Arduino_h */
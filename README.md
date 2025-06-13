# Omnia – Open Source PLC Board

## Overview

Omnia is an **open-source** and **open-hardware** Programmable Logic Controller (PLC). It is built around the **ESP32-C6 WROOM** module, combining wireless capabilities with robust processing and a rich set of I/O features. It is designed to be easily programmable and extendable, making it suitable for:

- Industrial automation projects  
- Smart home and IoT applications  
- Educational and research platforms  
- Rapid prototyping of control systems  

---

## Technical Specifications

| Feature                          | Description                                     |
|----------------------------------|-------------------------------------------------|
| **Microcontroller**              | ESP32-C6 WROOM (RISC-V core, Wi-Fi, BLE)        |
| **Digital Inputs**               | 3 channels, EMI and ESD protected               |
| **Analog Inputs**                | 3 channels, EMI and ESD protected               |
| **Digital Outputs**              | 6 channels, EMI and ESD protected               |
| **Relay Outputs**                | 3 24VDC high-side controlled relays             |
| **USB Interface**                | USB-C connector communication                   |
| **External Flash Memory**        | 64MB NOR Flash (W25Q512JV)                      |
| **Real-Time Clock**              | Integrated RTC (DS3231SN) with battery support  |
| **Communication Interface**      | RS-485 + expansion port                         |
| **Wireless Antenna**             | External IPEX antenna connector                 |
| **LED Indicators**               | Status LEDs for each input and output channel   |
| **Power Supply**                 | 24V to 3.3V regulator onboard                   |

---

## Pinout

| **Pin**   | **Function / Description** |
|-----------|----------------------------|
| GND       | Ground                     |
| 3V3       | Power Supply (3.3V)        |
| EN        | Reset (Enable)             |
| IO0       | BOOT Button                |
| IO1       | S0 (Analog MUX Select)     |
| IO2       | MISO (Flash)               |
| IO3       | DE/RE (RS-485 Direction)   |
| IO4       | INT/SQW (RTC Interrupt)    |
| IO5       | Digital Input              |
| IO6       | SCK (Flash Clock)          |
| IO7       | MOSI (Flash)               |
| IO8       | S1 (Analog MUX Select)     |
| IO9       | O6 (Digital Output)        |
| IO10      | O1 (Digital Output)        |
| IO11      | S2 (Analog MUX Select)     |
| IO12      | USB D-                     |
| IO13      | USB D+                     |
| IO15      | O2 (Digital Output)        |
| IO18      | O5 (Digital Output)        |
| IO19      | O4 (Digital Output)        |
| IO20      | O3 (Digital Output)        |
| IO21      | FLASH CS (Chip Select)     |
| IO22      | SDA (I²C)                  |
| IO23      | SCL (I²C)                  |
| RXD0      | RX (Serial Communication)  |
| TXD0      | TX (Serial Communication)  |
| NC        | Not Connected              |

---

## Getting Started

You can program the Omnia board using:

- **Arduino IDE** (ESP32-C6 Dev Module support)
- **OpenPLC Editor** + **Structured Text to Arduino Converter** (in accordance with IEC 61131-3)
- **PlatformIO** (esp32-c6-wroom support - https://github.com/BiaPopa/platform-espressif32.git)

The USB-C port provides a programming interface. For expansion or RS-485 communication, use the dedicated expansion port.

---


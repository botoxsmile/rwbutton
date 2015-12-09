// By botoxsmile 11/29/2015

#ifndef ibutton_h
#define ibutton_h

#include <Arduino.h>
#include <OneWire.h>

// --- Constants ----------------------
#define DS1990_FAMILY_CODE  0x01
#define DS2405_FAMILY_CODE  0x05
#define DS1822_FAMILY_CODE  0x22
#define DS2430_FAMILY_CODE  0x14
#define DS2431_FAMILY_CODE  0x2d
#define DS18S20_FAMILY_CODE 0x10
#define DS2433_FAMILY_CODE  0x23
#define RW1990_FAMILY_CODE  0xff

#define READ_ROM   0x33
#define SEARCH_ROM 0xF0
#define MATCH_ROM  0x55
#define SKIP_ROM   0xCC
#define WRITE_ROM  0xD5

// --- Typedef ----------------------
typedef struct {
  byte family;
  byte BSN[6];
  byte CRC;
} serialNumber ;

// --- Headers -----------------------
void printSerial(serialNumber id);
void poll_insert(OneWire button, serialNumber *id);
void poll_remove(OneWire button);
boolean check_button(OneWire button, serialNumber id, byte family_code);
void readROM(OneWire button, serialNumber *id);
void writeROM_1(OneWire button, serialNumber *id);
void writeROM_2(OneWire button, serialNumber *id);

#endif

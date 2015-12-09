// By botoxsmile 11/29/2015
#include "iButton.h"
#include <OneWire.h>

#define PIN 2
#define INT0 0
// --- Global variables ----------------------
// iBUTTON connected to PIN
OneWire iBUTTON (PIN); 
volatile boolean is_inserted = false;

// --- Setup -------------------------
void setup(){
 Serial.begin(9600); 
 attachInterrupt(INT0, get_status, LOW);
}

// --- Utils ------------------------
void get_status() {
  Serial.print("*");
}

// --- Loop -------------------------
void loop(){
  serialNumber iBSN; 
  serialNumber RWSN; 
  serialNumber checkSN;

  // --- Polling for token insertion  
  poll_insert(iBUTTON, &iBSN);
  Serial.print("\n--- Insert original -----\n");
  printSerial(iBSN);

  // --- Check token model (must be DS1990)
  if (!check_button(iBUTTON, iBSN, DS1990_FAMILY_CODE))
    return;

  // --- Polling for token removal
  poll_remove(iBUTTON);
  Serial.print("\n--- Remove original -----\n");
  
  // --- Polling for new token insertion
  poll_insert(iBUTTON, &RWSN);
  Serial.print("\n--- Insert clone ------\n");
  printSerial(RWSN);
  
  // --- Check new token model (must be RW1990)
  if (!check_button(iBUTTON, iBSN, RW1990_FAMILY_CODE))
    return;

  // --- Write SN
  writeROM_1(iBUTTON, &iBSN);
  
  // --- Check SN
  readROM(iBUTTON, &checkSN);
  printSerial(checkSN);
  if (memcmp(&iBSN, &checkSN, 8) == 0)
    Serial.print("\nCloning successful\n");
  else
    Serial.print("\nCloning failed\n");
  
   // --- Over
   poll_remove(iBUTTON);  

}


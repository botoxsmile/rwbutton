// Based on https://gist.github.com/swiftgeek/0ccfb7f87918b56b2259
// By botoxsmile 11/29/2015
#include "ibutton.h"

// --- Debug 
void printSerial(serialNumber id){
  // Print iButton serial number elements
  Serial.print("\nFamily code: ");
  Serial.print(id.family,HEX);

  Serial.print("\nSN: ");
  for (byte i = 1; i<5; i++){  
    Serial.print(id.BSN[i],HEX); 
    Serial.print("-");
  }
  Serial.print(id.BSN[6],HEX);

  Serial.print("\nCRC: ");
  Serial.print(id.CRC,HEX);
  Serial.print("\n");
}

// --- Utils
void poll_insert(OneWire button, serialNumber *id) {
  button.reset();
  button.reset_search();  
  while (!button.search((byte*)id)){
    Serial.print(".");
    button.reset_search();
    delay(200);
  }
  Serial.print("\n");
}

void poll_remove(OneWire button){
  byte id[8];
  
  button.reset();
  button.reset_search();  
  while (button.search(id)){
    button.reset_search();
    delay(200);
  }
}

boolean check_button(OneWire button, serialNumber id, byte family_code){
  if (id.family != family_code){
    Serial.print("\nInvalid family Code\n");
    return false;
  }
  if (id.CRC != button.crc8((byte*)&id, 7)){
    Serial.print("Invalid CRC\n");
    return false;
  }
 
 return true;
}

// --- Commands
void readROM(OneWire button, serialNumber *id){
  // Read iButton full serial number  
  button.skip();
  button.reset();  
  
  button.write(READ_ROM);
  button.read_bytes((byte*)id, 8);
}

void writeROM_1(OneWire button, serialNumber *id){
  // Write iButton full serial number 
  button.skip();
  button.reset();  
  
  button.write(WRITE_ROM);
  button.write_bytes((byte*)id, 8);
}

void writeROM_2(OneWire button, serialNumber *id){
  // Write iButton full serial number 
  button.skip();
  button.reset();  
  
  button.write(WRITE_ROM);
//  for (byte i = 0; i<8; i++)
//    writeByte(id[i]);
}

int writeByte(byte data){
  int data_bit;
  for(data_bit=0; data_bit<8; data_bit++){
    if (data & 1){
      digitalWrite(2, LOW); pinMode(2, OUTPUT);
      delayMicroseconds(60);
      pinMode(2, INPUT); digitalWrite(2, HIGH);
      delay(10);
    } else {
      digitalWrite(2, LOW); pinMode(2, OUTPUT);
      pinMode(2, INPUT); digitalWrite(2, HIGH);
      delay(10);
    }
    data = data >> 1;
  }
  return 0;
}


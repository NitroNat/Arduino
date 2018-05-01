/*
 *Description
 *   This is a test for Knob on BLuno Accessory shield
 */

#include "blunoAccessory.h"
blunoAccessory myAccessory;
void setup() {             
  Serial.begin(115200);   
  myAccessory.begin(); 
  Serial.println("blunoAccessory Knob test!");   
}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println(myAccessory.readKnob()); 
  delay(1000);
}

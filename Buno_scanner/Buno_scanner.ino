/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

 This example code is in the public domain.
 */
bool one = false;
bool two = false;
bool three = false;
bool four = false;
bool five = false;
bool six = false;
bool seven = false;
bool eight = false;
bool nine = false;
bool ten = false;

#define DEBUG 0

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  if (DEBUG == 1) Serial.println(sensorValue);
  
  if (sensorValue >=65 && sensorValue <=70 && one == false) {
    Serial.println("*s1!cd*e");
    one   = true;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=73 && sensorValue <=76 && two == false) {
    Serial.println("*s1!cg*e");
    one   = false;
    two   = true;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=80 && sensorValue <=84 && three == false) {
    Serial.println("*s1!cj*e");
    one   = false;
    two   = false;
    three = true;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;    
  }
  
    if (sensorValue >= 86 && sensorValue <= 88 && four == false) {
    Serial.println("*s1!ck*e");
    one   = false;
    two   = false;
    three = false;
    four  = true;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=92 && sensorValue <= 94 && five == false) {
    Serial.println("*s1!c;*e");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = true;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=97 && sensorValue <=99 && six == false) {
    Serial.println("*s1!c]*e");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = true;
    seven = false;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=101 && sensorValue <=102 && seven == false) {
    Serial.println("*s1!cp*e");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = true;
    eight = false;
    nine  = false;
    ten   = false;
  }
  
    if (sensorValue >=104 && sensorValue <=106 && eight == false) {
    Serial.println("*s1!co*e");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = true;
    nine  = false;
    ten   = false;
  }
 /*   
    if (sensorValue >=300 && sensorValue <=320 && nine == false) {
    Serial.println("*s1!cd");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = true;
    ten   = false;
  }
    
    if (sensorValue >=330 && sensorValue <=350 && ten == false) {
    Serial.println("*s1!cd");
    one   = false;
    two   = false;
    three = false;
    four  = false;
    five  = false;
    six   = false;
    seven = false;
    eight = false;
    nine  = false;
    ten   = true;
  }
   */ 
    
    
  //Serial.println(sensorValue);
  delay(50);        // delay in between reads for stability
}


/*
 ADXL3xx
 
 Reads an Analog Devices ADXL3xx accelerometer and communicates the
 acceleration to the computer.  The pins used are designed to be easily
 compatible with the breakout boards from Sparkfun, available from:
 http://www.sparkfun.com/commerce/categories.php?c=80

 http://www.arduino.cc/en/Tutorial/ADXL3xx

 The circuit:
 analog 0: accelerometer self test
 analog 1: z-axis
 analog 2: y-axis
 analog 3: x-axis
 analog 4: ground
 analog 5: vcc
 
 created 2 Jul 2008
 by David A. Mellis
 modified 30 Aug 2011
 by Tom Igoe 
 
 This example code is in the public domain.

*/

// these constants describe the pins. They won't change:
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup()
{
  // initialize the serial communications:
  Serial.begin(115200);
  
    delay(150);
  
  //CONFIGURE the BLE: for this to work, restart the Arduino IDE! 
  Serial.print("+++");
  delay(500);
  Serial.println("AT+SETTING=DEFPERIPHERAL");
  delay(250);
  Serial.println("AT+ROLE=ROLE_PERIPHERAL");
  delay(150);
  Serial.print("AT+NAME=Bluno_BLE\r\n");
  delay(150);
  Serial.println("AT+BIND=0xD03972A02367"); //Destination MAC to bind to
  delay(250);
  Serial.println("AT+CMODE=UNIQUE");
  delay(500);
  Serial.println("AT+BLUNODEBUG=OFF");
  delay(500);
  Serial.println("AT+USBDEBUG=OFF");
  delay(500);
  Serial.print("AT+EXIT\r\n");
  
}

void loop()
{
  // print the sensor values:
  Serial.print(analogRead(xpin));
  // print a tab between values:
  Serial.print("\n");
/*  Serial.print("\t");
  Serial.print(analogRead(ypin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print(analogRead(zpin));
  Serial.println();*/
  // delay before next reading:
  delay(100);
}

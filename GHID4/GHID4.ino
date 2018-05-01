
//MAC = 0xD03972C11865

/*  1) need to receive and decipher sensor data
 *  2) display sensor information
 *  3) continuously monitor sensor value
 *  4)...trigger keypresses
 */
#include "blunoAccessory.h"
#include "U8glib.h"

//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
blunoAccessory myAccessory;
//OLED constructor, for oled display
U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

  int senVal; //EOG analog output
  boolean set = false;
  String sensorType;
// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200);
  delay(150);
  
  //CONFIGURE the BLE: for this to work, restart the Arduino IDE! 
  Serial.print("+++");
  delay(500);
  Serial.println("AT+SETTING=DEFPERIPHERAL");
  delay(250);
  Serial.println("AT+ROLE=ROLE_CENTRAL");
  delay(150);
  Serial.print("AT+NAME=GHID_BLE\r\n");
  delay(150);
  Serial.println("AT+BIND=0xE0C79D61F333"); //Destination MAC to bind to
  delay(250);
  Serial.println("AT+CMODE=UNIQUE");
  delay(500);
  Serial.println("AT+BLUNODEBUG=OFF");
  delay(500);
  Serial.println("AT+USBDEBUG=OFF");
  delay(500);
  Serial.print("AT+EXIT\r\n");
  //Flush the buffer?
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  
  myAccessory.begin();
  myAccessory.setRGBLed(1,0,0);   //set to Red to indicate setup
  
}

// the loop routine runs over and over again forever:
void loop() {

      while (!set) { //wait for sensor information
         if(Serial.available() > 0)
          {
              sensorType = Serial.readString(); 
              Serial.println(sensorType[0]);
              
              if (sensorType[0] == '*') {
                sensorType.replace("*","");
                sensorType.trim();
                delay(10);
                myAccessory.setRGBLed(0,1,0);
                set = true;
//              } else {
//                myAccessory.setRGBLed(1,0,0);
//                //Serial.flush();//?
              } 
          }
               delay(10);         
                        
      }
      
    static unsigned long oledTimer=millis();        //every 200ms update the oled display
    if (millis() - oledTimer >= 200) {
        oledTimer=millis();
        myOled.firstPage();                         //for more information about the U8glib library, go to https://code.google.com/p/u8glib/
        do{
            draw();
        }
        while(myOled.nextPage());
    } 
    
     //Serial.available() returns the number of bytes in buffer (max 64 bytes)
       if(Serial.available())
        {
          senVal = Serial.parseInt(); //If accepts a DEC number in buffer, copy it otherwise is ZERO
          //TODO : look into this...
           if (senVal != 0) { //If a DEC number was recieved, SenVal will equal 0 if its not an integer in the serial buffer!
             
               if (senVal == 1023) {
                  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
                  myAccessory.setRGBLed(1,1,1);
               } else {
                  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
                  myAccessory.setRGBLed(0,1,0);
               }
           delay(10);  
        }
      }
 
  delay(100);        // delay in between reads for stability
}

void draw (void)
{
    myOled.setFont(u8g_font_unifont);
    //set the print position
     myOled.setPrintPos(40,16);
    myOled.print("GHID_BLE");
    myOled.setPrintPos(0,32);
    myOled.print("Input:");
    myOled.print(senVal);             //show knob(potentiometer) value read from analog pin
    myOled.setPrintPos(0,48);
    myOled.print("Key:");
    switch (senVal) {
      case 1023:
        myOled.print("Up"); //would replace this command
        break;        
      case 0:
        myOled.print("Down");//would replace this command
        break;
      default:
        myOled.print("X");
        break;
    }
   myOled.setPrintPos(0,64);
   myOled.print("Type:");
   myOled.print(sensorType);
}

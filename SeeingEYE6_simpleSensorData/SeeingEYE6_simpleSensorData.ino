/*
 //MAC = 0xE0C79D61F333
*/
#include "blunoAccessory.h"
#include "U8glib.h"

//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
blunoAccessory myAccessory;
//OLED constructor, for oled display
U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

int knob=0;                 //knob(potentiometer) value read from analog pin
String sensorType = "*EOG!";
String sensorUser = "@Nate!"; 
String sensorMode = "$2!";
String sensorKeys = "#Up,Down!";

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second: 
  //Could set it lower 9600? save power and necessary?
  Serial.begin(115200);
  delay(150);
  
  //CONFIGURE the BLE: for this to work, restart the Arduino IDE! 
  Serial.print("+++");
  delay(250);
  Serial.println("AT+FSM=FSM_TRANS_USB_COM_BLE"); //turn off BLE
  delay(250);
  Serial.println("AT+SETTING=DEFCENTRAL"); //for connection
  delay(250);
  Serial.println("AT+ROLE=ROLE_PERIPHERAL"); //for messaging, Can change roles
  delay(250);
  Serial.print("AT+NAME=EOG_BLE\r\n");
  delay(250);
  Serial.println("AT+BIND=0xD03972C11865"); //Destination MAC to bind to
  delay(250);
  Serial.println("AT+CMODE=UNIQUE");
  delay(250);
  Serial.println("AT+BLUNODEBUG=OFF");
  delay(500);
  Serial.println("AT+USBDEBUG=OFF");//stuff recieved by other bluno
  delay(500);
  Serial.print("AT+EXIT\r\n");
  //Flush the buffer?
  delay(1000);
  
  Serial.flush();//clear all the stuff in buffer
  myAccessory.begin();
  myAccessory.setRGBLed(1,0,0);   //set to Red to indicate setup
  //Send SEnsor Data
  //TODO: make it more robust!
  delay (500); 
  Serial.println(sensorType);
  Serial.flush();//thus doesn't work
  delay (500); 
  Serial.println(sensorUser);
  delay (500); 
  Serial.println(sensorMode);
  delay (500); 
  Serial.println(sensorKeys);
  delay(500);
  myAccessory.setRGBLed(0,1,0); //Green means Good to go!
}

// the loop routine runs over and over again forever:
void loop() {
  
      static unsigned long oledTimer=millis();        //every 100ms update the oled display
    if (millis() - oledTimer >= 100) {
        oledTimer=millis();
        myOled.firstPage();                         //for more information about the U8glib library, go to https://code.google.com/p/u8glib/
        do{
            draw();
        }
        while(myOled.nextPage());
    } 
    static unsigned long Timer500ms=millis();       //every 200ms update the knob(potentiometer)
    if (millis() - Timer500ms >= 200) {
        Timer500ms=millis();
        knob=myAccessory.readKnob();
    }
    //padded it with non integers so that easy to identify numbers in buffer
     Serial.println("%");
     Serial.println(knob); //this works by itself! ...close RX serial monitor; MUST use println!
     Serial.println("&");
 //  Serial.write(knob); //this doesn't work by itself!...must be transmitting it as a hex value?
     delay (10); //basically delays everything! Transmission speed
     Serial.flush(); //no idea what this does
}

void draw (void)
{
    myOled.setFont(u8g_font_unifont);
    //set the print position
     myOled.setPrintPos(40,16);
    myOled.print("EOG_BLE");
    myOled.setPrintPos(10,32);
    myOled.print("Knob:");
    myOled.print(knob);             //show knob(potentiometer) value read from analog pin
    myOled.setPrintPos(10,48);
    myOled.print("Command:");
    switch (knob) {
      case 1023:
        myOled.print("Up");
        break;        
      case 0:
        myOled.print("Down");
        break;
      default:
        myOled.print("X");
        break;
    }
}

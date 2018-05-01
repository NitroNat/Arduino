
 //MAC = 0xE0C79D61F333
/*
 TODO: 
 1) Connect to another bluetooth arduino
 2) Send the Analog input to the other
 3) The other should respond to the message
 */
#include "blunoAccessory.h"
#include "U8glib.h"

//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
blunoAccessory myAccessory;
//OLED constructor, for oled display
U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

int knob=0;                 //knob(potentiometer) value read from analog pin

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  delay(150);
  //Analog reference must be defualt 5 V
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
  delay(250);
  
  myAccessory.begin();
  myAccessory.setRGBLed(0,1,0);   //turn off the RGBLED
}

// the loop routine runs over and over again forever:
void loop() {
  
 

 
    static unsigned long oledTimer=millis();        //every 200ms update the oled display
    if (millis() - oledTimer >= 200) {
        oledTimer=millis();
        myOled.firstPage();                         //for more information about the U8glib library, go to https://code.google.com/p/u8glib/
        do{
            draw();
        }
        while(myOled.nextPage());
    } 
    static unsigned long Timer500ms=millis();       //every 500ms update the knob(potentiometer) and the joystick
    if (millis() - Timer500ms >= 500) {
        Timer500ms=millis();
        knob=myAccessory.readKnob();
    }
    
     Serial.println(knob);
 //  Serial.write(sensorValue);
     delay (500); //basically delays everything!
}

void draw (void)
{
    myOled.setFont(u8g_font_unifont);
    //set the print position
    myOled.setPrintPos(10,16);
    myOled.print("Knob:");
    myOled.print(knob);             //show knob(potentiometer) value read from analog pin
}

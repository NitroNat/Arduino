#include "U8glib.h"
#include "blunoAccessory.h"


//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
blunoAccessory myAccessory;

//OLED constructor, for oled display
U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

int knob=0;                 //knob(potentiometer) value read from analog pin

void setup() {
    myAccessory.begin();
    myAccessory.setRGBLed(0,0,1);   //turn off the RGBLED
}


void draw (void)
{
    myOled.setFont(u8g_font_unifont);
    myOled.setPrintPos(10,48);
    myOled.print("Knob:");
    myOled.print(knob);             //show knob(potentiometer) value read from analog pin
}


void loop()
{

    
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
    
}




//MAC = 0xD03972C11865

/*  
 * Continuously 
 */
int index = 0;
int index2 = 0;
int average;
const int window = 9;
int data[window] = {0};
const int sampleSize = 50;
int smoothedData[sampleSize] = {0};
int differenceData[sampleSize] = {0};
int binaryData[sampleSize] = {0};
int count = 0;
int counter[5] = {0}; //tracks number of postive or negative points
//about 5 points in each peak
boolean edge;
int total = 0;
int sensorValue = 0;
enum signal {positive, negative, none};
signal message;

#include "blunoAccessory.h"
#include "U8glib.h"

//blunoAccessory constructor, for setting the relay,buzzer, temperature, humidity, knob, joystick and RGBLED
blunoAccessory myAccessory;
//OLED constructor, for oled display
U8GLIB_SSD1306_128X64 myOled(U8G_I2C_OPT_NONE);

// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200);
  delay(150);
  /*
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
  */
  
  myAccessory.begin();
  myAccessory.setRGBLed(0,1,0);   //set to Red to indicate setup
}

// the loop routine runs over and over again forever:
void loop() {
  //concurrent procedures???
  //log data
   //====================Drawing Shield===============================================================================
    static unsigned long oledTimer = millis();        //every 200ms update the oled display
    if (millis() - oledTimer >= 50) {
        oledTimer=millis();
        myOled.firstPage();                         //for more information about the U8glib library, go to https://code.google.com/p/u8glib/
        do{
            draw();
        }
        while(myOled.nextPage());
    } 
    

  //=====================Wait min 100 ms to sample========================================================================
    static unsigned long Timer100ms = millis();       //every 100ms update the knob(potentiometer) and the joystick ==== 600ms is minimum
    if (millis() - Timer100ms >= 100) { //if elapse time is 500 ms from last line, a minimum gaurenteed
        Timer100ms=millis();
        sensorValue = myAccessory.readKnob();
    }
       
     
     //!!i dont' want to store the old data, i want to store the smoothed data
//=============culmulative simple average===========================================
  // subtract the last reading:
  total = total - data[index];     
  //update with new reading
  data[index] = sensorValue; 
  // add the new reading to the total:
  total = total + data[index];       
 

 //==============================================================================   
  // calculate the average:
  average = total / window;  
  smoothedData[index2] = average;  
 //============================================================================== 
  //calculate difference (change)
  differenceData[index2] = smoothedData[index2] - smoothedData[index2 - 1];
 //===============================================================================
  //Decide
  if (differenceData[index2] > 0) { //positive change (rising edge)
      binaryData[index2] = 1;
  } else if (differenceData[index2] < 0) { //negative change {falling edge}
      binaryData[index2] = -1;
  } else {
      binaryData[index2] = 0; //not really needed already all zeros
  }
 //================================================================================   
  //track the number of positive or negative points
  counter[count] = binaryData[index2];

  
  //Decide
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum+=counter[i];
  }
  //check if there is enought valid points to make decision
  if (sum == 5) 
    message = positive;
  else if (sum == -5)
    message = negative;
  else
    message = none;

 //========================================================================   
  // send it to the computer as ASCII digits
  Serial.print("raw: ");
  Serial.print(sensorValue); 
  Serial.print("    smooth: ");
  Serial.print(average); 
  Serial.print("    change: ");
  Serial.print(differenceData[index2]);
  Serial.print("    change: ");
  Serial.print(binaryData[index2]); 
  Serial.print("    counter: ");
  Serial.print(counter[count]); 
  Serial.print(" ");
 //================Determine the message======================================================== 
  if (message == positive){
     Serial.print("A positive Change");
     
       for (int i = 0; i < 5; i++)
          counter[i] = 0;
       
      delay (1000); //pause for 1 second (pause system)
  } else if (message == negative) {
      Serial.print("A negative Change");
      
        for (int i = 0; i < 5; i++) //Clear the counter of valid points
          counter[i] = 0;
        
      delay (1000); //pause for 1 second (pause system) for stability
  }  else {
  }
  Serial.println("");      
 //=============================================================================================
  // advance to the next position in the array:  
  index++;  
  if (index >= window)               
    index = 0; //reset  
   
    count++;
  if (count >=5) 
    count = 0; 
   
     
  index2++; 
  if (index2 >= sampleSize)               
    index2 = 0; //reset 
   
   
   
  delay(1);
}


void draw (void)
{
    myOled.setFont(u8g_font_tpss);
    myOled.setPrintPos(40,16);
    myOled.print("BLUNO_DSP");
    myOled.setPrintPos(0,32);
    myOled.print("Input:");
    myOled.print(sensorValue);             //show knob(potentiometer) value read from analog pin

}

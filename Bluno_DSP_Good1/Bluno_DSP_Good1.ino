
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
bool pause = false;
int track = 0;

// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {

  //=====================Wait min 100 ms to sample========================================================================
    static unsigned long Timer100ms = millis();       //every 100ms update the knob(potentiometer) and the joystick ==== 600ms is minimum
    if (millis() - Timer100ms >= 100) { //if elapse time is 500 ms from last line, a minimum gaurenteed
        Timer100ms=millis();
        sensorValue = analogRead(A0);
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
  if (pause == false) {
    counter[count] = binaryData[index2];
  } else {
    track++;
    counter[count] = 0;
  }
    
  if (track == 20) {
     pause = false;
     track = 0; 
  }
  
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
  Serial.print("    index: ");
  Serial.print(index2);
  Serial.print("    change: ");
  Serial.print(differenceData[index2]);
  Serial.print("    change: ");
  Serial.print(binaryData[index2]); 
    Serial.print("    cindex: ");
  Serial.print(count); 
  Serial.print("    counter: ");
  Serial.print(counter[count]); 
  Serial.print(" ");
 //================Determine the message======================================================== 
  if (message == positive){
     Serial.print("A positive Change");
       
      pause = true;
      delay (1000); //pause for 1 second (pause system)
      
  } else if (message == negative) {
      Serial.print("A negative Change");
      
      pause = true;
        
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
   
   
   
  delay(100);
}



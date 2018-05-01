
//MAC = 0xD03972C11865

/*  
 * Continuously 
 */
int sensorValue = 0;
const int DATA_SIZE = 10;
int data[DATA_SIZE] = {0};
int index = 0;
int index2= 0;
const int SAMPLE_SIZE = 50;
int differenceData[SAMPLE_SIZE] = {50};
bool pause = false;
int track = 0;
// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() {


  sensorValue = analogRead(A0);

  data[index] = sensorValue;
 //============================================================================== 
  //calculate difference (change)
 if (!pause) {
  if (index == 0)
   differenceData[index2] = data[index] - data[DATA_SIZE];
  else 
   differenceData[index2] = data[index] - data[index - 1];
 } else {
   differenceData[index2] = 0;
   track++;
    if (track == (10)) {
      pause = false;
      track = 0;
    }
 }
 //===============================================================================
  //Decide on the magnitude of difference
  if (differenceData[index2] > 50) { //positive change (rising edge)
      Serial.println ("*s4!cr!cp!co!cl*e");      
      pause = true;
      delay (1000); //pause for 1 second (pause system)
  } else if (differenceData[index2] < -50) { //negative change {falling edge}
      Serial.println("*s1!ce*e");
      pause = true;  
      delay (1000); //pause for 1 second (pause system) for stability 
  } else {
    
  }


 //========================================================================   
  // send it to the computer as ASCII digits
  Serial.print("raw: ");
  Serial.print(sensorValue); 
  Serial.print("    index2: ");
  Serial.print(index2);
  Serial.print("    change: ");
  Serial.print(differenceData[index2]);
  Serial.println("");
 
  index++;  
  if (index >= DATA_SIZE)               
    index = 0; //reset  
     
  index2++; 
  if (index2 >= SAMPLE_SIZE)               
    index2 = 0; //reset 
   
   
   
  delay(100);
}


/*

Must look left/right and return to middle
Holding direction will not work (need to adjust wait time)
 */

 const int windowSize = 5;//must be odd
 int rawData[windowSize] = {0};
 int medianData[50] = {0};
 int index = 0;
 int index2 = 0;
 int diffData[50] = {0};
 int index3 = 0;
 
 int edge = 0;
 int countpos = 10;
 int countneg = 10;
 int positive = 0;
 int negative = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  
  rawData[index] = sensorValue;
  
  medianData[index2] = median(rawData, windowSize);
  //=======================================================================
  if (index2 == 0) 
    diffData[index3] = medianData[index2] - medianData[49];
  else
    diffData[index3] = medianData[index2] - medianData[index2-1];
  //=======================================================================  
   Serial.print("raw: ");
  Serial.print(rawData[index]);
  Serial.print("     median: ");
  Serial.print(medianData[index2]);
  Serial.print("     diff: ");
  Serial.print(diffData[index3]);
 
  //threshold it
  if (diffData[index3] < 20 && diffData[index3] > -20)
        diffData[index3] = 0; 
 
  Serial.print("     threshold: ");
  Serial.print(diffData[index3]);

 
//======================================================================================
if (edge == 0) {//FIRST: detecting a rising or falling edge
    if (diffData[index3] > 0) //rising
        edge = 1; 
    else if (diffData[index3] < 0) // neg
        edge = -1; 
    
//SECOND: (should ignore invalid signals like backtoback pos or negs
} else if (edge == 1) { //has detected a rising edge, now find a following negative 
       if (countpos == 0) { //first check the count
          edge = 0; //search again
          countpos = 10; // reset counter
       } else if (diffData[index3] < 0) {
              positive = 1; //only trigger this when cycle is complete
              edge = 0; //search for new trigger
              countpos = 10;
       }
       countpos = countpos - 1; 
       
} else if (edge == -1) { //has detected a falling edge, now find a following positive
       if (countneg == 0) { //first check the count
          edge = 0;
          countneg = 10;
       } else if (diffData[index3] > 0) {
              negative = 1; //only trigger this when cycle is complete
              edge = 0; //search for new trigger
              countneg = 10;
       //elseif (binaryData(i) < 0)
       }
       countneg = countneg - 1;         
}

    if (positive == 1) {
        Serial.print ("Right");
        Serial.print (" ");
        Serial.println ("*s4!cd!cj!c;g*e");
        positive = 0;
    } else if (negative == 1) {
        Serial.print ("Left");
        Serial.print (" ");
        Serial.println("*s2!cg!c;*e");
        negative = 0;
    }
//======================================================================================    
  Serial.println("");  
  index++;
  index2++;
  index3++;
  
  if (index >= windowSize)               
    index = 0; //reset  
 
  if (index2 >= 50) 
    index2 = 0;
    
  if (index3 >= 50) 
    index3 = 0;
    
  delay(100);        // delay in between reads for stability
}


//finds the median of an array
int median(int data[], int arraySize)
{
   sort(data, arraySize);

   return data[arraySize/2]; //integer division rounds up
}

//Insertion sort: good for small arrays
void sort(int data[], int arraySize) //this is passing by pointer!
{
  //Serial.println(sizeof(data));//not reading it correctly!
    for (int i = 1; i < arraySize; i++) {
      int j = i;
        
        while (j>0 && data[j-1] > data[j]) {
           //swap
          int temp = data[j-1];
          data[j-1] = data[j];
          data[j] = temp;
          
          j--; 
        }
      
    }
}

/*
I think that a small value is sufficient
Since a blink is the source of peak noise = 3 points, 3 points on each side so window = 7
Purpose: get rid of sharp noises and outliers (high freq noise)
 */
//Median
 const int windowSize = 7;//must be odd
 int rawData[windowSize] = {0};
 int index = 0;
 int themedian = 0;
//Mean 
int index2 = 0;
int average;
const int window = 9;
int data[window] = {0};
int total = 0;

int sensorValue = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //for (int i = 0; i < windowSize; i++)
  //  Serial.print(rawData[i]);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  sensorValue = analogRead(A0);
  
  medianFilter(); 
    
  meanFilter();

  delay(100);        // delay in between reads for stability
}

void medianFilter() 
{
  rawData[index] = sensorValue;
  //Serial.println(median(rawData, windowSize)); 
  themedian = median(rawData, windowSize);
  index++;
  if (index >= windowSize)               
    index = 0; //reset 
}
void meanFilter() 
{
  //=============culmulative simple average===========================================
  // subtract the last reading:
  total = total - data[index2];     
  //update with new reading
  data[index2] = themedian; //store the median
  // add the new reading to the total:
  total = total + data[index2];       
   
  // calculate the average:
  average = total / window;  
 //========================================================================   
  // send it to the computer as ASCII digits
  Serial.println(average);
 
  // advance to the next position in the array:  
  index2++;  
  if (index2 >= window)               
    index2 = 0; //reset  
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

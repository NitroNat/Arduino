/*
I think that a small value is sufficient
Since a blink is the source of peak noise = 3 points, 3 points on each side so window = 7
Purpose: get rid of sharp noises and outliers (high freq noise)
 */

 const int windowSize = 7;//must be odd
 int rawData[windowSize] = {0};
 int index = 0;
 

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
  int sensorValue = analogRead(A0);
  
  rawData[index] = sensorValue;
  
  Serial.println(median(rawData, windowSize));
  
  index++;
  
  if (index >= windowSize)               
    index = 0; //reset  

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


//MAC = 0xD03972C11865

/*  
 averaging filter
purpose: smooth out the digital signal
Will be affected by high freq noise
Maybe good going after the median filter

May need to have large window
Perhaps do multiple passes??
 */
int index = 0;
int average;
const int window = 9;
int data[window] = {0};
int total = 0;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second: 
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {

//=============culmulative simple average===========================================
  // subtract the last reading:
  total = total - data[index];     
  //update with new reading
  data[index] = analogRead(A0); 
  // add the new reading to the total:
  total = total + data[index];       
   
  // calculate the average:
  average = total / window;  
 //========================================================================   
  // send it to the computer as ASCII digits
  Serial.println(average);
 
  // advance to the next position in the array:  
  index++;  
  if (index >= window)               
    index = 0; //reset  
   
  delay(100);
}


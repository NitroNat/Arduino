/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
 **ADC max range is 0 to 5V
 **AREF max range is 0 to 5V, AREF can set the upper limit of ADC
 **Must DC shift input to set lower limit to 0V
 http://arduino.cc/en/Reference/AnalogReference?from=Reference.AREF
 
 //MAC = 0xE0C79D61F333

 TODO: 
 1) Connect to another bluetooth arduino
 2) Send the Analog input to the other
 3) The other should respond to the message
 */
int i = 0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 115200 bits per second: 
  //Could set it lower 9600? save power and necessary?
  analogReference(EXTERNAL); //Use the AREF input pin to set the range of ADC (0 to AREF)V range = full 10 bit resolution
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
  delay(250);
}

// the loop routine runs over and over again forever:
void loop() {
  
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.print(sensorValue);
  
  
  //Serial.write("hello");//I'm getting GHID message from the slave!
  //delay(1000);  
  //Serial.print("BYE");
  //delay(1000);
  //Serial.print('A');
  //delay(1000);
  //Serial.print(45,DEC);
  //+delay(1000);
/*  while (i < 100) {
    Serial.write(i); //send decimal 45
    i++;
    delay(500);
  }*/
  /*
  int sensorValue = analogRead(A0);
  //Serial.write("55",4);
    // read the input on analog pin 0:
  
  // print out the value you read:
  Serial.println(sensorValue);
*/ 
    Serial.write(sensorValue);
//  Serial.print(1023);
//  delay(4000);        // delay in between reads for stability
//  Serial.print(45);
  delay(100);
}

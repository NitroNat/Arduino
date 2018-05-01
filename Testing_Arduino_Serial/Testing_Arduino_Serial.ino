int senVal;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    
    //Typing in the Console
    //User input is treated as ASCII, sent as represented Hex
    //The buffer will contain the hex value of the ASCII
    //readString: buffer byte hex --> ASCII text
    //read(): read each hex byte --> DEC byte
    //praseInt(): if hex is ASCII number, then hex byte --> DEC integer
    
    //Mainly used for output to console
    //println(val): outputs DEC interger value
    //println("..."): outputs as ASCII text 
    //ARDUINO always output byte as DEC number NOT HEX number
    
   //Serial.println(Serial.read()); //reads the individual bytes, display each byte as DEC
   // Serial.println(Serial.readString()); //reads the buffer as a ASCII
   //integer value
   senVal = Serial.parseInt(); //If accepts a DEC number in buffer, copy it otherwise is ZERO
   if (senVal != 0) { //If a DEC number was recieved
       Serial.print("GHID recieved: ");
       Serial.println(senVal);
       delay(500);
       senVal = senVal + 10;
       Serial.print("Adding 10: ");
       Serial.println(senVal);
       delay(500);   
   } else {
     Serial.println("Invalid value");
   }
 
  }
}

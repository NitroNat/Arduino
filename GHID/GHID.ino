
//MAC = 0xD03972C11865
  int number;
  int number2 = 10;
  int sum;
  int senVal; //EOG analog output
// the setup routine runs once when you press reset:
void setup() {

  // initialize serial communication at 115200 bits per second: 
  Serial.begin(115200);
  delay(150);
  
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
}

// the loop routine runs over and over again forever:
void loop() {
  /*
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  Serial.println(sensorValue);
  
  *//*
              if (Serial.available() > 0) {
                // read the incoming byte:

                // say what you got:
                Serial.print("I received: ");
                Serial.print(Serial.read());
                Serial.println(" ");
        }*/
    /*    if(Serial.available())
    {
      delay(100);
      //Serial.println() will always display as a ASCII text
      //Serial.println(Serial.readString()); //read the byte as ASCII text
      number = Serial.parseInt();
      sum = number + number2;
      Serial.println(sum);
      delay(100);
      Serial.println(number2);
      //Serial.println(Serial.read());
      Serial.print("\n");
      //Serial.println(Serial.parseInt());
    }
        //if (Serial.read() == "123456789") {
        //  Serial.println("HOOORAY!!!");
        //}*/
        
    //number = Serial.parseInt();
    //sum = number + number2;
    //Serial.println(Serial.readString());
   //Serial.println(number2);
   
       if(Serial.available())
        {
          senVal = Serial.parseInt(); //If accepts a DEC number in buffer, copy it otherwise is ZERO
           if (senVal != 0) { //If a DEC number was recieved
             
               if (senVal == 1023) {
                  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
               } else {
                  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
               }
           Serial.print("GHID recieved: ");
           Serial.println(senVal);
           delay(10);
           senVal = senVal + 10;
           Serial.print("Adding 10: ");
           Serial.println(senVal);
           delay(10);   
         } else {
           Serial.println("Invalid value");
         }
 
 //Serial.println(Serial.read()); 
      }
 
 // delay(500);        // delay in between reads for stability
}

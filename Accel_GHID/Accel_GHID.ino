//int val;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);

  delay(150);
// How to access CLE chip from LEO?
// As of now, must directly connect to the BLE (uno) to set the BLE chip parameters
  //CONFIGURE the LEO 
  /*
  Serial1.print("+++");
  delay(500);
  Serial1.println("AT+SETTING=DEFPERIPHERAL");
  delay(250);
  Serial1.println("AT+ROLE=ROLE_CENTRAL");
  delay(150);
  Serial1.print("AT+NAME=GHID_BLE\r\n");
  delay(150);
  Serial1.println("AT+BIND=0xE0C79D61F333"); //Bluno MAC
  delay(250);
  Serial1.println("AT+CMODE=UNIQUE");
  delay(500);
  Serial1.println("AT+BLUNODEBUG=OFF");
  delay(500);
  Serial1.println("AT+USBDEBUG=OFF");
  delay(500);
  Serial1.print("AT+EXIT\r\n");
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello");
  delay(500);
  
  if (Serial1.available()>0)
  {
    Serial.write (Serial1.read());
    delay (500);
  }
}

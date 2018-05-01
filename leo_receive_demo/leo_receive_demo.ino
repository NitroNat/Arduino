//int val;
void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()>0)
  {
    Serial.write (Serial1.read());
    delay (500);
  }
}

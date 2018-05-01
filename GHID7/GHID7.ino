//Question: How to configure the BLE when connected to Leo?
//how to configure AT mode 0xE0C79D61F333
// MAC address 0xE0C79D61F333

void setup() {
  
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
 
//  delay(1000);
//  Keyboard.println("Hello!");
//  delay (1000);
//  Keyboard.println ("This is a keyboard demo");
//  delay(1000);
//  Keyboard.print("See 3 left arrow presses then 3 right");
//  delay(1000);
//  
//  
//  for ( int i=1; i<=3;i++)
//  {
//    Keyboard.press(KEY_LEFT_ARROW);
//    delay (500);
//    Keyboard.release(KEY_LEFT_ARROW); 
//  }
//   for ( int i=1; i<=3;i++)
//  {
//    Keyboard.press(KEY_RIGHT_ARROW);
//    delay (700);
//    Keyboard.release(KEY_RIGHT_ARROW); 
//  }
//  
//  Keyboard.println("");
//  delay(3000);
//  
//  
//  Keyboard.print("Now See 3 up arrow presses then 3 down");
//  delay(3000);
//  
//  for ( int i=0; i<3;i++)
//  {
//  Keyboard.press(KEY_UP_ARROW);
//  delay (700);
//  Keyboard.release(KEY_UP_ARROW);
//  }
//  
//  for ( int i=0; i<3;i++)
//  {
//  Keyboard.press(KEY_DOWN_ARROW);
//  delay (500);
//  Keyboard.release(KEY_DOWN_ARROW);
//  }
  
  
  
}

void loop() 
{
  
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
 {
//  char inChar = Serial.read(); //open arduino serial monitor and type the letter on the keyboard, this will trigger key presses
  char inChar = Serial1.read(); //read from ble serial
   switch (inChar)
  {
//The following cases move the mouse cursor based on the data stored in the inChar variable
    case 'u':
      Mouse.move(0, -50);
      Serial.println("hello");
      break;
    case 'd':
      Mouse.move(0, 50);
      break;
    case 'l':
      Mouse.move(-50, 0);
      break;
    case 'r':
      Mouse.move(50, 0);
      break;
    case 'c':
      Mouse.click(MOUSE_RIGHT);
      break;
    default:
      Serial.println("unkown");
      break;
   }
  }
  
  delay(500);
    
}

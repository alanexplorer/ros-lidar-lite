// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPin = 8; 
// Create a servo object 
Servo Servo1; 
void setup() { 
   // We need to attach the servo to the used pin number 
   Servo1.attach(servoPin); 
}
void loop(){
  int i = 0;
  for (i = 0; i < 180; i+=10) {
    Servo1.write(i); 
    delay(100);
  }
  for (i = 0; i < 180; i+=10) {
    Servo1.write(180 - i); 
    delay(100);
  }
}

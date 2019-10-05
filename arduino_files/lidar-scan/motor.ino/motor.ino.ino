#include <Servo.h> 
 
const int pinoServo = 6;
 
Servo s; 
int pos; 
 
void setup (){

  Serial.begin(115200);
  delay(1000);
  s.attach(pinoServo);
  s.write(0);
}
void loop(){
 
}

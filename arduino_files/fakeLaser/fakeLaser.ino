void setup() {
  // put your setup code here, to run once:

  float distance = 0;
  float motor = 0;
  int N = 360;


}

void loop() {
 
    for(int i = 0; i < N; i++) {
      
      Serial.print(i); 
      Serial.print(",");
      Serial.print(fakeLaser()); 
      Serial.println();
      
    }
}

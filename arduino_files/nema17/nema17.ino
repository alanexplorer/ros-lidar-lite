    /*Example sketch to control a stepper motor with A4988/DRV8825 stepper motor driver and Arduino without a library. More info: https://www.makerguides.com */
    // Define stepper motor connections and steps per revolution:
    #define dirPin 2
    #define stepPin 3
    #define stepsPerRevolution 200
    #define buttonPin 4
    int buttonState = 0;
    bool started = false;
 
    void setup() {
      // Declare pins as output:
      pinMode(stepPin, OUTPUT);
      pinMode(dirPin, OUTPUT);
    }
    void checkButton() {
      // Read button state
      buttonState = digitalRead(buttonPin);
      // And start moving motor
      if (buttonState == HIGH) {
        if (started)
          started = false;
        else 
          started = true;
      }
    }
    void loop() {
      checkButton();

      if (started) {
        // Set the spinning direction clockwise:
        digitalWrite(dirPin, HIGH);
        // Spin the stepper motor 1 revolution slowly:
        for (int i = 0; i < 200; i++) {
          // These four lines result in 1 step:
          digitalWrite(stepPin, HIGH);
          delayMicroseconds(2000);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(2000);
        }
        
      }

    }

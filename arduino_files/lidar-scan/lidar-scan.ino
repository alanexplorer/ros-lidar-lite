/*------------------------------------------------------------------------------
  LIDARLite Arduino Library
  v3/GetDistanceI2c
  This example shows how to initialize, configure, and read distance from a
  LIDAR-Lite connected over the I2C interface.
  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND
  (Capacitor recommended to mitigate inrush current when device is enabled)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND
  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf
------------------------------------------------------------------------------*/

#include <Wire.h>
#include <LIDARLite.h>
#include "sync.h"
#include "TimerOne.h"
#include <AccelStepper.h>

// Define stepper motor connections and steps per revolution:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1 //The motorinterface type must be set to 1 when using a step and direction driver
#define stepsPerRevolution 200

LIDARLite myLidarLite;

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

const int steps = 200; // Makes 200 pulses/1.8 angle per step, for making one full cycle rotation
Sync sync(steps, 41, 60); // Steps Per Revolution, number of teeth in inputGear, number of teeth in outputGear
const int outputSteps = sync.get_outputStepsPerRevolution(); // steps on inputGear for a complete cycle in outputGear

 int index = 0;
 
//clock_t startTime;
int reading = 0;

void setup()
{

  Serial.begin(115200); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  stepper.setMaxSpeed(1000); // Set the maximum speed in steps per second

}

void loop()
{
  
  stepper.setCurrentPosition(0); // Set the current position to 0

  // Run the motor forward at 100 steps/second until the motor reaches 200 steps (1 revolutions):
  
  while(stepper.currentPosition() != 200)
  {
    reading = myLidarLite.distance(); //read distance on laser
    sync.set_motorPos(stepper.currentPosition()); // update motor'position
    stepper.setSpeed(100);
    stepper.runSpeed();
    
    Serial.print(index);
    Serial.print(",");
    Serial.print(stepper.currentPosition());
    Serial.print(",");
    Serial.print( (float) reading / 100.0); //value for ranges[] in meters
    Serial.println();

    

//    if(index == 200){
//      index = 0;
//    }
//    else{
//      index++;
//    }
//    
//    Serial.print(index);
//    Serial.print(",");
//    Serial.print(sync.fakeLaserAngle(index));
//    Serial.print(',');
//    Serial.print(sync.fakeLaser());
//    Serial.println();
//    delay(100);
  
  }
}

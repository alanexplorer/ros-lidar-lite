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
#include <AccelStepper.h>
#include "TimerOne.h"


LIDARLite myLidarLite;

const int steps = 200; // Makes 200 pulses/1.8 angle per step, for making one full cycle rotation
Sync sync(steps, 40, 60); // Steps Per Revolution, number of teeth in inputGear, number of teeth in outputGear
const int outputSteps = sync.get_outputStepsPerRevolution(); // steps on inputGear for a complete cycle in outputGear


//clock_t startTime;
int reading = 0;
long tNew, tOld;  // time in milliseconds()


AccelStepper stepper(2, 2,3);

void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  tOld = 0.0;

  stepper.setMaxSpeed(2000);
  stepper.setSpeed(500);  

}

void loop()
{
  
  for(int i = 0; i < outputSteps; i++) {

    reading = myLidarLite.distance(); //read distance on laser
    sync.set_motorPos(i); // update motor'position

    stepper.runSpeed();

    Serial.print( i ); // Print data index first
    Serial.print(",");
    Serial.print( sync.get_laserAngle() * 3.1415 / 180.0 ); // Laser angle in radians
    Serial.print(",");
    Serial.print(reading); //value for ranges[] a
    Serial.println();
    delay(10);

//    Serial.print(sync.fakeLaserAngle(i));
//    Serial.print(',');
//    Serial.print(sync.fakeLaser());
//    Serial.println();
//    delay(100);

  }
}

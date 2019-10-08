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
#include <Servo.h>
#include "TimerOne.h"


LIDARLite myLidarLite;

const int steps = 400; // Makes 400 pulses/0.9 angle per step, for making one full cycle rotation

Sync sync(steps); //steps Per Revolution

//clock_t startTime;
int reading = 0;
long tNew, tOld;  // time in milliseconds()

// defines pins numbers
const int stepPin = 3; 
const int dirPin = 4;

void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  tOld = 0.0;

  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

}

void loop()
{
  digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  
  for(int i = 0; i < steps; i++) {

    reading = myLidarLite.distance(); //read distance on laser
    sync.set_motorPos(i) // update motor'position
    sync.calculate_speed();

    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(500);

  }
  
  Serial.print( sync.get_motorPos() ); // index for ranges[]
  Serial.print(",");
  Serial.print(reading); //value for ranges[] 
  Serial.println();

}

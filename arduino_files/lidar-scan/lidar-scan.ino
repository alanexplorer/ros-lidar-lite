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

Sync sync(30); //steps Per Revolution

//clock_t startTime;
int reading = 0;
long tNew, tOld;  // time in milliseconds()

Servo s;
int pos; 
const int pinoServo = 6;
void setup()
{
  Serial.begin(115200); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  tOld = 0.0;

  s.attach(pinoServo);

  s.write(0);

}

void loop()
{
  reading = myLidarLite.distance();
  tNew = millis(); //return time in milliseconds since arduino was started

  sync.set_dT(tNew, tOld);
  sync.position_motor();
  sync.calculate_speed();

  Serial.print( sync.get_motorPos() ); // index for ranges[]
  Serial.print(",");
  Serial.print(reading); //value for ranges[]
  Serial.print(",");
  Serial.print(sync.get_secondsPerDegree(),3); //value time_increment 
  Serial.print(",");
  Serial.print(sync.get_dT());
  Serial.println();

  tOld = tNew;

  delay(500);
  sync.stepAdd();

}

/*------------------------------------------------------------------------------

  This Code is based on the  LIDARLite Arduino Library  GetDistanceI2c

  This code shows how to initialize, configure, and read distance from a
  LIDAR-Lite connected over the I2C interface and publish the data in a ROS topic.

  Connections:
  LIDAR-Lite 5 Vdc (red) to Arduino 5v
  LIDAR-Lite I2C SCL (green) to Arduino SCL
  LIDAR-Lite I2C SDA (blue) to Arduino SDA
  LIDAR-Lite Ground (black) to Arduino GND

  (Capacitor recommended for stability during fast operation)
  680uF capacitor (+) to Arduino 5v
  680uF capacitor (-) to Arduino GND

  See the Operation Manual for wiring diagrams and more information:
  http://static.garmin.com/pumac/LIDAR_Lite_v3_Operation_Manual_and_Technical_Specifications.pdf

------------------------------------------------------------------------------*/

#include "math.h"
#include <Servo.h>

//ROS includes
#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/LaserScan.h>
#include <Wire.h>
#include <LIDARLite.h>

float angle_min;
float angle_max;
float angle_increment;
float Time_increment;
float Scan_time;
float Range_min;
float Range_max;
float Ranges[180]; // max of 90 measurements
float Intensities[180];

int publisher_timer;
int laser_frequency = 1.8;
int point_reading = 180;
const int pin = 6 //digital pin used by servo
float time_Now,time_Later;

//objects
LIDARLite myLidarLite;
Servo s;

//ROS node handle
ros::NodeHandle  nh;

// ROS Serial Range message definition
sensor_msgs::LaserScan laser_msg;

// definition of the ROS publisher for the range data
ros::Publisher pub_range( "range_data", &laser_msg);

// Frame ID used in the ROS topics
char frameid[] = "/Lidar_frame";

void setup(){

  s.attach(pin); //digital pin association with Servo object

  s.write(0); // start the Servo at 0º position

  Serial.begin(9600); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  /* ROS related */
  nh.initNode();

  nh.advertise(pub_range);

  angle_min = 0; //start angle of the scan [rad]
  angle_max = M_PI; //end angle of the scan [rad]
  angle_increment = M_PI/point_reading; //angular distance between measurements [rad]
  Time_increment = ((1 /laser_frequency)/point_reading);  // time between measurements [seconds]
  Scan_time = 1.5; //time between scans [seconds]
  Range_min = 0.001; //minimum range value [m]
  Range_max = 40.00; //maximum range value [m]
  laser_msg.ranges_length = 90;
  laser_msg.intensities_length = 90;
  initRanges();

}

void initRanges(){
  for (int i = 0 ; i < 90; i++){
    Ranges[i] = i;
    Intensities[i] = i*i; //ângulo de varredura
  }
}

void loop(){

  if ((millis() - publisher_timer)> 50 ) {

      laser_msg.header.stamp = nh.now();
      laser_msg.header.frame_id = frameid;
      laser_msg.angle_min = angle_min;
      laser_msg.angle_max = angle_max;
      laser_msg.angle_increment = angle_increment;
      laser_msg.time_increment = Time_increment;
      laser_msg.range_min = Range_min;
      laser_msg.range_max = Range_max;

       // scan_time
      time_Later = millis();
      for (int i = 0 ; i < point_reading; i ++){
        delay(5);
        s.write((i+1)*2); //preciso testar
        // Serial.println((i+1)*2);
        Ranges[i] = myLidarLite.distance()/100.0;
        laser_msg.ranges[i] =  Ranges[i];
        laser_msg.intensities[i] =  Intensities[i];
      }

      time_Now  = millis();
      Scan_time = time_Now - time_Later;
      laser_msg.scan_time = Scan_time;
      pub_range.publish(&laser_msg);
      publisher_timer = millis() ;
    }
  nh.spinOnce();
  // delay(500);
}

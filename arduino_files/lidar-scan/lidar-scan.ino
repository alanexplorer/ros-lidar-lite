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
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

#define    LIDARLite_ADDRESS   0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure     0x00          // Register to write to initiate ranging.
#define    MeasureValue        0x04          // Value to initiate ranging.
#define    RegisterHighLowB    0x8f          // Register to get both High and Low bytes in 1 call.

#define    USB_USBCON

float angle_min;
float angle_max;
float angle_increment;
float time_increment;
float Scan_time;
float range_min;
float range_max;
float Ranges[30]; // max of 90 measurements
float Intensities[30];

int publisher_timer;
int laser_frequency = 40;
int point_reading = 30;
const int pin = 6; //digital pin used by servo
float time_Now,time_Later;

//objects
LIDARLite myLidarLite;
Servo s;

//ROS node handle
ros::NodeHandle  nh;

//ROS node tf
tf::TransformBroadcaster br;

//ROS geometry
geometry_msgs::TransformStamped t;

// ROS Serial Range message definition
sensor_msgs::LaserScan laser_msg;

// definition of the ROS publisher for the range data
ros::Publisher pub_range( "range_data", &laser_msg);

// Frame ID used in the ROS topics
char frameid[] = "/lidar_frame";
char base_link[] = "base_link";


double getRange()
{
  int val = -1;
  Wire.beginTransmission((int)LIDARLite_ADDRESS); 
  Wire.write((int)RegisterMeasure); 
  Wire.write((int)MeasureValue);   
  Wire.endTransmission(); 
  delay(10);

  Wire.beginTransmission((int)LIDARLite_ADDRESS);
  Wire.write((int)RegisterHighLowB); 
  Wire.endTransmission(); 
  delay(10); 
  Wire.requestFrom((int)LIDARLite_ADDRESS, 2);

  if(2 <= Wire.available()) {
   val = Wire.read(); 
   val = val << 8; 
   val = Wire.read();
  }
  return val*.01;
}

void setup(){

  s.attach(pin); //digital pin association with Servo object

  s.write(0); // start the Servo at 0º position

  Serial.begin(9600); // Initialize serial connection to display distance readings

  myLidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz

  myLidarLite.configure(0); // Change this number to try out alternate configurations

  /* ROS related */
  nh.initNode();

  br.init(nh);

  nh.advertise(pub_range);

  angle_min = 0; //start angle of the scan [rad]
  angle_max = M_PI; //end angle of the scan [rad]
  angle_increment = M_PI/point_reading; //angular distance between measurements [rad]
  time_increment = ((1 /laser_frequency)/point_reading);  // time between measurements [seconds]
  Scan_time = 1.5; //time between scans [seconds]
  range_min = 0.001; //minimum range value [m]
  range_max = 40; //maximum range value [m]
  laser_msg.ranges_length = 30;
  laser_msg.intensities_length = 30;

}

void loop(){

  time_Later = millis();
  laser_msg.header.frame_id = frameid;
  laser_msg.header.stamp = nh.now();
  laser_msg.angle_min = angle_min;
  laser_msg.angle_max = angle_max;
  laser_msg.angle_increment = angle_increment;
  laser_msg.time_increment = time_increment;
  laser_msg.range_min = range_min;
  laser_msg.range_max = range_max;
  laser_msg.ranges =  Ranges;
  laser_msg.intensities =  Intensities;

  for (unsigned int i = 0 ; i < point_reading; i ++){
    Ranges[i] = getRange();
    Intensities[i] = 10 + getRange();
  }

   
   t.header.stamp = nh.now();
   t.header.frame_id = base_link;

   t.child_frame_id = frameid;

   t.transform.translation.x = 0;
   t.transform.translation.y = 0;
   t.transform.translation.z = 0;

  for(unsigned int i = 0; i < point_reading; ++i){

   float angle = i*3;
   s.write(angle);

   t.transform.rotation = tf::createQuaternionFromYaw(angle);

   br.sendTransform(t);
    
    laser_msg.ranges[i] = Ranges[i];
    laser_msg.intensities[i] = Intensities[i];
   }

   laser_msg.ranges_length = point_reading;
   laser_msg.intensities_length = point_reading;

   time_Now  = millis();
   Scan_time = time_Now - time_Later;
   laser_msg.scan_time = Scan_time;
   pub_range.publish(&laser_msg);
  
  nh.spinOnce();
  delay(10);

}

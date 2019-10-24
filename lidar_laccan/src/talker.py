#!/usr/bin/python
import rospy
import serial
from sensor_msgs.msg import LaserScan
import std_msgs.msg
import math
import numpy as np

rospy.init_node('laser_scan')

pub = rospy.Publisher('scan', LaserScan, queue_size = 50)

num_readings = 200
laser_frequency = 4

scan = LaserScan()
scan.header.frame_id = 'frame_laser'
scan.angle_min = 0
scan.angle_max = 2*math.pi
scan.angle_increment = math.pi*2.0 / num_readings
scan.time_increment = 1.0 #(1.0/laser_frequency)/(num_readings) 
scan.range_min = 0.0
scan.range_max = 50.0
scan.ranges = np.zeros(num_readings, dtype = float)
scan.intensities = np.zeros(num_readings, dtype = float)

def is_float(value):
    try:
        float(value)
        return True
    except:
        return False

try:
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=0.050)

except(rospy.ServiceException, rospy.ROSException), e:
    ser.close()
    rospy.logerr("Unable to open port: %s" % (e,))

if ser.isOpen():
    rospy.loginfo("Serial Port initialized")
else:
    rospy.loginfo("Error Serial Port")

rate = rospy.Rate(10)

lostData = 0 #count Decode Error
     
while not rospy.is_shutdown():
    scan.header.stamp = rospy.Time.now()
    try:
        if (ser.inWaiting()): #if serial available
            data = ser.readline().decode().rstrip() # remove newline and carriage return characters
            data = data.split(',')
            if len(data) == 2:
                if is_float(data[0]) and is_float(data[1]):
                    pos_motor = float(data[0])
                    index = pos_motor/1.8
                    scan.ranges[int(index)] = float(data[1])
                    scan.intensities[int(index)] = float(data[1])
                
        else:
            lostData=+1
    except UnicodeDecodeError:# catch error and ignore it
        lostData=+1
    
    pub.publish(scan)
    rate.sleep()

print('Amount of data lost', lostData)
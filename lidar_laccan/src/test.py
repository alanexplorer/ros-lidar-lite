#!/usr/bin/python
import rospy
import serial
from sensor_msgs.msg import LaserScan
import std_msgs.msg
import math


ser = serial.Serial('/dev/ttyACM0', 115200)


while not rospy.is_shutdown():
    if (ser.inWaiting() > 0):
        #data = ser.readline().decode("utf-8").strip('\n').strip('\r') 
        data = ser.readline().decode().rstrip() # remove newline and carriage return characters
        print(data)


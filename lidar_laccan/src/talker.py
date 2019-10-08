#!/usr/bin/python
import rospy
import serial
from sensor_msgs.msg import LaserScan
import std_msgs.msg


rospy.init_node('laser_scan')

ser = serial.Serial('/dev/ttyACM0', 115200)
pub = rospy.Publisher('scan', LaserScan, queue_size = 50)

num_readings = 400
laser_frequency = 4

scan = LaserScan()
scan.header.stamp = rospy.Time.now()
scan.header.frame_id = rospy.get_param('laser_frame') 
scan.angle_min = 0
scan.angle_max = 2*math.pi
scan.angle_increment = math.pi*2.0 / num_readings
scan.time_increment = 1.0 #(1.0/laser_frequency)/(num_readings) 
scan.range_min = 0.0
scan.range_max = 40.0
scan.ranges = []
scan.intensities = []

r = rospy.Rate(10.0)

try:
     while not rospy.is_shutdown():
        if (s.inWaiting() > 0):
            #data = ser.readline().decode("utf-8").strip('\n').strip('\r') 
            data = ser.readline().decode().rstrip() # remove newline and carriage return characters
            pos, distance = data # get pos array and distance for array ranges

            for i in range(0, num_readings):
                scan.ranges[pos] = distance
                scan.intensities[pos] = distance
except:
        rospy.loginfo("Control node terminated.")
        #traceback.print_exc()
        ser.close()
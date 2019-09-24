#!/usr/bin/python
import rospy
from sensor_msgs.msg import Range
import tf

"""
How to run?


rosrun rosserial_python serial_node.py /dev/ttyACM0

rosrun lidar_laccan range_listener.py

"""

def range_msg_cb(msg):
    print 'Read range value: {} cm'.format(msg.range * 100)

def update_tf(br, pos=[0, 0], theta=0):
    br.sendTransform((pos[0], pos[1], 0),
                    tf.transformations.quaternion_from_euler(0, 0, theta),
                    rospy.Time.now(),
                    'laser_lite_v3',
                    'world')

if __name__ == '__main__':
    rospy.init_node('range_listener')
    rospy.Subscriber('range_data', Range, range_msg_cb)
    br = tf.TransformBroadcaster()


    rate = rospy.Rate(30)
    pos = [0.5, 0]
    theta = 0
    
    print '[SCRIPT] Waiting messages from /range_listener'
    while( not rospy.is_shutdown() ):
        rate.sleep()
        update_tf(br, pos, theta)

import mediapipe as mp
import time
import re
import rospy
import utm
import serial
import threading
from robot_arm.msg import arm_angles

# send initializer message

def serial_send():
    print("hi")

def listener():
    # Arduino port
    ser_port = rospy.get_param('port2')
    ser = serial.Serial(ser_port, 9600)

    rospy.init_node('listener', anonymous=True)
    pub = rospy.Subscriber('/talker', arm_angles, serial_send) 

    rospy.spin()    



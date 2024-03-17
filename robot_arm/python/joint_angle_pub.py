from robot_arm_IK import inverse_kinematics
import rospy
import time
from robot_arm.msg import arm_dists, camera_dists

"""
def convert_talker():
    pub = rospy.Publisher('/joint_angles', arm_dists, queue_size=10)
    rospy.init_node('joint_angle_pub', anonymous=True)
    rate = rospy.Rate(5)
 
    message = arm_dists()

    while not rospy.is_shutdown:

        try:
            # arm_angles.one, arm_angles.two, arm_angles.three, arm_angles.four, arm_angles.five =  

            pub.publish(message)
            rospy.loginfo(message)
            rate.sleep()

        except rospy.ROSInterruptException:
            break
        except OSError:
            time.sleep(1)
            continue
"""
pub = rospy.Publisher("/arm_dists", arm_dists)


def listener():
    rospy.init_node('convert_node', anonymous=True)
    convert_sub = rospy.Subscriber("/camera_dists", camera_dists, callback)
    rospy.spin()

def callback(data):
    arm_array = robot_arm_IK.inverse_kinematics(data.x_dist, data.y_dist, data.z_dist, data.r, data.p, data.y)
    
    message = arm_dists()
    message.one = arm_array[0]
    message.two = arm_array[1]
    message.three = arm_array[2]
    message.four = arm_array[3]
    message.five = arm_array[4]
    pub.publish(message)

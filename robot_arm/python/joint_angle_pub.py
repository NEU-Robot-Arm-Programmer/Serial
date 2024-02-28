# from robot_arm_IK import inverse_kinematics
import rospy
import time
from ArmControl.msg import arm_angles

def joint_angle_pub():

    rate = rospy.Rate(5)
    while not rospy.is_shutdown:

        #Get data from Intel**
        message = angle_msg()
        message.angles = 40

        pub.publish(message)
        rospy.loginfo(message)
        rate.sleep()

if __name__ == '__main__':
    # parser = argparse.ArgumentParser()
    # parser.add_argument('port')
    # args = parser.parse_args()

    pub = rospy.Publisher('/joint_angles', arm_angles, queue_size=10)
    rospy.init_node('joint_angle_pub', anonymous=True)
    rate = rospy.Rate(5)
 
    message = angle_msg()
    message.angles = 40

    while not rospy.is_shutdown:

        try:
            

            pub.publish(message)
            rospy.loginfo(message)
            rate.sleep()

        except rospy.ROSInterruptException:
            break
        except OSError:
            time.sleep(1)
            continue

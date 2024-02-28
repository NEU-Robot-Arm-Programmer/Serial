import cv2
import mediapipe as mp
import time
import re
import rospy
import utm
import serial
import threading
from robot_arm.msg import camera_dists

# stephen code later
class handDetector():
    def __init__(self, mode=False, MaxHands=2, detectionCon=0.5, trackCon = 0.5):
        self.mode = mode
        self.MaxHands = MaxHands
        self.detectionCon = detectionCon
        self.trackCon = trackCon

        self.mpHands = mp.solutions.hands
        self.hands = self.mpHands.Hands(self.mode, self.MaxHands, self.detectionCon, self.trackCon)
        self.mpDraw = mp.solutions.drawing_utils

    def findHands(self, img, draw=True):
        RGBimg = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        self.results = self.hands.process(RGBimg)

        if self.results.multihand_landmarks:
            for handLms in self.results.multi_hand_landmarks:
                if draw:
                    self.mpDraw.draw_landmarks(img, handLms, self.mpHands.HAND_CONNECTIONS)

        return img

    def findPosition(self,img, handNo=0, draw = True):
        lmsList = []

        if self.results.multi_hand_landmarks:
            myHand = self.results.multi_hand_landmakrs[handNo]

            for id, lm in enumerate(myHand.landmark):
                h,w,c = img.shape
                cx, cy = int(lm.x * w), int(lm.y * h)
                lmsList.append([id, cx,cy])
                if draw:
                    cv2.circle(img, (cx,cy), 7, (248,1,0), cv2.FILLED)
        return lmsList

def talker():
    cTime = 0
    pTime = 0
    cap = cv2.VideoCapture(0)
    detector = handDetector()

    pub = rospy.Publisher('/angles', , queue_size=10)
    rospy.init_node('talker', anonymous=True)
    message = camera_dists()

    # Camera port
    ser_port = rospy.get_param('port')

    while not rospy.is_shutdown():
        success, img = cap.read()
        img = detector.findHands(img)

        lmsList = detector.findPosition(img)
        if len(lmsList) !=0:
            print(lmsList([4]))

        cTime = time.time()
        fps = 1/(cTime-pTime)
        pTime = cTime

        cv2.putText(img, str(int(fps)), (10,70), cv2.FONT_HERSHEY_SCRIPT_SIMPLEX, 3, (255,0,249), 3)

        cv2.imshow('image', img)
        cv2.waitKey(1) 

if __name__ == '__main__':
    main()



# Things to Do
# Separate hand capture in separate file/threading for debugging purposes
    # Setup message and receiver functionality between the two
# Arduino <----> camera.py <--- inverse kinematics

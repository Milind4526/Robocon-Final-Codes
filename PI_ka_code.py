import cv2
import argparse
import numpy as np
from imutils.video.pivideostream import PiVideoStream
import imutils
import time
from collections import deque
import serial
from time import sleep
ser = serial.Serial('/dev/ttyUSB0',57600)       ######NANO ADDRESS OVER USB######

    
def nothing(x):
    pass

cv2.namedWindow('image',0)

####################THRESHOLD FOR COLOR########################
Col={'Blue':[83,67,35,123,250,180],'Red':[157,102,73,187,186,180],   ####TO CHANGE IN 
     'Gold':[0,33,112,60,92,225]}                                    ####ACCORDANCE WITH
###############################################################      ####LIGHTING


cam= PiVideoStream(resolution=(400, 300), framerate=2).start()
time.sleep(5)

red=0
blue=0
gold=0


while 1:
    var=''
    fram=cam.read()
    fram=imutils.resize(fram,width=400)
    fram1=fram.copy()

    cropped=fram[150:300,100:200]                       #####ROI SELECTOR#####
    cv2.rectangle(fram,(150,300),(100,200),(0,0,0),3)   #####ROI SELECTOR#####
    blurred=cv2.medianBlur(cropped,19)
    for i in Col.keys():
        col_lst=Col[i]
        hsv=cv2.cvtColor(blurred,cv2.COLOR_BGR2HSV)
        lower=np.array(col_lst[0:3])
        upper=np.array(col_lst[3:6])
        mask=cv2.inRange(hsv,lower,upper)
        img = cv2.bitwise_and(cropped,cropped, mask =mask)
        cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                cv2.CHAIN_APPROX_SIMPLE)[1]
        if len(cnts) > 0:
            c = max(cnts, key=cv2.contourArea)
            ((x, y), radius) = cv2.minEnclosingCircle(c)
            M = cv2.moments(c)
            if (M["m00"] != 0):
                center = (int(M["m10"] / M["m00"])+220, int(M["m01"] / M["m00"])+160)
                if (radius >5 and radius < 100 and cv2.contourArea(c) > 500):
                    cv2.circle(fram, (int(x)+220, int(y)+160), int(radius),
                            (0, 255, 255), 2)
                    cv2.circle(fram, center, 3, (0, 0, 255), -1)
                    var=i
        if var=='Red':
            time.sleep(2)
            ser.write(str(1))
        elif var=='Blue':
            time.sleep(2)
            ser.write(str(2))
        elif var=='Gold':
            time.sleep(2)
            ser.write(str(3))
        else:
            ser.write('N')
        cv2.imshow('s',fram)
        k=cv2.waitKey(1) & 0xFF
        if k==ord('q'):
            break
cv2.destroyAllWindows()
cam.stop()

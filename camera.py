import cv2
import time
import sys
cam=cv2.VideoCapture(1)
count=0

while True:
 ret,frame=cam.read()
 cv2.imshow('kityo',frame)
 key=cv2.waitKey(10)
 if key==27:
  cam.release(1) 
  sys.exit()
  break
 if key==ord(' '):
     name="hand.jpg"
     print name
     cv2.imwrite(name,frame)
 

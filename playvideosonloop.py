import cv2
import numpy as np
import os

path = "/home/jc/robin/video_ads"
vid_list = os.listdir(path)

print(vid_list)
while(True):
    for i in range(len(vid_list)):
        print(vid_list[i])
        vid = cv2.VideoCapture("video_ads/"+vid_list[i])
        if (vid.isOpened()==False):
            print("Error opening vid.")
        cv2.startWindowThread()
        cv2.namedWindow(vid_list[i], cv2.WND_PROP_FULLSCREEN)
        cv2.setWindowProperty(vid_list[i], cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        while(vid.isOpened()):
            ret, frame = vid.read()
            if ret == True:
                cv2.imshow(vid_list[i], frame)
                if cv2.waitKey(25) & 0xFF ==ord('q'):
                    break
            else:
                break
        vid.release()
        cv2.destroyAllWindows()

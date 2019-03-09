"""
Author: Avneesh Mishra
Purpose: View video stream at camera `CAM_NO` (0 for webcam, 1 and above for external webcam)
"""
import cv2 as cv

CAM_NO = 1
cam = cv.VideoCapture(CAM_NO)

while (cam.isOpened()):
    ret_val, img = cam.read()
    cv.imshow("Video feed", img)

    key = cv.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        break

cam.release()
cv.destroyAllWindows()

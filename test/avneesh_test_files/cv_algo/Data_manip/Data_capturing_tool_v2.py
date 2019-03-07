"""
Author: Avneesh Mishra
Purpose: To build a tool to capture images and save it with the serial reading received
"""

# -------- List of parameters ---------
# Webcam number (for video feed)
CAM_NO = 0

import cv2 as cv

cam = cv.VideoCapture(CAM_NO)

print("The following are the controls\n",
      "\t", "'q' or ESC to quit","\n"
      "\t", "'c' or 's' to save the image along with serial return","\n"
      )
input("Press enter to move ahead...")
# Create windows
cv.namedWindow("Live Feed")
cv.moveWindow("Live Feed", 20, 20)
while cam.isOpened():
    ret, img = cam.read()
    cv.imshow("Live Feed", img)

    key = cv.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        print("Emergency exit called...")
        cam.release()
        break

cv.destroyAllWindows()

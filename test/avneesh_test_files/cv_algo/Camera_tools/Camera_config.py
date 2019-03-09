"""
Author: Avneesh Mishra
Purpose: A script to adjust the properties of a camera

Default properties of the camera we have are as follows
CAP_PROP_BRIGHTNESS = 128
CAP_PROP_APERTURE = -1  (N/A)
CAP_PROP_CONTRAST = 32
CAP_PROP_BACKLIGHT = 1.0    (N/A)
CAP_PROP_FPS = 30.0
CAP_PROP_SATURATION = 32
CAP_PROP_TEMPERATURE = 5559 (N/A)
"""

import cv2 as cv

CAM_NO = 1


# Create function for returning a configuration function
def configTrackbar(trackbarName, windowName, cam, propName, maxVal=255):
    """
    Creates a trackbar to adjust camera property
    :param cam: Camera object
    :param propName: Property "cv.CAP_PROP_*"
    :param maxVal: Maximum value of a property
    :param trackbarName: Name of the trackbar
    :param windowName: Name of window
    """
    def valueChanged(value):
        """
        Function valled when value is changed
        :param value: New value
        :return: None
        """
        cam.set(propName, value)
    cv.createTrackbar(trackbarName, windowName, int(cam.get(propName)), maxVal, valueChanged)


cam = cv.VideoCapture(CAM_NO)
cv.namedWindow("Settings")
print("Brightness:", cam.get(cv.CAP_PROP_BRIGHTNESS))
configTrackbar("Brightness", "Settings", cam, cv.CAP_PROP_BRIGHTNESS)
print("Contrast:", cam.get(cv.CAP_PROP_CONTRAST))
configTrackbar("Contrast", "Settings", cam, cv.CAP_PROP_CONTRAST)
print("Saturation:", cam.get(cv.CAP_PROP_SATURATION))
configTrackbar("Saturation", "Settings", cam, cv.CAP_PROP_SATURATION)

while cam.isOpened():
    ret, img = cam.read()
    cv.imshow("Feed", img)
    key = cv.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv.destroyAllWindows()
cam.release()

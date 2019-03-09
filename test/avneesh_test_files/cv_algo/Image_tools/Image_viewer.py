"""
Author: Avneesh Mishra
Purpose: View and inspect an image using the inspection tool
note: ../Camera_tools/images/captured_image.jpg contains GREEN color LEDs
note: ../Camera_tools/images/captured_image1.jpg contains RED color LEDs
"""
import cv2 as cv
# Location of the file to be read and read image
image_location = "../Camera_tools/images/captured_image2.jpg"
img = cv.imread(image_location)
# Grayscale conversion
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
# Display image in windows
cv.namedWindow("Image")
cv.moveWindow("Image", 700, 30)
cv.namedWindow("Image Gray")
cv.moveWindow("Image Gray", 10, 30)
# Display slidebar window for thresholding
THRESH_VALUE = 0    # High pass thresholding


# Callback function for the trackbar
def threshChangeTo(value):
    """
    Change threshold
    :param value: new value
    :return: None
    """
    global THRESH_VALUE
    THRESH_VALUE = value


cv.namedWindow("Settings")
cv.moveWindow("Settings", 900, 620)
cv.createTrackbar("Threshold", "Settings", 0, 255, threshChangeTo)
while True:
    cv.imshow("Image", img)
    cv.imshow("Image Gray", img_gray)
    # TODO: Add thresholding code
    key = cv.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv.destroyAllWindows()

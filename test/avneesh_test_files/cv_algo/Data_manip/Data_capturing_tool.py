"""
Author: Avneesh Mishra
Purpose: To build a tool to capture images and save it with the serial reading received in the
    serial
Usage:
    1. Run this program
    2. Capture images
        2.1. Click numbers from 0 to 7
    3. Click 'e' to save
"""

# -------- List of parameters ---------
# Webcam number (for video feed)
CAM_NO = 1
ADC_NUM = 0
PORT_ADDR = "/dev/ttyACM0"
PORT_BAUD_RATE = 115200
PORT_TIMEOUT = 2
SAVE_IMAGE_FILE_NAME = "ring_images.npy"
SAVE_ADC_READINGS_FILE_NAME = "ring_readings.npy"

import cv2 as cv
from Data_manip.Serial_communication_test.Serial_reader_v3 import SerialParser
import time
import numpy as np

ser_com = SerialParser(PORT_ADDR, PORT_BAUD_RATE, PORT_TIMEOUT)
cam = cv.VideoCapture(CAM_NO)

print("The following are the controls\n",
      "\t", "'q' or ESC to quit (nothing of the current session will be saved)", "\n",
      "\t", "'e' to exit the loop", "\n",
      "\t", "'c' or 's' to save the image along with serial return", "\n",
      "\t", "'d' or 'r' to remove the latest recorded observation", "\n",
      "\t", "A number between 0 and 7 to set the ADC number to it",
      "\nStarted program..."
      )
time.sleep(1)

# Create windows
cv.namedWindow("Live Feed")
cv.moveWindow("Live Feed", 20, 20)
images = []
adc_readings = []
while cam.isOpened():
    ret, img = cam.read()
    img_disp = img.copy()   # Image to display only
    cv.imshow("Live Feed", img_disp)
    key = cv.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        print("Emergency exit called...")
        exit(0)
    elif key == ord('e'):
        break
    elif key == ord('c') or key == ord('s'):
        # Save everything
        images.append(img)
        reading_adc = ser_com.getADCval(ADC_NUM)
        adc_readings.append(reading_adc)
        print("Recording number {i} saved, ADC value {a}".format(i=len(adc_readings), a=reading_adc))
    elif key == ord('d') or key == ord('r'):
        if len(adc_readings) >= 1:
            print("Recording number {i} deleted ".format(i=len(adc_readings)), end='')
            images.pop()
            adc_readings.pop()
            print("{i} left".format(i=len(adc_readings)))
        else:
            print("Recording stack empty")
    elif key >= ord('0') and key <= ord('7'):
        ADC_NUM = int(chr(key))
        print("ADC number set to {i}".format(i=ADC_NUM))


cam.release()
cv.destroyAllWindows()
del ser_com
adc_vals = np.array(adc_readings)
np.save(SAVE_ADC_READINGS_FILE_NAME, adc_vals)
img_vals = np.array(images)
np.save(SAVE_IMAGE_FILE_NAME, img_vals)

"""
Author: Avneesh Mishra
Purpose: To collect data, images and values from the analog serial monitor. Connect the
    microcontroller to PORT_ADDR and
"""
import serial
import re
import os
import cv2 as cv
import numpy as np

CAM_NO = 2
ADC_NO = 0
PORT_ADDR = "/dev/ttyACM0"
BAUD_RATE = 115200
cam = cv.VideoCapture(CAM_NO)
ser = serial.Serial(PORT_ADDR, BAUD_RATE)
imgs = []
vals = []


# Save the recorded data
def saveData(fname: str, fext: str = 'npy'):
    """
    Save the data in a .npy file
    :param fname: File name
    :param fext: File extension (without '.')
    :return: Names of the file saved as dictionary
        "imgs": Name of file containing imgs
        "vals": Name of file containing vals
    """
    global imgs, vals
    imgs = np.array(imgs)
    vals = np.array(vals).reshape((-1, 1))
    if os.path.exists("{n}_imgs.{e}".format(n=fname, e=fext)) or \
            os.path.exists("{n}_vals.{e}".format(n=fname, e=fext)):
        i = 1
        while True:
            if os.path.exists("{nm}{nu}_imgs.{ext}".format(nm=fname, nu=i, ext=fext)) \
                    or \
                    os.path.exists("{nm}{nu}_vals.{ext}".format(nm=fname, nu=i, ext=fext)):
                # Increase index number if any of the files already exist
                i += 1
                continue
            else:
                # Final base name decided
                fname = "{nm}{nu}".format(nm=fname, nu=i)
                break
    # Names under which they'll be saved
    save_names = {
        "imgs": "{fn}_imgs.{fe}".format(fn=fname, fe=fext),
        "vals": "{fn}_vals.{fe}".format(fn=fname, fe=fext)
    }
    np.save(save_names["imgs"], imgs)
    np.save(save_names["vals"], vals)
    return save_names


# Create and move windows
cv.namedWindow("Feed")
cv.moveWindow("Feed", 30, 30)
cv.namedWindow("Latest image")
cv.moveWindow("Latest image", 720, 30)
while cam.isOpened():
    # Read image
    ret, img = cam.read()
    if not ret:
        print("Lost image")
        continue
    img_disp = cv.putText(img.copy(), "Press 's' or 'c' to capture", (200, 470),
                          cv.FONT_HERSHEY_PLAIN, 1, (0, 0, 255))
    cv.imshow("Feed", img_disp)
    key = cv.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        # Emergency exit
        print("Emergency escape received...")
        break
    elif key == ord('s') or key == ord('c'):
        # Save value / Capture value
        # Get the analog value from serial
        req = "read {pno}".format(pno=ADC_NO)
        ser.write(req.encode('utf-8'))
        res_txt = str(ser.readline())[2:-5]
        num = int(re.split(': ', res_txt)[1])
        vals.append(num)
        # Append image
        img_disp = cv.putText(img.copy(), "{n}".format(n=num), (70, 460),
                              cv.FONT_HERSHEY_PLAIN, 2, (0, 0, 255))
        cv.imshow("Latest image", img_disp)
        imgs.append(img)
        print("Saved the image into 'imgs'")
        continue
    elif key == ord('d') or key == ord('o'):
        # Done / Over
        # Save the data recorded
        final_fname = saveData('data/data')
        print("Records saved in {fnm}".format(fnm=final_fname))
        break

cv.destroyAllWindows()
cam.release()

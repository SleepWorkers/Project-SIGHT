"""
Author: Avneesh Mishra
Purpose: Snap images from a webcam and save them as a file
"""

import cv2 as cv
import os

CAM_NO = 1
cam = cv.VideoCapture(CAM_NO)


# Function to save images
def saveImage(img, fname, fext):
    """
    Save image `img` as fname.fext
    :param img: Image tensor
    :param fname: File name (without extension)
    :param fext: Extension (without .)
    :return: Name of the final file
    :rtype: str
    """

    # TODO: Add an algorithm to create folders as well, if they don't exist. Folder name from fname

    if os.path.exists("{n}.{e}".format(n=fname, e=fext)):
        # print("Warning: File already exists. Going to append a number")
        i = 1
        while True:
            if os.path.exists("{name}{num}.{e}".format(name=fname, num=i, e=fext)):
                i += 1
                continue
            else:
                # print("Saving as {n}{num}.{e}".format(n=fname, num=i, e=fext))
                fname = "{n}{num}".format(n=fname, num=i)
                break
    cv.imwrite("{n}.{e}".format(n=fname, e=fext), img)
    return "{n}.{e}".format(n=fname, e=fext)


while cam.isOpened():
    ret, img = cam.read()
    if not ret:
        print("Lost image")
        continue
    img_disp = cv.putText(img.copy(), "Press 's' or 'c' to capture", (200, 470),
                          cv.FONT_HERSHEY_PLAIN, 1, (0, 0, 255))
    cv.imshow("Feed", img_disp)
    key = cv.waitKey(1) & 0xFF
    if key == ord('q') or key == 27:
        print("Emergency escape received...")
        break
    elif key == ord('s') or key == ord('c'):
        cv.destroyWindow("Feed")
        cv.imshow("Captured Image", img)
        final_name = saveImage(img, "images/captured_image", "jpg")
        print("Saving image as {fname}".format(fname=final_name))
        cv.waitKey(5000)
        break

cv.destroyAllWindows()
cam.release()
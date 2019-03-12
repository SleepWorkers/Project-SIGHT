"""
Author: Avneesh Mishra
Purpose: To create training set for the algorithms
"""
import cv2 as cv
import numpy as np
import time

# Properties
IMAGE_FILE = "images.npy"
POINT_FILE = "points.npy"
ANGLES_FILE = "angles.npy"
imgs = np.load(IMAGE_FILE)
currpoint = (0, 0)
points = []
final_points = []
angles = []
final_angles = []


# Main image loop has to be broken
class MainImageExitLoop(Exception):
    pass


# Mouse callback events
def mouseCallback(event, x, y, flags, params):
    global currpoint, angles
    if event == cv.EVENT_MOUSEMOVE:
        currpoint = (x, y)
    elif event == cv.EVENT_LBUTTONUP:
        points.append(np.array([x, y]))
        angles = retAngles(points)


# Return angles
def retAngles(points):
    """
    Return the angles between points
    :param points: array of np.array type
    :return:
    """
    if (len(points) < 3): # No angles possible
        return []
    def angle3pts(p1, p2, p3):
        a = np.linalg.norm(p3 - p2)
        b = np.linalg.norm(p3 - p1)
        c = np.linalg.norm(p1 - p2)
        theta = np.arccos((a**2 + c**2 - b**2)/(2*a*c))
        if np.cross(p1 - p2, p3 - p2) > 0:
            return theta
        else:
            return 2*np.pi - theta
    angles = []
    for i in range(1, len(points) - 1):
        angles.append(angle3pts(points[i-1], points[i], points[i+1]))
    return angles


print("The following are the controls\n",
      "\t", "'q' or ESC to perform an emergency exit", "\n",
      "\t", "'n' to go to the next image", "\n",
      "\t", "'r' to reselect the image points", "\n",
      "Please select the points and then go to the next image", "\n"
      "Started program..."
      )
time.sleep(1)
cv.namedWindow("Image")
cv.moveWindow("Image", 10, 30)
cv.setMouseCallback("Image", mouseCallback)
for i_index in range(len(imgs)):
    img = imgs[i_index]
    try:
        # For every single image in the imgs array
        while True:
            img_disp = cv.circle(img.copy(), currpoint, 3, (0, 0, 255), 2)
            for pt in points:
                # Make points that are selected
                img_disp = cv.circle(img_disp, tuple(pt), 10, (255, 125, 0), thickness=-1)
            if len(points) > 1:
                # Make the connecting lines
                for i in range(1, len(points)):
                    img_disp = cv.line(img_disp, tuple(points[i - 1]), tuple(points[i]), (0, 255, 0), 1)
                if len(points) > 2:
                    # Write the angles
                    for i in range(0, len(angles)):
                        angle_deg = np.round(np.degrees(angles[i]), 2)
                        img_disp = cv.putText(img_disp, str(angle_deg), tuple(points[i+1]),
                                              cv.FONT_HERSHEY_DUPLEX, 0.5, (0, 0, 255), 1)
            cv.imshow("Image", img_disp)
            key = cv.waitKey(2) & 0xFF
            if key == ord('q') or key == 27:
                # Execution error
                raise MainImageExitLoop
            elif key == ord('n'):
                # Next image
                final_points.append(np.array(points))
                final_angles.append(np.array(angles))
                points = []
                angles = []
                break
            elif key == ord('r'):
                # Retake the points
                points = []
                angles = []
    except MainImageExitLoop:
        print("Emergency exit called")
        exit(0)

cv.destroyAllWindows()
print("Points: ", final_points)
print("Angles: ", final_angles)
final_pts = np.array(final_points)
final_ang = np.array(final_angles)
np.save(POINT_FILE, final_pts)
np.save(ANGLES_FILE, final_ang)

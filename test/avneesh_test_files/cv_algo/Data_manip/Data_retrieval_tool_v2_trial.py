import cv2 as cv
import numpy as np

points = []
angles = []
currpoint = (0, 0)


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
        return None
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


cv.namedWindow("Image")
cv.moveWindow("Image", 10, 30)
cv.setMouseCallback("Image", mouseCallback)
# Generate an image
img = np.random.randint(0, 255, (480, 640, 3), 'uint8')
while True:
    img_disp = cv.circle(img.copy(), currpoint, 3, (0, 0, 255), thickness=2)
    for pt in points:
        # Make points that are selected
        img_disp = cv.circle(img_disp, tuple(pt), 10, (255, 125, 0), thickness=-1)
    if len(points) > 1:
        # If there are more than 2 points, connect them using a line
        for i in range(1, len(points)):
            img_disp = cv.line(img_disp, tuple(points[i-1]), tuple(points[i]), (0, 255, 0), thickness=1)
        if len(points) > 2:
            # Print angles
            for i in range(len(angles)):
                img_disp = cv.putText(img_disp,
                                      str(angles[i]),
                                      tuple(points[i + 1]),
                                      cv.FONT_HERSHEY_DUPLEX, 0.5, (0, 0, 255), 1)

    # Display the images
    cv.imshow("Image", img_disp)
    key = cv.waitKey(2) & 0xFF
    if key == ord('q') or key == 27:
        break

cv.destroyAllWindows()
print(points)
if len(points) > 2:
    print(angles)
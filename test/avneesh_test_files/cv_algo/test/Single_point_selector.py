import cv2 as cv
import numpy as np
# Shape of image
img_shape = {
    "rows": 480,
    "columns": 640
}
img_back = np.zeros([img_shape["rows"], img_shape["columns"]], 'uint8')
img_display = img_back.copy()
num_points_captured = 0
num_points = 5
points = np.empty([num_points, 2], 'uint8')


# Callback function
def mouse_callback(event, x, y, flags, param):
    global img_display, num_points, img_back
    if (event == cv.EVENT_MOUSEMOVE):
        img1 = cv.line(img_back.copy(), (x, 0), (x, img_shape["rows"]), color=255, thickness=1)
        cv.line(img1, (0, y), (img_shape["columns"], y), color=255, thickness=1)
        img_display = cv.putText(img1, "({px}, {py})".format(px=x, py=y), (x, y),
                                 cv.FONT_HERSHEY_PLAIN, 1, color=255, thickness=1)
    elif (event == cv.EVENT_LBUTTONUP):
        # Add point
        cv.circle(img_back, (x, y), 10, 127, -1)    


# Create windows
cv.namedWindow("Point Selection")
cv.moveWindow("Point Selection", 700, 50)
cv.namedWindow("Background")
cv.moveWindow("Background", 30, 200)
# Mouse callback on point selection window
cv.setMouseCallback("Point Selection", mouse_callback)
while True:
    cv.imshow("Point Selection", img_display)
    cv.imshow("Background", img_back)
    key = cv.waitKey(1) & 0xFF
    if key == ord('q'):
        break

cv.destroyAllWindows()

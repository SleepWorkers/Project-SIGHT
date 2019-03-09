# Author: Avneesh Mishra
# Purpose: Generate fake images for testing the vision algorithm
# Notes:
#   Camera Specifications: Images: 480, 640, 3

import numpy as np
import cv2 as cv

image_dims = {
    "width": 640,
    "height": 480
}


# Generate points on random
def generate_random_points(num_points, seedval=2):
    """
    Generates random coordinate points in space
    :param num_points: number of points to be generated
    :param seedval: seed values to be used in random point generation
    :return: numpy.ndarray 2D array of points
    """
    np.random.seed(seedval)
    # Actual code to generate point
    fr_cord = np.random.rand(num_points, 2)
    w_pts = np.array(fr_cord[:, 0] * image_dims["width"], 'int').reshape([num_points, 1])
    h_pts = np.array(fr_cord[:, 1] * image_dims["height"], 'int').reshape([num_points, 1])
    random_points = np.concatenate([w_pts, h_pts], axis=1)
    return random_points


# Point selection tool
def point_selection_tool(num_points=1):
    """
    Creates a window and let's you select points in it
    :param num_points: Number of points (1 by default)
    :return numpy.ndarray 2D array of points
    """
    # Empty points
    pts = np.empty([number_points, 2], dtype='int')
    for i in range(num_points):
        print("Point {n}".format(n=i))
        # Single point selector tool



# Code to produce a gaussian image
def generate_gray_image(points, dev=50, dfun=lambda i: 255-20*i):
    """
    Generate grayscale image with gaussians at every point
    :param points: Points in 2D array of [[x1, y1], [x2, y2]...], np.ndarray type
    :param dev: Deviation in gaussian curve, more the value, more is the spread
    :param dfun: Difernce function in the magniture for point 'i', lambda function
    :return: Grayscale image
    """
    ret_mask = np.zeros([image_dims["height"], image_dims["width"], 1], )
    for (i, [x, y]) in enumerate(points):
        # Gaussian function definition
        def gaussian_function(px, py):
            return np.exp(-((px - x)**2 + (py - y)**2)/dev**2)
        # Main processing
        print("Processing point {num}: ({cx}, {cy})".format(num=i, cx=x, cy=y))
        for cy in range(image_dims["height"]):
            for cx in range(image_dims["width"]):
                ret_mask[cy, cx] += dfun(i) * gaussian_function(cx, cy)
    return np.ndarray.astype(ret_mask, 'uint8')


number_points = 5
pts = generate_random_points(number_points)

img_display = generate_gray_image(pts, 40, lambda i: 255 - i * (255 - 150) / number_points)
cv.imshow("Result image", img_display)
cv.waitKey()
cv.destroyAllWindows()

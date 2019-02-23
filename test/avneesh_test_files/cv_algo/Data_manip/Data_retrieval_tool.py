"""
Author: Avneesh Mishra
Purpose: Retrieve the data captured
"""

import numpy as np
IMAGES_DATA_FILE = "data/data2_imgs.npy"
VALS_DATA_FILE = "data/data2_vals.npy"
imgs = np.load(IMAGES_DATA_FILE)
vals = np.load(VALS_DATA_FILE)

print("Shape of data")
print("Images:", np.shape(imgs))
print("Values:", np.shape(vals))

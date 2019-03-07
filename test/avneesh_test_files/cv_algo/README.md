# What is this?
This folder has the test codes for the CV algorithm. We've used Python here.

# Table of contents
- [What is this?](#what-is-this)
- [Table of contents](#table-of-contents)
- [Python libraries](#python-libraries)
- [Files and folders](#files-and-folders)
  - [Camera_tools](#cameratools)
  - [Data_manip](#datamanip)
  - [Image_tools](#imagetools)
  - [~~Fake\_image\_generator~~](#fakeimagegenerator)
- [Capturing your own data](#capturing-your-own-data)
  - [Principle](#principle)
- [References](#references)
  - [Library references](#library-references)


# Python libraries
We've used the following python libraries:

| **Library name** | **Purpose** |
| ----- | ----- |
| os | To interface with the operating system kernel, for file structures |
| re | Regular expression library |
| serial | Serial communication and interfacing with boards connected to USB |
| opencv | Computer vision purposes |
| numpy | Numeric computation |

# Files and folders
Let's explore the files and folders in detail
## [Camera_tools](./Camera_tools/)
Used to deal with camera (mainly). It has the following files:

| **File Name** | **Purpose** | 
| ---- | ---- |
| [*Camera\_config.py*](./Camera_tools/Camera_config.py) | Used to configure settings of a webcam for further purposes of this tutorial |
| [*Video_feed_preview.py*](./Camera_tools/Video_feed_preview.py) | Used to preview a video camera stream | 
| [*Snap\_image.py*](./Camera_tools/Snap_image.py) | Used to capture and store images (just for evaluation purposes) |

This folder also has the following subfolders:
- [**images**](./Camera_tools/images/): Stores the images captured using the [Snap\_image](./Camera_tools/Snap_image.py) tool.
  - These are essentially for evaluation purposes (for generating masks and figuring out how we can detect the LEDs in the image).

## [Data_manip](./Data_manip/)
Contains all the data manipulation tools. The detailed file explanation is as follows:

| **File name** | **Purpose** |
| ---- | ---- |
| [Data_capturing_tool.py](./Data_manip/Data_capturing_tool.py) | This tool is used to capture data and generate data files |
| [Data_retrieval_tool.py](./Data_manip/Data_retrieval_tool.py) | This tool is used to read data files |

> **Tip**: To know more about how to capture data, see the [data capturing section](#capturing-your-own-data).

This folder also has the following subfolders:
<!-- TODO: Work here -->
- [**data**](./Data_manip/data/): The data generated as `.npy` files. Currently, not all data files are available here.

## [Image_tools](./Image_tools/)
Image viewing tools are available here.

| **File Name** | **Purpose** |
| ---- | ---- |
| **Image_viewer.py** | Used to view the image and apply selective thresholding |

> **Note**: Thresholding is under #_todo_ and not an important feature for now.

## ~~[Fake\_image\_generator](./Fake_image_generator/)~~
> **Note**: :warning: Discontinued :warning:. This directory is no longer in support or development.

This directory contains files to generate fake sample images.

# Capturing your own data
To capture your own data, do the following:
1. Burn the program file on the microcontroller:
    - The description of this is available in the folders for microcontrollers.
      - [Arduino](../Arduino_codes/) or [TI_CC3220SF](TI_CC3220SF_WiFi_MCU)
2. Run the script [Data_capturing_tool.py](Data_manip/Data_capturing_tool_v1.py).
3. Follow the instructions 
    - `'c'` or `'s'` to save
    - `'d'` or `'o'` when done
    - `'q'` or `ESC` to break out of the program.

## Principle
The principle is:
- To get `N + 2` points in an image having `N` joints, with every joint being a point and two reference. 
  - We use LEDs to get all these points
- Simultaneously, a flex sensor is also connected to the circuit and the response of this is read by the ADC of microcontroller which is in direct communication with the python script
- So now that the python script has all control, it can prepare a dataset.
- For now, the dataset is basically image and value pairs in `.npy` files.

# References
## Library references
1. **Numpy**: [Manual](https://docs.scipy.org/doc/numpy/index.html)
2. **OpenCV**: [Docs](https://docs.opencv.org/)
3. **PySerial**: [readthedocs](https://pyserial.readthedocs.io/en/latest/pyserial_api.html#exceptions)
4. **ReGex**: [W3Schools](https://www.w3schools.com/python/python_regex.asp#split)

[![TheProjectsGuy developer shield][TheProjectsGuy-dev-shield]][TheProjectsGuy-dev-profile]

[TheProjectsGuy-dev-shield]: https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg
[TheProjectsGuy-dev-profile]: https://github.com/TheProjectsGuy

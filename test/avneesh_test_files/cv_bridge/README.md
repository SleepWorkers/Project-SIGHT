# What is this?
This is the folder for the CV bridge made to create a training algorithm for flex sensors. The main goal is to create an algorithm that gives out joint angles from flex sensor readings.

# Table of contents
- [What is this?](#what-is-this)
- [Table of contents](#table-of-contents)
- [Files and folders](#files-and-folders)
  - [TI Board](#ti-board)
    - [CC3220SF](#cc3220sf)
      - [ADC Serial code](#adc-serial-code)
- [Versions](#versions)
  - [Version 1](#version-1)

# Files and folders
## TI Board 
The code written for TI boards

### CC3220SF
The codes written for the board `TI SimpleLink CC3220SF WiFi MCU`.

#### [ADC Serial code](./TI_Board_codes/CC3220SF/ADC_Mux_v1_empty_CC3220SF_LAUNCHXL_tirtos_ccs)
This is code uploaded to the board to read data from serial monitor.

# Versions
The following iterations were tried for accomplishing the task

## [Version 1](./v1/)
Follow the following steps to generate data for training:
1. Upload the ADC Serial code on the microcontroller
2. Open the [Data_capturing_tool.py](./v1/Data_capturing_tool.py) file
3. Run the script with the correct variables. Read the instruction given on the console.
4. After all has been captured, end program with an `e` key.
5. The data just generated has serial readings and images

Now, you can use the [Data_retrieval_tool.py](./v1/Data_retrieval_tool.py) file to generate joint angles from images using the point selection tool. Perform the following:
1. Run the script
2. Use mouse to select points. Go to the next image using `n` key
3. End after everything is done

The new file for `ANGLES_FILES` variable is the angles file and ADC values were already stored in `SAVE_ADC_READINGS_FILE_NAME` file from *Data capturing tool*. Now we have the data to train a model.

[![TheProjectsGuy developer shield][TheProjectsGuy-dev-shield]][TheProjectsGuy-dev-profile]

[TheProjectsGuy-dev-shield]: https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg
[TheProjectsGuy-dev-profile]: https://github.com/TheProjectsGuy

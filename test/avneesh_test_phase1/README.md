# What is this?
All the testing done by [@TheProjectsGuy](https://github.com/TheProjectsGuy) (Avneesh Mishra) resides in this folder.

# Table of Contents
- [What is this?](#what-is-this)
- [Table of Contents](#table-of-contents)
- [How to use the tests?](#how-to-use-the-tests)
  - [Ubuntu](#ubuntu)


# How to use the tests?

## Ubuntu
Open terminal and type the following:
- If you've not cloned the repository
    ```bash
    git clone -b avneesh-test-phase1 https://github.com/SleepWorkers/Project-SIGHT.git
    ```
    - If you're using SSH, you can use `git@github.com:SleepWorkers/Project-SIGHT.git` instead.
- If you've already cloned the repository
    ```bash
    git fetch origin avneesh-test-phase1
    ```
- Now, checkout the branch `avneesh-test-phase1` for the latest list of files.
    ```bash
    git checkout avneesh-test-phase1
    ```
- Now, you can navigate and open any file from the location at which you've cloned. For example, to open `FlexSensor_voltage_divider.slx`, perform the following steps:
  - Open **MATLAB** on your system
  - Run the command `simulink` to start simulink.
  - Choose **open** and navigate to the `FlexSensor_voltage_divider.slx` file under `MATLAB_tests/Simulink/FlexSensor_voltage_divider.slx` and the file will be opened.

The exact procedure to open files might be given in the README documents in the directories of this folder.

[![TheProjectsGuy developer shield](https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg)](https://github.com/TheProjectsGuy)

# What is this?
All the testing done by [@TheProjectsGuy](https://github.com/TheProjectsGuy) (Avneesh Mishra) resides in this folder.

# Table of Contents
- [What is this?](#what-is-this)
- [Table of Contents](#table-of-contents)
- [Directory structure](#directory-structure)
  - [Visible directories](#visible-directories)
  - [Hidden directories](#hidden-directories)
- [How to use the tests?](#how-to-use-the-tests)
  - [Windows](#windows)
  - [Ubuntu](#ubuntu)

# Directory structure
The directory structure is given below

## Visible directories
| **Directory name** | **Purpose** |
| --- | --- |
| [*arduino\_test\_files*](./arduino_test_files/) | Used to store files generated while testing things on the Arduino platform |
| [*MATLAB\_tests\_version1*](./MATLAB_tests_version1/) | MATLAB Files generated for first test iteration (see [this issue](https://github.com/SleepWorkers/Project-SIGHT/issues/16#issuecomment-460722749)) |
| [*MATLAB\_tests\_version2*](./MATLAB_tests_version2/) | MATLAB Files generated for second test iteration (see [this issue](https://github.com/SleepWorkers/Project-SIGHT/issues/16#issuecomment-460722749)) |

## Hidden directories
| **Directory name** | **Purpose** |
| --- | --- |
| [*.media*](./.media) | Used to store documentation resources |

# How to use the tests?

## Windows
- Open [GitHub Desktop](https://desktop.github.com/) and clone the repository `https://github.com/SleepWorkers/Project-SIGHT.git`.
    > **Tip**: If you're using SSH, you can use `git@github.com:SleepWorkers/Project-SIGHT.git` instead (for the link).

- Checkout the `avneesh-test-phase1` branch.
- Open the file that you want to inspect using the appropriate application for that file after that.

## Ubuntu
Open terminal and type the following:
- If you've not cloned the repository
    ```bash
    git clone -b avneesh-test-phase1 https://github.com/SleepWorkers/Project-SIGHT.git
    ```
    > **Tip**: If you're using SSH, you can use `git@github.com:SleepWorkers/Project-SIGHT.git` instead.
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

The exact procedure to open files and more documentation might be mentioned in the README documents in sub-directories of this folder.

[![TheProjectsGuy developer shield](https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg)](https://github.com/TheProjectsGuy)

---
# ADC Peripheral Testing using CC2640R2F

---

## Example Summary

This example is intended to showcase the integration of ADC created using Sensor Controller Studio with Code composer Studio.

## Peripherals Exercised

* `Board_GPIO_LED0`  - LED0
* 'Board_GPIO_LED1'  - LED1
* 'Board_GPIO_DIO28'  - ADC INPUT
* 'Board_GPIO_DIO29' - Reference Voltage
* 'Board_GPIO_DIO30' - Reference Voltage

## Resources & Jumper Settings

> If you're using an IDE (such as CCS or IAR), please refer to Board.html in
your project directory for resources used and board-specific jumper settings.
Otherwise, you can find Board.html in the directory
&lt;SDK_INSTALL_DIR&gt;/source/ti/boards/&lt;BOARD&gt;.


## Example Usage

* The example illustrates the following: 
The Sensor Controller ADC driver will measure an analog input voltage on one pin (DIO29) and set the green LED if the input ADC value is below a set threshold to indicate LOW input. If the ADC input value is above the set threshold it will notify the main application processor which then set the Red LED to indicate HIGH input. To vary the input voltage applied to the pin, an external voltage source can be connected to the analog input pin. In this example, a jumper from the LaunchPad is used to short the analog input pin with adjacent pins (DIO28 and DIO30). 

## Details 

* Please refer to the link attached:
http://dev.ti.com/tirex/content/simplelink_academy_cc2640r2sdk_2_40_03_00/modules/sensor_controller/sc_01_project_from_scratch/sc_01_project_from_scratch.html


## Application Design Details

TI-RTOS:

* When building in Code Composer Studio, the kernel configuration project will
be imported along with the example. The kernel configuration project is
referenced by the example, so it will be built first. The "release" kernel
configuration is the default project used. It has many debug features disabled.
These feature include assert checking, logging and runtime stack checks. For a
detailed difference between the "release" and "debug" kernel configurations and
how to switch between them, please refer to the SimpleLink MCU SDK User's
Guide. The "release" and "debug" kernel configuration projects can be found
under &lt;SDK_INSTALL_DIR&gt;/kernel/tirtos/builds/&lt;BOARD&gt;/(release|debug)/(ccs|gcc).

FreeRTOS:

* Please view the `FreeRTOSConfig.h` header file for example configuration
information.

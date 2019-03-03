# What is this?
This is the folder that stores all the examples for Code Composer Studio software to be used with `TI SimpleLink WiFi CC3220SF` wireless microcontroller.

# Table of contents
- [What is this?](#what-is-this)
- [Table of contents](#table-of-contents)
- [How to use the examples](#how-to-use-the-examples)
- [List of projects](#list-of-projects)
  - [Circular Blink](#circular-blink)
    - [Code](#code)
- [References](#references)
  - [CC3220SF TI Driver Documents](#cc3220sf-ti-driver-documents)
    - [GPIOs](#gpios)

# How to use the examples
Every folder is a project in it's own. You only have to move both the folders into a workspace directory and then build and upload the project. Each example is discussed in detail. 

> **Note**: When you're building a project, make sure that the release project is also from the same example folder.

For example, if you want to use the `CircularBlink` example and your workspace folder path is `~/ccs_ws/ws1/`, then you have to do the following:
- Copy the folder `CirculaBlink/CircularBlink_empty_CC3220SF_LAUNCHXL_tirtos_ccs` to your workspace folder path `~/ccs_ws/ws1/`.
- Copy the folder `CircularBlink/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs` to your workspace folder path `~/ccs_ws/ws1/`. This is for the project to build correctly.
- Build the code and upload to the board


# List of projects
## Circular Blink
This example basically blinks a debugger LED (D10, D9 or D8) and you can change which LED is blinking by pressing the switch SW2 to go left or switch SW3 to go right. 
So if say the red LED (D10) is blinking, by pressing SW2 (left switch), the left LED (D9, yellow LED) starts blinking. Press SW2 again and now the green one (D8) is blinking, press it again and the sequence rolls over and now the red one (D10) is blinking. By pressing the switch on the right (SW3), the exact opposite thing happens, the sequence shifts right instead of left.

### Code
The code is derived from the _empty_ template in the Examples provided in the SDK. Here's how we go about making it:
The specific example for this version is found in `Resource Explorer -> SimpleLink CC32xx SDK - v:2.40.02.00 -> Examples -> Development Tools -> CC3220SF LaunchPad -> TI Drivers -> empty -> TI-RTOS -> CCS Compiler -> empty`. We've made modifications to this particular file. This is exactly the `CircularBlink_empty_CC3220SF_LAUNCHXL_tirtos_ccs` file.

The files that have been modified are as follows:
- **empty.c**: The main code file, where we've attached interrupts to the buttons and set the LED pin modes.
- **Board.h**: Altered the following `#define` tags for the LEDs:
    ```cpp
    #define Board_GPIO_LED1 CC3220SF_LAUNCHXL_GPIO_LED_D9
    #define Board_GPIO_LED2 CC3220SF_LAUNCHXL_GPIO_LED_D8
    ```
    Check the **Usage** section of [GPIO.h File reference][cc3220sf-ti_driver_gpio_main].
- **CC3220SF_LAUNCHXL.c**: Added code for the LED configurations. The following has been altered in the _GPIO section_ to set the default configuration as output and low by default:
    ```cpp
    /* CC3220SF_LAUNCHXL_GPIO_LED_D9 */
    GPIOCC32XX_GPIO_10 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW,
    /* CC3220SF_LAUNCHXL_GPIO_LED_D8 */
    GPIOCC32XX_GPIO_11 | GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW,
    ```
    Check the **CC32xx GPIO Driver Configuration** section of the [GPIOCC32XX.h reference][cc3220sf-ti_driver_gpio_cc32xx].
- **CC3220SF_LAUNCHXL.h**: Added names in the *CC3220SF\_LAUNCHXL\_GPIOName* enumerator so that the `Board.h` file can parse it as board names (generic names). We've added the following at the same indexes corresponding to the list in *GPIO\_PinConfig* of `CC3220SF_LAUNCHXL.c` file. We've altered the following after `CC3220SF_LAUNCHXL_GPIO_LED_D10` in the enum `CC3220SF_LAUNCHXL_GPIOName`:
    ```cpp
    CC3220SF_LAUNCHXL_GPIO_LED_D9,
    CC3220SF_LAUNCHXL_GPIO_LED_D8
    ```

Then, we upload the code and observe the results.



# References

## CC3220SF TI Driver Documents 
- [**Main page**][cc3220sf-ti_driver_reference_page]

### GPIOs
General Purpose Input Output documentation:
- [**GPIO.h**][cc3220sf-ti_driver_gpio_main] reference
- [**GPIOCC32XX.h**][cc3220sf-ti_driver_gpio_cc32xx] reference

[cc3220sf-ti_driver_reference_page]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/index.html
[cc3220sf-ti_driver_gpio_main]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_g_p_i_o_8h.html
[cc3220sf-ti_driver_gpio_cc32xx]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_g_p_i_o_c_c32_x_x_8h.html

[![TheProjectsGuy developer shield][TheProjectsGuy-dev-shield]][TheProjectsGuy-dev-profile]

[TheProjectsGuy-dev-shield]: https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg
[TheProjectsGuy-dev-profile]: https://github.com/TheProjectsGuy

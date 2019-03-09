# What is this?
This is the folder that stores all the examples for Code Composer Studio software to be used with `TI SimpleLink WiFi CC3220SF` wireless microcontroller.

# Table of contents
- [What is this?](#what-is-this)
- [Table of contents](#table-of-contents)
- [How to use the examples](#how-to-use-the-examples)
- [List of projects](#list-of-projects)
  - [CircularBlink](#circularblink)
    - [Code](#code)
  - [CircularFade](#circularfade)
    - [Code](#code-1)
  - [SimpleMultimeter](#simplemultimeter)
    - [Code](#code-2)
    - [Usage](#usage)
- [References](#references)
  - [Information](#information)
  - [CC3220SF TI Driver Documents](#cc3220sf-ti-driver-documents)
    - [GPIOs](#gpios)
    - [PWM](#pwm)
    - [UART](#uart)
    - [ADC](#adc)

# How to use the examples
Every folder is a project in it's own. You only have to move both the folders into a workspace directory and then build and upload the project. Each example is discussed in detail. 

> **Note**: When you're building a project, make sure that the release project is also from the same example folder.

For example, if you want to use the `CircularBlink` example and your workspace folder path is `~/ccs_ws/ws1/`, then you have to do the following:
- Copy the folder `CirculaBlink/CircularBlink_empty_CC3220SF_LAUNCHXL_tirtos_ccs` to your workspace folder path `~/ccs_ws/ws1/`.
- Copy the folder `CircularBlink/tirtos_builds_CC3220SF_LAUNCHXL_release_ccs` to your workspace folder path `~/ccs_ws/ws1/`. This is for the project to build correctly.
- Build the code and upload to the board


# List of projects
## [CircularBlink](./CircularBlink/)
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
    Check the **Usage** section of [GPIO.h file reference][cc3220sf-ti_driver_gpio_main].
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

## [CircularFade](./CircularFade/)
In functionality, this example is the same as CircularBlink, the only difference is that here, the LEDs fade and brighten up instead of blinking, so it looks more gradual. Along with this, this example also demonstrates how to use only one function for two different interrupts and differentiating the interrupt caused by the index number (check the _empty.c_ file).

### Code
The code is derived from the _empty_ template in the Examples provided in the SDK. Here's how we go about making it:
The specific example for this version is found in `Resource Explorer -> SimpleLink CC32xx SDK - v:2.40.02.00 -> Examples -> Development Tools -> CC3220SF LaunchPad -> TI Drivers -> empty -> TI-RTOS -> CCS Compiler -> empty`. We've made modifications to this particular file. This is exactly the `CircularFade_empty_CC3220SF_LAUNCHXL_tirtos_ccs` file.

The files that have been modified are as follows:
- **empty.c**: The main code file, where we've attached interrupts to the buttons and set the LED pin modes. Main code is in the following lines:
    ```cpp
    // Driver initialization
    PWM_init();
    // Parameter initialization
    int i;
    for (i = 0; i < CC3220SF_LAUNCHXL_PWMCOUNT ; i++) {
        PWM_Params_init(&pwmParams[i]);
        pwmParams[i].idleLevel = PWM_IDLE_LOW;   // Ideally LOW level
        pwmParams[i].periodUnits = PWM_PERIOD_HZ;  // Period in Hz
        pwmParams[i].periodValue = 1e6;            // 1 MHz
        pwmParams[i].dutyUnits = PWM_DUTY_FRACTION;  // Duty is in fractional percentage
        pwmParams[i].dutyValue = 0;                  // 0% initial PWM
        // Create handler instance
        pwm[i] = PWM_open(pwmNames[i], &pwmParams[i]);
        // Start the PWM
        PWM_start(pwm[i]);
    }
    ```
    and
    ```cpp
    dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * count) / 100);  // Duty cycle
    PWM_setDuty(pwm[current_index], dutyValue);                                 // PWM value
    ```
- **Board.h**: Altered the following `#define` tags for the LEDs:
    ```cpp
    // #define Board_GPIO_LED0  CC3220SF_LAUNCHXL_GPIO_LED_D10 // Not used the debugger LED D10
    // PWM pins
    #define Board_PWM0  CC3220SF_LAUNCHXL_PWM1
    #define Board_PWM1  CC3220SF_LAUNCHXL_PWM2
    #define Board_PWM2  CC3220SF_LAUNCHXL_PWM3
    ```
    Here, the pin names have been initialized. Check the [PWM reference][cc3220sf-ti_driver_pwm_main] for more.
- **CC3220SF_LAUNCHXL.h**: Altered the `enum CC3220SF_LAUNCHXL_PWMName` to:
    ```cpp
    typedef enum CC3220SF_LAUNCHXL_PWMName {
        CC3220SF_LAUNCHXL_PWM1 = 0,
        CC3220SF_LAUNCHXL_PWM2,
        CC3220SF_LAUNCHXL_PWM3,

        CC3220SF_LAUNCHXL_PWMCOUNT
    } CC3220SF_LAUNCHXL_PWMName;
    ```
    These are just names given to PWM pins. These are again wrapped in `Board.h` header file for portability.
- **CC3220SF_LAUNCHXL.c**: Altered the PWM configurations section to match the debugger LED pins. You can check the main source for pin names in the `PWMTimerCC32XX.h` file. The following code is placed in the PWM section after the `#include` directives:
    ```cpp
    const PWMTimerCC32XX_HWAttrsV2 pwmTimerCC3220SHWAttrs[CC3220SF_LAUNCHXL_PWMCOUNT] = {
        {    /* CC3220SF_LAUNCHXL_PWM1 */
            .pwmPin = PWMTimerCC32XX_PIN_64     // Red LED
        },
        {    /* CC3220SF_LAUNCHXL_PWM2 */
            .pwmPin = PWMTimerCC32XX_PIN_01     // Yellow LED
        },
        {
            /* CC3220SF_LAUNCHXL_PWM3 */
            .pwmPin = PWMTimerCC32XX_PIN_02     // Green LED
        }
    };

    const PWM_Config PWM_config[CC3220SF_LAUNCHXL_PWMCOUNT] = {
        {
            .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
            .object = &pwmTimerCC3220SObjects[CC3220SF_LAUNCHXL_PWM1],
            .hwAttrs = &pwmTimerCC3220SHWAttrs[CC3220SF_LAUNCHXL_PWM1]
        },
        {
            .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
            .object = &pwmTimerCC3220SObjects[CC3220SF_LAUNCHXL_PWM2],
            .hwAttrs = &pwmTimerCC3220SHWAttrs[CC3220SF_LAUNCHXL_PWM2]
        },
        {
            .fxnTablePtr = &PWMTimerCC32XX_fxnTable,
            .object = &pwmTimerCC3220SObjects[CC3220SF_LAUNCHXL_PWM3],
            .hwAttrs = &pwmTimerCC3220SHWAttrs[CC3220SF_LAUNCHXL_PWM3]
        }
    };

    const uint_least8_t PWM_count = CC3220SF_LAUNCHXL_PWMCOUNT;
    ```

## [SimpleMultimeter](./SimpleMultimeter/)
This is a simple multimeter made using the ADC on board. The ADC pins are as follows:

| **Pin Number** | **Channel Number** | **Name** |
| ----- | ------ | ----- |
| Pin 58 | Channel 1 | Board_ADC0 |
| Pin 59 | Channel 2 | Board_ADC1 |
| Pin 60 | Channel 3 | Board_ADC2 |
| Pin 57<sup>\*</sup> | Channel 0 | |

<sup>\*</sup> Pin 57 is also used for RX line of UART0 serial, thus it's not used here.

### Code 
We've made the following modifications to the files of the `empty` project template:
- **empty.c**: Contains the main code, check the [file](./SimpleMultimeter/SimpleMultimeter_empty_CC3220SF_LAUNCHXL_tirtos_ccs/empty.c) for full details.
- **CC3220SF_LAUNCHXL.c**: The ADC section of this file was modified for the ADC configurations. 
    ```cpp
    const ADCCC32XX_HWAttrsV1 adcCC3220SHWAttrs[CC3220SF_LAUNCHXL_ADCCOUNT] = {
        {
            .adcPin = ADCCC32XX_PIN_58_CH_1
        },
        {
            .adcPin = ADCCC32XX_PIN_59_CH_2
        },
        {
            .adcPin = ADCCC32XX_PIN_60_CH_3
        }
    };

    const ADC_Config ADC_config[CC3220SF_LAUNCHXL_ADCCOUNT] = {
        {
            .fxnTablePtr = &ADCCC32XX_fxnTable,
            .object = &adcCC3220SObjects[CC3220SF_LAUNCHXL_ADC0],
            .hwAttrs = &adcCC3220SHWAttrs[CC3220SF_LAUNCHXL_ADC0]
        },
        {
            .fxnTablePtr = &ADCCC32XX_fxnTable,
            .object = &adcCC3220SObjects[CC3220SF_LAUNCHXL_ADC1],
            .hwAttrs = &adcCC3220SHWAttrs[CC3220SF_LAUNCHXL_ADC1]
        },
        {
            .fxnTablePtr = &ADCCC32XX_fxnTable,
            .object = &adcCC3220SObjects[CC3220SF_LAUNCHXL_ADC2],
            .hwAttrs = &adcCC3220SHWAttrs[CC3220SF_LAUNCHXL_ADC2]
        }
    };
    ```
    Check the [ADC reference](#adc) for more
- **CC3220SF_LAUNCHXL.h**: The names of pins are declared in an `enum` for _ADCNames_ are as shown below:
    ```cpp
    typedef enum CC3220SF_LAUNCHXL_ADCName {
        CC3220SF_LAUNCHXL_ADC0 = 0,
        CC3220SF_LAUNCHXL_ADC1,
        CC3220SF_LAUNCHXL_ADC2,

        CC3220SF_LAUNCHXL_ADCCOUNT
    } CC3220SF_LAUNCHXL_ADCName;
    ```
- **Board.h**: The names above are translated for the board and are used in the final code. The following lines were changed:
    ```cpp
    // All ADCs used
    #define Board_ADC0  CC3220SF_LAUNCHXL_ADC0
    #define Board_ADC1  CC3220SF_LAUNCHXL_ADC1
    #define Board_ADC2  CC3220SF_LAUNCHXL_ADC2
    #define Board_ADC_COUNT CC3220SF_LAUNCHXL_ADCCOUNT
    ```

### Usage
1. Select the right ADC in the file **empty.c** in the line:
    ```cpp
    adc = ADC_open(Board_ADC0, &adc_params);
    ```
2. Open a serial monitor
    - You can either use the CCS built in terminal. `Shift` + `Ctrl` + `Alt` + `T` and select the serial port with 115200 baud rate.
    - You can use an external app like [gtkterm](https://linux.die.net/man/1/gtkterm).
3. Supply voltage to pin and see the LEDs change brightness as well as values on the serial monitor.

> **Note**: The maximum input voltage to the ADCs is 1.5V

# References

## Information
- [**UART**][info_uart] communication reference.
- [**SPI**][info_spi] communication reference.
- [**I2C**][info_i2c] communication protocol.

[info_uart]: http://www.circuitbasics.com/basics-uart-communication/
[info_spi]: http://www.circuitbasics.com/basics-of-the-spi-communication-protocol/
[info_i2c]: http://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/

## CC3220SF TI Driver Documents 
Documentation for SimpleLink SDK built on TI RTOS
- [**Main page**][cc3220sf-ti_driver_reference_page]

### GPIOs
General Purpose Input Output documentation:
- [**GPIO.h**][cc3220sf-ti_driver_gpio_main] reference
- [**GPIOCC32XX.h**][cc3220sf-ti_driver_gpio_cc32xx] reference

### PWM
Pulse Width Modulation documentation:
- [**PWM.h**][cc3220sf-ti_driver_pwm_main] reference
- [**PWMTimerCC32XX.h**][cc3220sf-ti_driver_pwm_timer_cc32xx] reference

### UART
Universal Asynchronous Receiver/Transmitter documentation:
- [**UART.h**][cc3220sf-ti_driver_uart_main] reference
- [**UARTCC32XX.h**][cc3220sf-ti_driver_uart_cc32xx] reference
- [**UARTCC32XXDMA.h**][cc3220sf-ti_driver_uart_cc32xxdma] reference

### ADC
Analog to Digital Converter documentation:
- [**ADC.h**][cc3220sf-ti_driver_adc_main] reference
- [**ADCCC32XX.h**][cc3220sf-ti_driver_adc_cc32xx] reference

[cc3220sf-ti_driver_reference_page]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/index.html
[cc3220sf-ti_driver_gpio_main]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_g_p_i_o_8h.html
[cc3220sf-ti_driver_gpio_cc32xx]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_g_p_i_o_c_c32_x_x_8h.html
[cc3220sf-ti_driver_pwm_main]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_p_w_m_8h.html
[cc3220sf-ti_driver_pwm_timer_cc32xx]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_p_w_m_timer_c_c32_x_x_8h.html
[cc3220sf-ti_driver_uart_main]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_u_a_r_t_8h.html
[cc3220sf-ti_driver_uart_cc32xx]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_u_a_r_t_c_c32_x_x_8h.html
[cc3220sf-ti_driver_uart_cc32xxdma]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_u_a_r_t_c_c32_x_x_d_m_a_8h.html
[cc3220sf-ti_driver_adc_main]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_a_d_c_8h.html
[cc3220sf-ti_driver_adc_cc32xx]: http://dev.ti.com/tirex/content/simplelink_cc32xx_sdk_2_40_02_00/docs/tidrivers/doxygen/html/_a_d_c_c_c32_x_x_8h.html

[![TheProjectsGuy developer shield][TheProjectsGuy-dev-shield]][TheProjectsGuy-dev-profile]

[TheProjectsGuy-dev-shield]: https://img.shields.io/badge/Dev-TheProjectsGuy-0061ff.svg
[TheProjectsGuy-dev-profile]: https://github.com/TheProjectsGuy

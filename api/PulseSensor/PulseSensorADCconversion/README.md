---
# PulseSensorADCconversion

---

## Code Summary
This code enables you to convert the raw ADC values from a Pulse sensor to actual Voltage values measured in microvolts(uV).

## Peripherals Exercised

* `Board_ADC1` - ADC channel 1

## Resources & Jumper Settings

> If you're using an IDE (such as CCS or IAR), please refer to Board.html in
your project directory for resources used and board-specific jumper settings.
Otherwise, you can find Board.html in the directory
&lt;SDK_INSTALL_DIR&gt;/source/ti/boards/&lt;BOARD&gt;.


## Code Usage

* Example output is generated through use of Display driver APIs. Refer to the
Display driver documentation found in the SimpleLink MCU SDK User's Guide.

* Connect the Pulse sensors terminals to the supply voltage pin(5V or 3.3V in this case), Ground(0V) and to Analog Pin DIO24(A1). The code samples the input from the Analog port 1.

>__Important:__ Caution should be used when connecting the pins to analog inputs greater than 3VDC.

* Open a serial session (e.g. [`PuTTY`](http://www.putty.org/ "PuTTY's
Homepage"), etc.) to the appropriate COM port.
    * The COM port can be determined via Device Manager in Windows or via
`ls /dev/tty*` in Linux. Do not forget to put the baud rate 112500. 

The connection will have the following settings:
```
    Baud-rate:     115200
    Data bits:          8
    Stop bits:          1
    Parity:          None
    Flow Control:    None
```

* Run the example.

Example snippet of outputs:
```
Starting the Pulse sensor example

Pulse sensor raw result (0): 2956

Pulse sensor converted result (0): 3138640 uV

Pulse sensor raw result (1): 2958

Pulse sensor converted result (1): 3140736 uV

Pulse sensor raw result (2): 2955

Pulse sensor converted result (2): 3137584 uV

Pulse sensor raw result (3): 2956

Pulse sensor converted result (3): 3138640 uV

Pulse sensor raw result (4): 2954

Pulse sensor converted result (4): 3136528 uV

Pulse sensor raw result (5): 2956

Pulse sensor converted result (5): 3138640 uV

Pulse sensor raw result (6): 2956

Pulse sensor converted result (6): 3138640 uV

Pulse sensor raw result (7): 2955

Pulse sensor converted result (7): 3137584 uV

Pulse sensor raw result (8): 2954

Pulse sensor converted result (8): 3136528 uV

Pulse sensor raw result (9): 2954

Pulse sensor converted result (9): 3136528 uV
```

* The example outputs ten samples from `Board_ADC1`.

* The actual conversion result values may vary depending on the reference
voltage settings. Please refer to the board specific datasheet for more details.

## Application Design Details

This application uses one threads:

`threadFxn1` - performs the following actions:

1. Opens an ADC driver object.

2. Uses the ADC driver object to perform 10 samples and output the results.

3. Closes the ADC driver object.

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

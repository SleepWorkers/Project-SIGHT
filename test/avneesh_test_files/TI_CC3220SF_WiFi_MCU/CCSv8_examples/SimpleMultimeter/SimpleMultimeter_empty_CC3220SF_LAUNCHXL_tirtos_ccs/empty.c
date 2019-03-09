/*
 * Copyright (c) 2015-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== empty.c ========
 */

/* For usleep() */
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h>
#include <ti/drivers/PWM.h>

/* Board Header file */
#include "Board.h"

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    useconds_t time = 1e4;  // 10 millisecond delay

    /* Call driver init functions */
    // ==== UART ====
    UART_init();
    UART_Handle uart;   // UART handler
    UART_Params uartParams;
    UART_Params_init(&uartParams);
    uartParams.baudRate = 115200;
    uartParams.readEcho = UART_ECHO_ON;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.writeDataMode = UART_DATA_BINARY;
    uart = UART_open(Board_UART0, &uartParams);    // Started UART communication protocol
    char *text = "Initialized UART handler...\r\n";
    UART_write(uart, text, strlen(text));

    // ==== ADC =====
    ADC_init();
    ADC_Handle adc;     // ADC handler
    ADC_Params adc_params;
    ADC_Params_init(&adc_params);
    adc = ADC_open(Board_ADC0, &adc_params);
    uint16_t adcValue;     // Values read from the ADCs
    // Debugger message
    text = (char*) "Initialized ADCs...\r\n";
    UART_write(uart, text, strlen(text));

    // ==== PWM =====
    PWM_init();
    PWM_Handle pwm[Board_PWM_COUNT];
    int pwm_pins[Board_PWM_COUNT] = {
                                        Board_PWM0,     // Green LED
                                        Board_PWM1,     // Yellow LED
                                        Board_PWM2      // Red LED
    };
    PWM_Params pwm_params[Board_PWM_COUNT];
    uint32_t pwm_values[Board_PWM_COUNT];
    int i = 0;
    for (i = 0; i < Board_PWM_COUNT; i++) {
        // Initialize PWM parameters and generate handlers for all the pins
        PWM_Params_init(&pwm_params[i]);
        pwm_params[i].idleLevel = PWM_IDLE_LOW;
        pwm_params[i].periodValue = 1e6;
        pwm_params[i].periodUnits = PWM_PERIOD_HZ;
        pwm_params[i].dutyValue = 0;
        pwm_params[i].dutyUnits = PWM_DUTY_FRACTION;
        pwm[i] = PWM_open(pwm_pins[i], &pwm_params[i]);
        PWM_start(pwm[i]);
        pwm_values[i] = 0;
        PWM_setDuty(pwm[i], pwm_values[i]);
    }

    // ==== Main task ====
    text = (char *) "Operations started...";
    UART_write(uart, text, strlen(text));
    while (true) {
        usleep(time);
        // Get the ADC values
        ADC_convert(adc, &adcValue);
        int32_t adcval = adcValue;    // To get only the +ve part as an integer and not have uint issues
        // Print it on the serial
        char a[30];
        ltoa(adcval, a);
        strcat(a, "\r\n");
        UART_write(uart, a, strlen(a));
        // Light up the LEDs
        if (adcval <= 1365) {
            pwm_values[0] = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * adcval)/ 1365);
            pwm_values[1] = 0;
            pwm_values[2] = 0;
        } else if (adcval <= 2730){
            pwm_values[0] = PWM_DUTY_FRACTION_MAX;
            pwm_values[1] = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * (adcval - 1365))/ 1365);
            pwm_values[2] = 0;
        } else {
            pwm_values[0] = PWM_DUTY_FRACTION_MAX;
            pwm_values[1] = PWM_DUTY_FRACTION_MAX;
            pwm_values[2] = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * (adcval - 2730))/ 1365);
        }
        // Write the numbers to LEDs
        for (i = 0; i < Board_PWM_COUNT; i++) {
            PWM_setDuty(pwm[i], pwm_values[i]);
        }
    }
}


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
#include <stdlib.h>
#include <strings.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>
#include <ti/drivers/ADC.h>

/* Board Header file */
#include "Board.h"

/*
 * DEFINE tags
 */
#ifndef AMUX_CONFIG_ERROR
#define AMUX_CONFIG_ERROR -1
#endif

/*
 * Function prototypes
 */

int setLEDConfigs(long number);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Call driver init functions */
    GPIO_init();
    UART_init();
    ADC_init();

    ADC_Handle adc;
    ADC_Params adc_params;
    ADC_Params_init(&adc_params);
    adc = ADC_open(Board_ADC0, &adc_params);    // Pin 59 - Channel 2 ADC
    uint16_t adc_value;

    UART_Handle uart;
    UART_Params uart_params;
    char buffer[100];
    UART_Params_init(&uart_params);
    uart_params.readEcho = UART_ECHO_OFF;
    uart_params.baudRate = 115200;
    uart = UART_open(Board_UART0, &uart_params);
    while (1) {
        int ret = UART_read(uart, buffer, 100);
        if (ret != UART_STATUS_ERROR) { // If something useful is received on the UART terminal
            buffer[ret] = '\0'; // Trailing end character
            // READ command to read from ADCs
            if (strcmp(buffer, "READ\n") == 0) {
                strcpy(buffer, "READ received, send number\n"); // Ask for the number (for ADC pin selection)
                UART_write(uart, buffer, strlen(buffer));
                UART_read(uart, buffer, 100);
                long num = atol(buffer);
                // Set the pin configurations and read ADC
                int rstat = setLEDConfigs(num);
                if (rstat == AMUX_CONFIG_ERROR) {
                    // Pin configuration error
                    strcpy(buffer, "Selection configuration error\n");
                    UART_write(uart, buffer, strlen(buffer));
                    continue;
                } else {
                    // Setting configuration done, ask for ADC0_READ flag
                    ltoa(rstat, buffer);  // buffer -> "010"
                    strcpy(buffer, strcat(buffer, ", send ADC0_READ\n"));   // buffer -> "110, send ADC0_READ\n"
                    UART_write(uart, buffer, strlen(buffer));
                    ret = UART_read(uart, buffer, 100);
                    buffer[ret] = '\0';
                    if (strcmp(buffer, "ADC0_READ\n") == 0) {   // Got ADC0_READ flag
                        // Read ADC
                        ADC_convert(adc, &adc_value);
                        ltoa((long) adc_value, buffer);
                        strcpy(buffer, strcat(buffer, "\n"));   // buffer -> "4\n"
                        UART_write(uart, buffer, strlen(buffer));
                    } else {
                        strcpy(buffer, "Error, process failed\n");
                        UART_write(uart, buffer, strlen(buffer));
                        continue;
                    }
                    // Configurations done
                    continue;
                }
            } else {    // Invalid command received
                strcpy(buffer, "INVALID COMMAND\n");
                UART_write(uart, buffer, strlen(buffer));
            }
        }
    }
}

/*
 * Set the GPIO configurations for the analog selection IC
 *  D10 -> LSB (S0)
 *  D9 -> S1
 *  D8 -> S2
 */
int setLEDConfigs(long num) {
    int rnum;
    if (num >= 8 || num < 0) {
        rnum = AMUX_CONFIG_ERROR;
        return rnum;
    }
    // Set configurations
    // S0  (0th bit)
    if (num == 1 || num == 3 || num == 5 || num == 7) {
        rnum = 1;
        GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_ON);
    } else {
        rnum = 0;
        GPIO_write(Board_GPIO_LED0, Board_GPIO_LED_OFF);
    }
    // S1  (1st bit)
    if (num == 2 || num == 3 || num == 6 || num == 7) {
        rnum += 10;
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_ON);
    } else {
        rnum += 00;
        GPIO_write(Board_GPIO_LED1, Board_GPIO_LED_OFF);
    }
    // S2  (2nd bit)
    if (num == 4 || num == 5 || num == 6 || num == 7) {
        rnum += 100;
        GPIO_write(Board_GPIO_LED2, Board_GPIO_LED_ON);
    } else {
        rnum += 000;
        GPIO_write(Board_GPIO_LED2, Board_GPIO_LED_OFF);
    }
    return rnum;
}

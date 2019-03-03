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

/* Driver Header files */
#include <ti/drivers/GPIO.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

/*
 * ======== Memory Chunks =========
 */
// The data in this can change any time
volatile int num = 0;    // Index
// Pin values
uint_least8_t pin[] = {
                           Board_GPIO_LED0,    // Red
                           Board_GPIO_LED1,    // Yellow
                           Board_GPIO_LED2     // Green
    };

/*
 *  ====== Function Prototypes ======
 */
void moveBlinkLEDLeft(uint_least8_t index);
void moveBlinkLEDRight(uint_least8_t index);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* 1 second delay */
    uint32_t time = 1;

    /* Call driver init functions */
    GPIO_init();
    // I2C_init();
    // SPI_init();
    // UART_init();
    // Watchdog_init();
    int NO_PINS = sizeof(pin) / sizeof(uint_least8_t);
    // Attach interrupts to switches
    GPIO_setCallback(Board_GPIO_BUTTON0, moveBlinkLEDLeft);
    GPIO_setCallback(Board_GPIO_BUTTON1, moveBlinkLEDRight);
    // Attach everything
    GPIO_enableInt(Board_GPIO_BUTTON0);
    GPIO_enableInt(Board_GPIO_BUTTON1);
    /* Configure the LED pin */
    int i;
    for (i = 0; i < NO_PINS; i++) {
        // Configure all pins as OUTPUT
        GPIO_setConfig(pin[i], GPIO_CFG_OUT_STD);
    }

    /* Turn on user LED */
    GPIO_write(pin[num], Board_GPIO_LED_ON);

    while (1) {
        sleep(time);
        GPIO_toggle(pin[num]);
    }
}

/*
 * ====== Interrupt Functions =======
 */
// For SW2 on P4 of the board
void moveBlinkLEDLeft(uint_least8_t index) {
    // Turn OFF current LED
    GPIO_write(pin[num], Board_GPIO_LED_OFF);
    // SW2 pressed - Rotate left - Increase num
    num = (num + 1 > 2) ? 0 : num + 1;
}
// For SW3 on P5 of the board
void moveBlinkLEDRight(uint_least8_t index) {
    // Turn OFF current LED
    GPIO_write(pin[num], Board_GPIO_LED_OFF);
    // SW3 pressed - Rotate right - Decrease num
    num = (num - 1 < 0) ? 2 : num - 1;
}

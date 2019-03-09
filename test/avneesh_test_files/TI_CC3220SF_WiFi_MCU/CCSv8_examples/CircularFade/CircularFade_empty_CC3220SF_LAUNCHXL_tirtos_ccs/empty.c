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
#include <stdbool.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/PWM.h>
// #include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

/*
 * ======= Global variables ========
 */
volatile int current_index = 0;
void changeIndex(uint_least8_t index);
PWM_Handle pwm[CC3220SF_LAUNCHXL_PWMCOUNT];

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    useconds_t ustime = 10000;  // 10 ms increments
    uint32_t dutyValue;
    PWM_Params pwmParams[CC3220SF_LAUNCHXL_PWMCOUNT];
    int pwmNames[] = {
                    CC3220SF_LAUNCHXL_PWM1,  // Red
                    CC3220SF_LAUNCHXL_PWM2,  // Yellow
                    CC3220SF_LAUNCHXL_PWM3   // Green
    };
    /* Call driver init functions */
    // ==== PWM initializer functions ====
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
    // ==== GPIO initializer functions ====
    GPIO_init();
    GPIO_setCallback(Board_GPIO_BUTTON0, changeIndex);
    GPIO_setCallback(Board_GPIO_BUTTON1, changeIndex);
    GPIO_enableInt(Board_GPIO_BUTTON0);
    GPIO_enableInt(Board_GPIO_BUTTON1);
    // I2C_init();
    // SPI_init();
    // UART_init();
    // Watchdog_init();

    // PWM configuration
    dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * 0) / 100);  // Duty cycle
    for (i = 0; i < CC3220SF_LAUNCHXL_PWMCOUNT; i++) {
        PWM_setDuty(pwm[i], dutyValue);                                             // PWM value
    }

    int count = 0;
    bool increase = true;
    while (1) {
        usleep(ustime);
        if (increase) {
            count += 1;
        } else {
            count -= 1;
        }
        dutyValue = (uint32_t) (((uint64_t) PWM_DUTY_FRACTION_MAX * count) / 100);  // Duty cycle
        PWM_setDuty(pwm[current_index], dutyValue);                                 // PWM value
        if (count == 100 || count == 0) {
            increase = !increase;
        }
    }
}

// Interrupt function for SW2 and SW3
/*
 * SW2 -> index = 0
 * SW3 -> index = 1
 */
void changeIndex(uint_least8_t index) {
    // Make the current PWM 0
    PWM_setDuty(pwm[current_index], 0);
    switch (index) {
    case 0:
        current_index = (current_index >= 2) ? 0 : current_index + 1;  // Move left
        break;
    case 1:
        current_index = (current_index <= 0) ? 2 : current_index - 1;  // Move right
        break;
    default:
        break;
    }
}

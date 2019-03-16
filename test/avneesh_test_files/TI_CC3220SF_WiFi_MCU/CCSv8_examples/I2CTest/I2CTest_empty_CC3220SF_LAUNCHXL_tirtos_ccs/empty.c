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
#include <strings.h>
#include <stdio.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/I2C.h>
// #include <ti/drivers/SPI.h>
#include <ti/display/Display.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

// I2C Addresses
#define TMP006_ADDR 0x41
#define TMP006_SENSOR_HEX_ADDR 0x0001

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    /* Variables */
    useconds_t time = 50e3;
    uint16_t temp;
    uint8_t txBuffer[1];
    uint8_t rxBuffer[2];
    I2C_Handle i2c;
    I2C_Params i2c_params;
    I2C_Transaction i2c_transaction;

    /* Initialize drivers */
    Display_init();
    I2C_init();

    /* Open Display for UART */
    Display_Handle display = Display_open(Display_Type_UART, NULL);

    /* Open I2C and set parameters */
    I2C_Params_init(&i2c_params);
    i2c_params.bitRate = I2C_400kHz;
    i2c = I2C_open(Board_I2C_TMP, &i2c_params);
    i2c_transaction.slaveAddress = TMP006_ADDR;
    txBuffer[0] = TMP006_SENSOR_HEX_ADDR;
    i2c_transaction.writeBuf = txBuffer;
    i2c_transaction.writeCount = 1;
    i2c_transaction.readBuf = rxBuffer;
    i2c_transaction.readCount = 2;

    /* Start program */
    Display_printf(display, 0, 0, "Started I2C and UART Display, going to read TMP006 data soon");

    while (1) {
        // Wait for I2C transfer
        if (I2C_transfer(i2c, &i2c_transaction)) {
            /*
             * rxBuffer[0] = Upper byte
             * rxBuffer[1] = Lower byte
             * We have to right shift the entire thing (according to TMP006 datasheet)
             */
            temp = (rxBuffer[0] << 8) >> 2 | rxBuffer[1] >> 2;
            // If High byte MSB is set to 1, then compliment
            if (rxBuffer[0] & 0x80) {
                temp |= 0xF000;     // Sign extended value (put a -ve while printing)
            }
            temp /= 32; // Convert to 'deg C'
            Display_printf(display, 0, 0, "Temperature = %d (deg C)", temp);
        }
        // Delay
        usleep(time);
    }
    // Close I2C
    I2C_close(i2c);
    Display_printf(display, 0, 0, "Program closed");
}

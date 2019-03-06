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
// #include <ti/drivers/SDSPI.h>
// #include <ti/drivers/SPI.h>
// #include <ti/drivers/UART.h>
// #include <ti/drivers/Watchdog.h>

/* Board Header file */
#include "Board.h"

#include "scif.h"
#define BV(x)    (1 << (x))
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>

// Main loop Semaphore
Semaphore_Struct semMainLoop;
Semaphore_Handle hSemMainLoop;

// SWI Task Alert
Swi_Struct swiTaskAlert;
Swi_Handle hSwiTaskAlert;


void processTaskAlert(void)
{
    // Clear the ALERT interrupt source
    scifClearAlertIntSource();

    // Do SC Task processing here
    // Fetch 'state.high' variable from SC
    uint8_t high = scifTaskData.adcLevelTrigger.state.high;
    // Set Red LED to the state variable
    GPIO_write(Board_GPIO_RLED, high);

    // Acknowledge the ALERT event
    scifAckAlertEvents();
} // processTaskAlert


void scCtrlReadyCallback(void)
{

} // scCtrlReadyCallback

void scTaskAlertCallback(void)
{

    // Post to main loop semaphore
    Semaphore_post(hSemMainLoop);

} // scTaskAlertCallback


/*
 *  ======== mainThread ========
 */
void *tirtosScThread(void *arg0)
{

    // Semaphore initialization
    Semaphore_Params semParams;
    Semaphore_Params_init(&semParams);
    Semaphore_construct(&semMainLoop, 0, &semParams);
    hSemMainLoop = Semaphore_handle(&semMainLoop);

    /* Call driver init functions */
    GPIO_init();
    // I2C_init();
    // SDSPI_init();
    // SPI_init();
    // UART_init();
    // Watchdog_init();

    // Initialize the Sensor Controller
    scifOsalInit();
    scifOsalRegisterCtrlReadyCallback(scCtrlReadyCallback);
    scifOsalRegisterTaskAlertCallback(scTaskAlertCallback);
    scifInit(&scifDriverSetup);

    // Set the Sensor Controller task tick interval to 1 second
    uint32_t rtc_Hz = 1;  // 1Hz RTC
    scifStartRtcTicksNow(0x00010000 / rtc_Hz);

    // Configure Sensor Controller tasks
    scifTaskData.adcLevelTrigger.cfg.threshold = 600;

    // Start Sensor Controller task
    scifStartTasksNbl(BV(SCIF_ADC_LEVEL_TRIGGER_TASK_ID));


    while (1) {
        // Wait on sem indefinitely
        Semaphore_pend(hSemMainLoop, BIOS_WAIT_FOREVER);

        // Call process function
        processTaskAlert();
    }
}

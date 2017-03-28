/*
 * Copyright (c) 2015-2016, Texas Instruments Incorporated
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
 *  ======== main.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <pthread.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#include <ti/drivers/GPIO.h>

#include "Board.h"
#include "UARTUtils.h"
//////////////GPIO
#include "pin_mux_config.h"
#include "hw_types.h"
#include "hw_memmap.h"
#include "hw_gpio.h"
#include "pin.h"
#include "gpio.h"
#include "prcm.h"
#include "rom.h"
#include "rom_map.h"
///////////////////////////
#include "wificonfig.h"

extern void NetWiFi_init(void);
extern void runAWSClient(void);
extern void vinayudp(void);
extern void dexterpicontroller(void);
extern void dynamic_power_2(void);
extern void dynamic_power_1(void);
extern int updateota(void);
extern void deviceidread();
extern void philiphsidread();
//extern void otamain(void);
/*
 *  ======== slTask ========
 */
void slTask(unsigned int arg0, unsigned int arg1)
{

    Task_Handle taskHandle;
    Task_Params taskParams;

// Clock ticks based
//Clock_Handle clk2;
//Clock_Params clkParams;
// End of clock ticks code


    /*
     *  Add the UART device to the system.
     *  All UART peripherals must be setup and the module must be initialized
     *  before opening.  This is done by Board_initUART().  The functions used
     *  are implemented in UARTUtils.c.
     */
    add_device("UART", _MSA, UARTUtils_deviceopen,
               UARTUtils_deviceclose, UARTUtils_deviceread,
               UARTUtils_devicewrite, UARTUtils_devicelseek,
               UARTUtils_deviceunlink, UARTUtils_devicerename);

    /* Open UART0 for writing to stdout and set buffer */
    freopen("UART:0", "w", stdout);
    setvbuf(stdout, NULL, _IOLBF, 128);

    /* Open UART0 for writing to stderr and set buffer */
    freopen("UART:0", "w", stderr);
    setvbuf(stderr, NULL, _IOLBF, 128);

    /* Open UART0 for reading from stdin and set buffer */
    freopen("UART:0", "r", stdin);
    setvbuf(stdin, NULL, _IOLBF, 128);

    /*
     *  Initialize UART port 0 used by SysCallback.  This and other SysCallback
     *  UART functions are implemented in UARTUtils.c. Calls to //System_printf
     *  will go to UART0, the same as printf.
     */
    UARTUtils_systemInit(0);

    /* Initialize SimpleLink */
    //deviceidread();
    NetWiFi_init();
    deviceidread();
    philiphsidread();

    int update;
    update = updateota();
    GPIOPinWrite(GPIOA3_BASE, 0x40, 0x40);
    if(!update){

    Task_Params_init(&taskParams);
    taskParams.stackSize = 4096;//1024;//4096;
    taskParams.priority = 3;
    taskHandle = Task_create((Task_FuncPtr)runAWSClient, &taskParams, NULL);
     if (taskHandle == NULL) {
        System_abort("runAWSClient: failed to create a Task!\n");
	}

    taskParams.priority = 3;
   taskHandle = Task_create((Task_FuncPtr)dexterpicontroller, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("runAWSClientpublish: failed to create a Task!\n");
	}

    taskParams.priority = 1;

    taskHandle = Task_create((Task_FuncPtr)vinayudp, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("udp: failed to create a Task!\n");
    }

   taskParams.priority = 1;

   taskHandle = Task_create((Task_FuncPtr)dynamic_power_1, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("runPowerStoring: failed to create a Task!\n");
	}
  /* taskParams.priority = 1;

taskHandle = Task_create((Task_FuncPtr)updateota, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("updateota: failed to create a Task!\n");
	}*/
/* Create a periodic Clock Instance with period = 5 system time units */
/*Clock_Params_init(&clkParams);
clkParams.period = 5;
clkParams.startFlag = TRUE;
clk2=Clock_create(dynamic_power_1, 5, &clkParams, NULL);*/
//Clock_start(clk2);

// End of clock ticks

 /*  taskHandle = Task_create((Task_FuncPtr)dynamic_power_2, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("runDynamicPowerDetect: failed to create a Task!\n");
	}
*/
    //runAWSClient();
//otamain();
}
}

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
    Task_Handle taskHandle;
    Task_Params taskParams;

    Board_initGeneral();
    Board_initGPIO();
    Board_initUART();
    Board_initWiFi();

    //GPIO_write(Board_LED0, Board_LED_ON);
    GPIOPinWrite(GPIOA3_BASE, 0x40, 0x40);

    Task_Params_init(&taskParams);
    taskParams.stackSize = 4096;//1024;

    taskHandle = Task_create((Task_FuncPtr)slTask, &taskParams, NULL);
    if (taskHandle == NULL) {
        System_abort("main: failed to create a Task!\n");
    }

    BIOS_start();
}

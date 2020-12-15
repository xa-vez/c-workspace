/*
 * FreeRTOS V202011.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/******************************************************************************
 * This project provides three demo applications.  A simple blinky style project,
 * a more comprehensive test and demo application, and a TCP echo demo.
 * The mainSELECTED_APPLICATION setting is used to select between
 * the three
 *
 * If mainSELECTED_APPLICATION = BLINKY_DEMO the simple blinky demo will be built.
 * The simply blinky demo is implemented and described in main_blinky.c.
 *
 * If mainSELECTED_APPLICATION = FULL_DEMO the more comprehensive test and demo
 * application built. This is implemented and described in main_full.c.
 *
 * If mainSELECTED_APPLICATION = ECHO_CLIENT_DEMO the tcp echo demo will be built.
 * This is implemented and described in main_networking.c
 *
 * This file implements the code that is not demo specific, including the
 * hardware setup and FreeRTOS hook functions.
 *
 *******************************************************************************
 * NOTE: Linux will not be running the FreeRTOS demo threads continuously, so
 * do not expect to get real time behaviour from the FreeRTOS Linux port, or
 * this demo application.  Also, the timing information in the FreeRTOS+Trace
 * logs have no meaningful units.  See the documentation page for the Linux
 * port for further information:
 * https://freertos.org/FreeRTOS-simulator-for-Linux.html
 *
 *******************************************************************************
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

/* Local includes. */
#include "console.h"

/*
 * Prototypes for the standard FreeRTOS application hook (callback) functions
 * implemented within this file.  See http://www.freertos.org/a00016.html .
 */
void vApplicationMallocFailedHook( void );
void vApplicationIdleHook( void );
void vApplicationTickHook( void );
void vApplicationDaemonTaskStartupHook( void );
void vAssertCalled( const char * const pcFileName, unsigned long ulLine );

/*!
 * @brief 
 *  
 */
void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created.  It is also called by various parts of the
    demo application.  If heap_1.c, heap_2.c or heap_4.c is being used, then the
    size of the    heap available to pvPortMalloc() is defined by
    configTOTAL_HEAP_SIZE in FreeRTOSConfig.h, and the xPortGetFreeHeapSize()
    API function can be used to query the size of free heap space that remains
    (although it does not provide information on how the remaining heap might be
    fragmented).  See http://www.freertos.org/a00111.html for more
    information. */
    vAssertCalled( __FILE__, __LINE__ );
}

/*!
 * @brief 
 *  
 */
void vApplicationIdleHook( void )
{
    /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
    to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
    task.  It is essential that code added to this hook function never attempts
    to block in any way (for example, call xQueueReceive() with a block time
    specified, or call vTaskDelay()).  If application tasks make use of the
    vTaskDelete() API function to delete themselves then it is also important
    that vApplicationIdleHook() is permitted to return to its calling function,
    because it is the responsibility of the idle task to clean up memory
    allocated by the kernel to any task that has since deleted itself. */    

    usleep(15000);
    //printf("Idle hook\n");
}

/*!
 * @brief 
 *  
 */
void vApplicationTickHook( void )
{
    /* This function will be called by each tick interrupt if
    configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
    added here, but the tick hook is called from an interrupt context, so
    code must not attempt to block, and only the interrupt safe FreeRTOS API
    functions can be used (those that end in FromISR()). */

    //printf("Tick hook\n");
}

/*!
 * @brief 
 *  
 */
void vApplicationDaemonTaskStartupHook( void )
{
    /* This function will be called once only, when the daemon task starts to
    execute    (sometimes called the timer task).  This is useful if the
    application includes initialisation code that would benefit from executing
    after the scheduler has been started. */
    printf("Daemon Startup Hook \n");
}

/*!
 * @brief 
 *  
 */
void vAssertCalled( const char * const pcFileName,
                    unsigned long ulLine )
{
    static BaseType_t xPrinted = pdFALSE;
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    /* Called if an assertion passed to configASSERT() fails.  See
    http://www.freertos.org/a00110.html#configASSERT for more information. */

    /* Parameters are not used. */
    ( void ) ulLine;
    ( void ) pcFileName;


    taskENTER_CRITICAL();
    {
        /* You can step out of this function to debug the assertion by using
        the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
        value. */
        while( ulSetToNonZeroInDebuggerToContinue == 0 )
        {
            __asm volatile ( "NOP" );
            __asm volatile ( "NOP" );
        }
    }
    taskEXIT_CRITICAL();
}


/*!
 * @brief 
 *  
 */
static void stats_task(void *pvParameters)
{
	const TickType_t sample_interval = 5000/portTICK_PERIOD_MS;

    char buffer[1024] = {0};

	for( ;; )
	{
		// Wait for the next cycle.
		vTaskDelay( sample_interval );

        printf( "Memory Available: %d/%d\n", xPortGetFreeHeapSize(), configTOTAL_HEAP_SIZE);

        vTaskList(&buffer);

        if (buffer) {
            printf("NAME         STATUS     PRIO    STACK   NBR\n");
            printf("%s\n", buffer);
        }
	}
}

/*!
 * @brief 
 *  
 */
static void hello_task(void *pvParameters)
{
	TickType_t last_wake_time;

	//Set tx interval to 1 sec
	const TickType_t sample_interval = 1000/portTICK_PERIOD_MS;

	// Initialize the last_wake_time variable with the current time
	last_wake_time = xTaskGetTickCount();

	for( ;; )
	{
		// Wait for the next cycle.
		vTaskDelayUntil( &last_wake_time, sample_interval );

        console_print("hello world !!!\n");	
	}
}

/*!
 * @brief 
 *  
 */
int main( void )
{
    printf ("\n\n");
    printf ("============================================\n");
    printf ("%s\n", __DATE__);
    printf ("============================================\n");

    // console initialization
    console_init();

    // create a task
	xTaskCreate(hello_task, "hello_task", configMINIMAL_STACK_SIZE + 10, NULL, configMAX_PRIORITIES-3, NULL);
    
    // create a task
    xTaskCreate(stats_task, "stats_task", configMINIMAL_STACK_SIZE + 10, NULL, 1, NULL); 

    // start scheduler
	vTaskStartScheduler();
	
    while(1);
		
    return 0;
}
/*-----------------------------------------------------------*/

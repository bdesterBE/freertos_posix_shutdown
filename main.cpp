/**
 * main.cpp
 *
 * @brief Test of the ability for a POSIX port freeRTOS program to exit
 * cleanly after ending the scheduler. Program should exit after call to
 * vTaskEndScheduler().
 *
 * @authors Brandon Dester, Chris Morgan
 *
*/

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include <thread>
#include <cstdio>
#include "task.h"
#include "unistd.h"

#define TASK_DEPTH 20000

static StackType_t task_stack [TASK_DEPTH];
static StaticTask_t task;

static bool running = true;

/* FreeRTOS required function stubs and implementations */
/*-----------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif
void vApplicationDaemonTaskStartupHook()
{
}

/* configUSE_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
 * application must provide an implementation of ()
 * to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t ** ppxTimerTaskTCBBuffer,
                                     StackType_t ** ppxTimerTaskStackBuffer,
                                     uint32_t * pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
	static StaticTask_t xTimerTaskTCB;
    static StackType_t uxIdleTaskStack[ 131072 * 2 ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
     * task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}
#ifdef __cplusplus
}
#endif

void vApplicationGetIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                    StackType_t ** ppxIdleTaskStackBuffer,
                                    uint32_t * pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
 * function then they must be declared static - otherwise they will be allocated on
 * the stack and so not exists after this function exits. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ 131072 * 2];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
     * state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
     * Note that, as the array is necessarily of type StackType_t,
     * configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/*-----------------------------------------------------------*/

void app_main(void* arg)
{
    // work performed here
    running = false;
    vTaskDelete(NULL); // queue itself for deletion by idle thread
}

int inner_main()
{
    xTaskCreateStatic(app_main, "app_main", TASK_DEPTH, (void*) 1,
                     1, task_stack, &task);

    vTaskStartScheduler();
    // should return here after ending the scheduler
    printf("After vTaskStartScheduler()\n");

    return 0;
}

int main()
{
    std::thread t1(inner_main);

    while(running)
    {
        usleep(1000);
    }

    printf("Before vTaskEndScheduler()\n");
    vTaskEndScheduler();
    printf("After vTaskEndScheduler()\n");

    return 0;
}

/*******************************************************************************
 * @file        os_freertos.c
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-08-01
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/
#include "os_freertos.h"
#include "FreeRTOS.h"
#include "drv_gpio.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "semphr.h"
#include "task.h"

/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/
#define STACK_SIZE 0x100

/******************************************************************************/
/* TYPEDEF                                                                    */
/******************************************************************************/

/******************************************************************************/
/* ENUM                                                                       */
/******************************************************************************/

/******************************************************************************/
/* STRUCTURE                                                                  */
/******************************************************************************/

/******************************************************************************/
/* UNION                                                                      */
/******************************************************************************/

/******************************************************************************/
/* LOCAL INLINE FUNCTION DECLARATION                                          */
/******************************************************************************/

/******************************************************************************/
/* LOCAL FUNCTION DECLARATION                                                 */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DECLARATION                                                */
/******************************************************************************/
static void s_led1_blink(void *param);
static void s_led2_blink(void *param);
static void s_cpu_timer1_isr_job();

/******************************************************************************/
/* LOCAL VARIABLE DEFINITION                                                  */
/******************************************************************************/
static StaticTask_t s_idle_task_buffer;
static StackType_t s_idle_task_stack[STACK_SIZE];
// #pragma DATA_SECTION(s_idle_task_buffer, ".freertosStaticStack")
// #pragma DATA_ALIGN(s_idle_task_stack, portBYTE_ALIGNMENT)

static StaticTask_t s_task1_buffer;
static StackType_t s_task1_stack[STACK_SIZE];

static StaticTask_t s_task2_buffer;
static StackType_t s_task2_stack[STACK_SIZE];

static SemaphoreHandle_t s_semaphore = NULL;
static StaticSemaphore_t s_semaphore_buffer;

/******************************************************************************/
/* GLOBAL VARIABLE DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/
void os_freertos_init() {
    s_semaphore = xSemaphoreCreateBinaryStatic(&s_semaphore_buffer);

    /** Setup timer1 interrupt */
    drv_timer_setup_cpu_timer1(&s_cpu_timer1_isr_job, 100000);

    /** Enable Global interrupt INTM */
    drv_mcu_ENABLE_GLOBAL_INTERRUPT();

    /** Enable Global realtime interrupt DBGM */
    drv_mcu_ENABLE_DEBUG_EVENT_INTERRUPT();

    xTaskCreateStatic(
        s_led2_blink,         /**< Function that implements the task. */
        "Led2BlinkTask",      /**< Text name for the task. */
        STACK_SIZE,           /**< Number of indexes in the xStack array. */
        NULL,                 /**< Parameter passed into the task. */
        tskIDLE_PRIORITY + 2, /**< Priority at which the task is created. */
        s_task2_stack,        /**< Array to use as the task's stack. */
        &s_task2_buffer /**< Variable to hold the task's data structure. */
    );

    xTaskCreateStatic(
        s_led1_blink,         /**< Function that implements the task. */
        "Led1BlinkTask",      /**< Text name for the task. */
        STACK_SIZE,           /**< Number of indexes in the xStack array. */
        NULL,                 /**< Parameter passed into the task. */
        tskIDLE_PRIORITY + 1, /**< Priority at which the task is created. */
        s_task1_stack,        /**< Array to use as the task's stack. */
        &s_task1_buffer /**< Variable to hold the task's data structure. */
    );
}

void os_freertos_main() {
    vTaskStartScheduler();
}

//------------------------------------------------------------------------------
// FreeRTOS user specified
//------------------------------------------------------------------------------
void vApplicationGetIdleTaskMemory(
    StaticTask_t **ppxIdleTaskTCBBuffer,
    StackType_t **ppxIdleTaskStackBuffer,
    configSTACK_DEPTH_TYPE *pulIdleTaskStackSize
) {
    *ppxIdleTaskTCBBuffer = &s_idle_task_buffer;
    *ppxIdleTaskStackBuffer = s_idle_task_stack;
    *pulIdleTaskStackSize = STACK_SIZE;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    while (1) {
    };
}

/******************************************************************************/
/* LOCAL FUNCTION DEFINITION                                                  */
/******************************************************************************/
static void s_cpu_timer1_isr_job() {
    BaseType_t higher_priority_task_woken = pdFALSE;
    xSemaphoreGiveFromISR(s_semaphore, &higher_priority_task_woken);
    portYIELD_FROM_ISR(higher_priority_task_woken);
}

static void s_led1_blink(void *param) {
    for (;;) {
        drv_gpio_turn_on_led(drv_gpio_PIN_LED1);
        vTaskDelay(500 / portTICK_PERIOD_MS); /** Delay 500 ms */
        drv_gpio_turn_off_led(drv_gpio_PIN_LED1);
        vTaskDelay(500 / portTICK_PERIOD_MS); /** Delay 500 ms */
    }
}

static void s_led2_blink(void *param) {
    static u8 cnt = 0;
    for (;;) {
        if (xSemaphoreTake(s_semaphore, portMAX_DELAY) == pdTRUE) {
            if (cnt == 0) {
                drv_gpio_turn_on_led(drv_gpio_PIN_LED2);
                cnt = 1;
            } else {
                drv_gpio_turn_off_led(drv_gpio_PIN_LED2);
                cnt = 0;
            }
        }
    }
}

/******************************************************************************/
/* LOCAL INLINE FUNCTION DEFINITION                                           */
/******************************************************************************/

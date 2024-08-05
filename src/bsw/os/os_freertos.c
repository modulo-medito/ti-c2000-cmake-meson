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
/* INCLUDE */
/******************************************************************************/
#include "os_freertos.h"
#include "FreeRTOS.h"
#include "drv_gpio.h"
#include "drv_mcu.h"
#include "drv_timer.h"
#include "semphr.h"
#include "task.h"

/******************************************************************************/
/* DEFINE */
/******************************************************************************/
#define STACK_SIZE 0x100

/******************************************************************************/
/* TYPEDEF */
/******************************************************************************/

/******************************************************************************/
/* ENUM */
/******************************************************************************/

/******************************************************************************/
/* STRUCTURE */
/******************************************************************************/

/******************************************************************************/
/* UNION */
/******************************************************************************/

/******************************************************************************/
/* LOCAL INLINE FUNCTION DECLARATION */
/******************************************************************************/

/******************************************************************************/
/* LOCAL FUNCTION DECLARATION */
/******************************************************************************/
void _led1_blink(void *param);
void _led2_blink(void *param);

/******************************************************************************/
/* GLOBAL FUNCTION DECLARATION */
/******************************************************************************/
static void _cpu_timer1_isr_job();

/******************************************************************************/
/* LOCAL VARIABLE DEFINITION */
/******************************************************************************/
static StaticTask_t _s_idle_task_buffer;
static StackType_t _s_idle_task_stack[STACK_SIZE];
// #pragma DATA_SECTION(_s_idle_task_buffer, ".freertosStaticStack")
// #pragma DATA_ALIGN(_s_idle_task_stack, portBYTE_ALIGNMENT)

static StaticTask_t _s_task1_buffer;
static StackType_t _s_task1_stack[STACK_SIZE];

static StaticTask_t _s_task2_buffer;
static StackType_t _s_task2_stack[STACK_SIZE];

static SemaphoreHandle_t _s_semaphore = NULL;
static StaticSemaphore_t _s_semaphore_buffer;

/******************************************************************************/
/* GLOBAL VARIABLE DEFINITION */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION */
/******************************************************************************/
void os_freertos__init() {
    _s_semaphore = xSemaphoreCreateBinaryStatic(&_s_semaphore_buffer);

    /** Setup timer1 interrupt */
    drv_timer__setup_cpu_timer1(&_cpu_timer1_isr_job, 100000);

    /** Enable Global interrupt INTM */
    drv_mcu_enable_global_interrupt();

    /** Enable Global realtime interrupt DBGM */
    drv_mcu_enable_debug_event_interrupt();

    xTaskCreateStatic(
        _led2_blink,          /**< Function that implements the task. */
        "Led2BlinkTask",      /**< Text name for the task. */
        STACK_SIZE,           /**< Number of indexes in the xStack array. */
        NULL,                 /**< Parameter passed into the task. */
        tskIDLE_PRIORITY + 2, /**< Priority at which the task is created. */
        _s_task2_stack,       /**< Array to use as the task's stack. */
        &_s_task2_buffer /**< Variable to hold the task's data structure. */
    );

    xTaskCreateStatic(
        _led1_blink,          /**< Function that implements the task. */
        "Led1BlinkTask",      /**< Text name for the task. */
        STACK_SIZE,           /**< Number of indexes in the xStack array. */
        NULL,                 /**< Parameter passed into the task. */
        tskIDLE_PRIORITY + 1, /**< Priority at which the task is created. */
        _s_task1_stack,       /**< Array to use as the task's stack. */
        &_s_task1_buffer /**< Variable to hold the task's data structure. */
    );
}

void os_freertos__main() {
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
    *ppxIdleTaskTCBBuffer = &_s_idle_task_buffer;
    *ppxIdleTaskStackBuffer = _s_idle_task_stack;
    *pulIdleTaskStackSize = STACK_SIZE;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    while (1) {
    };
}

/******************************************************************************/
/* LOCAL FUNCTION DEFINITION */
/******************************************************************************/
static void _cpu_timer1_isr_job() {
    BaseType_t higher_priority_task_woken = pdFALSE;
    xSemaphoreGiveFromISR(_s_semaphore, &higher_priority_task_woken);
    portYIELD_FROM_ISR(higher_priority_task_woken);
}

void _led1_blink(void *param) {
    for (;;) {
        drv_gpio__turn_on_led(drv_gpio__PIN_LED1);
        vTaskDelay(500 / portTICK_PERIOD_MS); /** Delay 500 ms */
        drv_gpio__turn_off_led(drv_gpio__PIN_LED1);
        vTaskDelay(500 / portTICK_PERIOD_MS); /** Delay 500 ms */
    }
}

void _led2_blink(void *param) {
    static u8 cnt = 0;
    for (;;) {
        if (xSemaphoreTake(_s_semaphore, portMAX_DELAY) == pdTRUE) {
            if (cnt == 0) {
                drv_gpio__turn_on_led(drv_gpio__PIN_LED2);
                cnt = 1;
            } else {
                drv_gpio__turn_off_led(drv_gpio__PIN_LED2);
                cnt = 0;
            }
        }
    }
}

/******************************************************************************/
/* LOCAL INLINE FUNCTION DEFINITION */
/******************************************************************************/

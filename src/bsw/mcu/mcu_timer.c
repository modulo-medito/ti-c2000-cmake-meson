/*******************************************************************************
 * @file        mcu_timer.c
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-31
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/
#include "mcu_timer.h"

/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/

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

/******************************************************************************/
/* LOCAL VARIABLE DEFINITION                                                  */
/******************************************************************************/
static void s_config_cputimer_period_us(u32 timer, u32 period_us);

/******************************************************************************/
/* GLOBAL VARIABLE DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/
void mcu_timer_init_timer_with_period_us(u32 timer, u32 period_us) {
    CPUTimer_setPeriod(timer, 0xffffffff);
    CPUTimer_setPreScaler(timer, 0);
    CPUTimer_stopTimer(timer);
    CPUTimer_reloadTimerCounter(timer);
    s_config_cputimer_period_us(timer, period_us);
}

/******************************************************************************/
/* LOCAL FUNCTION DEFINITION                                                  */
/******************************************************************************/
/**
 * This function initializes the selected timer to the period specified by the
 * "freq" and "period" variables. The "freq" is CPU frequency in Hz and the
 * period in uSeconds. The timer is held in the stopped state after
 * configuration
 */
static void s_config_cputimer_period_us(u32 timer, u32 period_us) {
    u32 temp;
    u32 freq = DEVICE_SYSCLK_FREQ;

    /** Initialize timer period */
    /** (DEVICE_SYSCLK_FREQ / 1000000) = ticks per us */
    temp = ((freq / 1000000) * period_us);
    CPUTimer_setPeriod(timer, temp);

    /** Set pre-scale counter to divide by 1 (SYSCLKOUT): */
    CPUTimer_setPreScaler(timer, 0);

    /**
     * Initializes timer control register.
     * The timer is stopped, reloaded, free run disabled, and interrupt enabled.
     * Additionally, the free and soft bits are set.
     */
    CPUTimer_stopTimer(timer);
    CPUTimer_reloadTimerCounter(timer);
    CPUTimer_setEmulationMode(
        timer, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT
    );
}

/******************************************************************************/
/* LOCAL INLINE FUNCTION DEFINITION                                           */
/******************************************************************************/

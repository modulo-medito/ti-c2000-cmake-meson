/*******************************************************************************
 * @file        mcu_timer.h
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-31
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
#ifndef __MCU_TIMER_H__
#define __MCU_TIMER_H__
/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/
#include "mcu_dependency.h"

/******************************************************************************/
/* TYPEDEF                                                                    */
/******************************************************************************/

/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/
#define mcu_timer_CPUTIMER1 (CPUTIMER1_BASE)
#define mcu_timer_CPUTIMER2 (CPUTIMER2_BASE)

#define mcu_timer_ENABLE_TIMER_INTERRUPT(timer)                                \
    do {                                                                       \
        CPUTimer_enableInterrupt(timer);                                       \
    } while (0)

#define mcu_timer_START_TIMER(timer)                                           \
    do {                                                                       \
        CPUTimer_startTimer(timer);                                            \
    } while (0)

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
/* GLOBAL VARIABLE DECLARATION                                                */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DECLARATION                                                */
/******************************************************************************/
extern void mcu_timer_init_timer_with_period_us(u32 timer, u32 period_us);

/******************************************************************************/
/* GLOBAL INLINE FUNCTION DEFINITION                                          */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif /* __MCU_TIMER_H__ */

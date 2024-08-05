/*******************************************************************************
 * @file        mcu_sys.h
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-31
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
#ifndef __MCU_SYS_H__
#define __MCU_SYS_H__
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
#define mcu_ctl__clear_interrupt_indication_flags()                            \
    do {                                                                       \
        IFR = 0x0000;                                                          \
    } while (0)

#define mcu_ctl__clear_interrupt_enable_flags()                                \
    do {                                                                       \
        IER = 0x0000;                                                          \
    } while (0)

#define mcu_ctl__interrupt_disable()                                           \
    do {                                                                       \
        DINT;                                                                  \
    } while (0)

#define mcu_ctl__interrupt_enable()                                            \
    do {                                                                       \
        EINT;                                                                  \
    } while (0)

#define mcu_ctl__debug_event_enable()                                          \
    do {                                                                       \
        ERTM;                                                                  \
    } while (0)

#define mcu_ctl__delay_us(val)                                                 \
    do {                                                                       \
        DEVICE_DELAY_US(val);                                                  \
    } while (0)

#define mcu_ctl__feed_watchdog()                                               \
    do {                                                                       \
        SysCtl_serviceWatchdog();                                              \
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

/******************************************************************************/
/* GLOBAL INLINE FUNCTION DEFINITION                                          */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif /* __MCU_SYS_H__ */

/*******************************************************************************
 * @file        drv_int.h
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-31
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
#ifndef __DRV_INT_H__
#define __DRV_INT_H__
/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/
#include "mcu.h"
#include "typedef.h"

/******************************************************************************/
/* TYPEDEF                                                                    */
/******************************************************************************/

/******************************************************************************/
/* DEFINE                                                                     */
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
/* GLOBAL VARIABLE DECLARATION                                                */
/******************************************************************************/

/******************************************************************************/
/* GLOBAL FUNCTION DECLARATION                                                */
/******************************************************************************/
extern void drv_int_regist_isr_timer1(void (*isr)(void));
extern void drv_int_enable_isr_timer1();
extern void drv_int_regist_isr_timer2(void (*isr)(void));
extern void drv_int_enable_isr_timer2();

/******************************************************************************/
/* GLOBAL INLINE FUNCTION DEFINITION                                          */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif /* __DRV_INT_H__ */

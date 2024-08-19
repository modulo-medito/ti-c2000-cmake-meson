/*******************************************************************************
 * @file        drv_gpio.h
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-25
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__
/******************************************************************************/
/* INCLUDE                                                                    */
/******************************************************************************/
#include "mcu_gpio.h"
#include "typedef.h"

/******************************************************************************/
/* TYPEDEF                                                                    */
/******************************************************************************/

/******************************************************************************/
/* DEFINE                                                                     */
/******************************************************************************/
#define drv_gpio_PIN_LED1 (mcu_gpio_PIN_LED1)
#define drv_gpio_PIN_LED2 (mcu_gpio_PIN_LED2)

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
extern void drv_gpio_init();
extern void drv_gpio_turn_on_led(u8 gpio_num);
extern void drv_gpio_turn_off_led(u8 gpio_num);

/******************************************************************************/
/* GLOBAL INLINE FUNCTION DEFINITION                                          */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
#endif /* __DRV_GPIO_H__ */

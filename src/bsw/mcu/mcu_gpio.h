/*******************************************************************************
 * @file        mcu_gpio.h
 * @author      Modulo Medito (chcchc1995@outlook.com)
 * @brief
 *
 * @version     0.0.1
 * @date        2024-07-31
 * @copyright   Copyright (C) 2024. All rights reserved.
 ******************************************************************************/
#ifndef __MCU_GPIO_H__
#define __MCU_GPIO_H__
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
#define mcu_gpio_PIN_LED1 (DEVICE_GPIO_PIN_LED1)
#define mcu_gpio_PIN_LED2 (DEVICE_GPIO_PIN_LED2)

#define mcu_gpio_WRITE_PIN(pin, val)                                           \
    do {                                                                       \
        GPIO_writePin(pin, val);                                               \
    } while (0)

#define mcu_gpio_SET_PIN_DIR_OUT(pin)                                          \
    do {                                                                       \
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_OUT);                         \
    } while (0)

#define mcu_gpio_SET_PIN_DIR_IN(pin)                                           \
    do {                                                                       \
        GPIO_setDirectionMode(pin, GPIO_DIR_MODE_IN);                          \
    } while (0)

/** Push-pull output or floating input */
#define mcu_gpio_SET_PIN_TYPE_STD(pin)                                         \
    do {                                                                       \
        GPIO_setPadConfig(pin, GPIO_PIN_TYPE_STD);                             \
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
#endif /* __MCU_GPIO_H__ */

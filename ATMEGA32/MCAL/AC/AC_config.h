/****************************************************************************
 * @file    AC_config.h
 * @author  Boles Medhat
 * @brief   Analog Comparator (AC) Configuration Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration macros for the Analog Comparator (AC)
 * driver for ATmega32 microcontroller. It allows for customizing the interrupt
 * trigger mode, interrupt enable/disable, and input capture functionality.
 *
 * @note
 * - All available choices (e.g., trigger mode, interrupt enable/disable) are
 *   defined in `AC_def.h` and explained with comments there.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef AC_CONFIG_H_
#define AC_CONFIG_H_

#include "AC_def.h"


/*Set Analog Comparator Interrupt Trigger Event
 * choose between:
 * 1. AC_INT_ON_TOGGLE
 * 2. AC_INT_ON_FALLING
 * 3. AC_INT_ON_RISING
 */
#define AC_INT_MODE							AC_INT_ON_TOGGLE


/*Set Analog Comparator Interrupt Status
 * choose between:
 * 1. AC_INT_DISABLE
 * 2. AC_INT_ENABLE
 */
#define AC_INT_STATUS						AC_INT_DISABLE


/*Set Analog Comparator Input Capture Enable
 * choose between:
 * 1. AC_TRIGGER_ICU_DISABLE		<--the most used
 * 2. AC_TRIGGER_ICU_ENABLE
 */
#define AC_TRIGGER_ICU_STATUS				AC_TRIGGER_ICU_DISABLE


#endif /* AC_CONFIG_H_ */

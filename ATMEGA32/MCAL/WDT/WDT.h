/******************************************************************************
 * @file    WDT.h
 * @author  Boles Medhat
 * @brief   Watchdog Timer Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This header provides the function prototypes for managing the Watchdog Timer
 * (WDT) in the ATmega32 microcontroller. It allows software to enable or
 * disable the WDT and trigger a system reset using the WDT.
 *
 * The Watchdog Timer driver includes the following functionalities:
 * - Enable the WDT with selectable timeout durations.
 * - Disable the WDT to prevent unwanted resets.
 * - Force a microcontroller reset by using the shortest timeout setting.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef WDT_H_
#define WDT_H_

#include "../../LIB/BIT_MATH.h"
#include "WDT_def.h"


/*
 * @brief Enables the Watchdog Timer (WDT) with a specified timeout period.
 *
 * This function starts the Watchdog Timer countdown using the selected timeout.
 * If the timer is not reset before it expires, the microcontroller will perform a system reset.
 *
 * @param time_out: Timeout period for the Watchdog Timer. Must be one of the following predefined values:
 *                     - WDT_TIME_OUT_16ms
 *                     - WDT_TIME_OUT_32ms
 *                     - WDT_TIME_OUT_65ms
 *                     - WDT_TIME_OUT_130ms
 *                     - WDT_TIME_OUT_260ms
 *                     - WDT_TIME_OUT_520ms
 *                     - WDT_TIME_OUT_1000ms
 *                     - WDT_TIME_OUT_2100ms
 */
void WDT_Enable( uint8 time_out );


/*
 * @brief Disables the Watchdog Timer (WDT).
 *
 * This function stops the countdown of the Watchdog Timer, preventing a reset from occurring.
 */
void WDT_Disable();


/*
 * @brief Resets the microcontroller using the Watchdog Timer.
 *
 * This function forces a reset by configuring the Watchdog Timer with the shortest timeout (16ms)
 * and enabling it. The MCU will then enter an infinite loop, causing the WDT to reset the MCU.
 */
void WDT_RESET_MCU();


#endif /* WDT_H_ */

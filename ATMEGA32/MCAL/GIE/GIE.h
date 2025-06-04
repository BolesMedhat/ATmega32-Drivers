/****************************************************************************
 * @file    GIE.h
 * @author  Boles Medhat
 * @brief   Global Interrupt Enable Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This source file implements functions for enabling and disabling the global
 * interrupt system in AVR microcontrollers using the Status Register (SREG).
 *
 * The GIE module includes the following functionalities:
 * - `GIE_Enable()` to set the global interrupt enable bit.
 * - `GIE_Disable()` to clear the global interrupt enable bit.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Global interrupts should only be enabled after configuring the desired
 *   peripheral interrupt sources.
 * - Disabling global interrupts does not affect the individual interrupt flags.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef GIE_H_
#define GIE_H_

#include "../../LIB/BIT_MATH.h"
#include "GIE_def.h"


/*
 * @brief Enables global interrupts.
 *
 * This function sets the global interrupt enable bit (I-bit) in the Status Register (SREG),
 * allowing the microcontroller to respond to enabled peripheral interrupts.
 *
 * @note Should be called after configuring and enabling the specific peripheral interrupt sources.
 */
void GIE_Enable( void );


/*
 * @brief Disables global interrupts.
 *
 * This function clears the global interrupt enable bit (I-bit) in the Status Register (SREG),
 * preventing the microcontroller from responding to any interrupts.
 *
 * @note Disabling global interrupts does not clear or disable individual peripheral interrupt flags.
 */
void GIE_Disable( void );


#endif /* GIE_H_ */

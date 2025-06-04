/****************************************************************************
 * @file    AC.h
 * @author  Boles Medhat
 * @brief   Analog Comparator (AC) Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file implements the functions for controlling the Analog Comparator
 * (AC) module in the ATmega32 microcontroller. It provides functions for
 * initialization, input source selection, interrupt control, and setting
 * callback functions for interrupt handling.
 *
 * The AC driver includes the following functionalities:
 * - Initialization and configuration using compile-time macros.
 * - Runtime control of positive/negative input source.
 * - Trigger mode selection (toggle, rising, falling).
 * - Reading comparator output state.
 * - Interrupt management (enable/disable/change trigger).
 * - Callback registration for ISR handling.
 *
 * @note
 * - Requires `AC_config.h` for macro-based configuration.
 * - Disabling the ADC module is required when using ADCx inputs as negative input.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef AC_H_
#define AC_H_

#include "../../LIB/BIT_MATH.h"
#include "AC_config.h"


/*
 * @brief Initialize the Analog Comparator based on configuration options.
 *
 * This function configures the interrupt mode, trigger source for ICU, input source, and enables
 * the Analog Comparator.
 * It configures the Analog Comparator registers according to the defined macros in `AC_config.h`.
 *
 * @see `AC_config.h` for configuration options.
 */
void AC_Init( void );


/*
 * @brief Get the output state of the Analog Comparator.
 *
 * This function checks the output of the Analog Comparator (ACO flag), which indicates whether
 * the positive input is greater than the negative input.
 *
 * @return (uint8) The output of the Analog Comparator.
 *               - Returns 1 if the positive input is greater than the negative input.
 *               - Returns 0 if the negative input is greater or equal to the positive input.
 */
uint8 AC_GetOutput( void );


/*
 * @brief Change the negative input source of the Analog Comparator.
 *
 * This function selects the negative input from various sources, including AIN1 or any of the ADC channels.
 *
 * @param Negative_Input: One of [AC_AIN1, AC_ADC0 ... AC_ADC7].
 *
 * @warning Choosing any ADC channel (AC_ADC0 ... AC_ADC7) will disable the ADC module.
 * @note If AC_AIN1 is selected, the ADC module will not be disabled.
 */
void AC_ChangeNegativeInput( uint8 Negative_Input );


/*
 * @brief Change the positive input source of the Analog Comparator.
 *
 * This function selects the positive input for the Analog Comparator from
 * AIN0 or the internal bandgap voltage (AC_BG).
 *
 * @param Positive_Input: One of [AC_AIN0, AC_BG].
 */
void AC_ChangePositiveInput( uint8 Positive_Input );


/*
 * @brief Change the interrupt trigger condition for the Analog Comparator.
 *
 * This function configures the event that triggers the Analog Comparator interrupt. The interrupt can
 * be triggered by a toggle of the output, a rising edge, or a falling edge.
 *
 * @param mode The desired trigger mode. It can be one of the following:
 *        - AC_INT_ON_TOGGLE: Trigger interrupt on output toggle.
 *        - AC_INT_ON_FALLING: Trigger interrupt on falling output edge.
 *        - AC_INT_ON_RISING: Trigger interrupt on rising output edge.
 */
void AC_ChangeTriggerEvent( uint8 mode );


/*
 * @brief Enable Analog Comparator interrupt.
 *
 * This function enables the interrupt for the Analog Comparator. The interrupt will be triggered based
 * on the configured trigger mode (toggle, rising, or falling edge).
 */
void AC_InterruptEnable( void );


/*
 * @brief Disable Analog Comparator interrupt.
 *
 * This function disables the interrupt for the Analog Comparator.
 */
void AC_InterruptDisable( void );


/*
 * @brief Sets the callback function for the Analog Comparator interrupt.
 *
 * This function registers a callback function that will be executed when the Analog Comparator interrupt
 * occurs.
 *
 * @example
 * void AC_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * AC_SetCallback( AC_InterruptHandler );
 *
 * @param CopyFuncPtr: Pointer to the callback function. The function should have a void return type and no parameters.
 */
void AC_SetCallback( void (*CopyFuncPtr)(void) );

#endif /* AC_H_ */

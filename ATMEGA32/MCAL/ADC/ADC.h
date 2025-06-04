/****************************************************************************
 * @file    ADC.h
 * @author  Boles Medhat
 * @brief   ADC Driver Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-16]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides an abstraction layer for the Analog-to-Digital Converter (ADC)
 * in the ATmega32 microcontroller. It supports both 8-bit and 10-bit resolutions,
 * single and auto trigger conversion modes, interrupt handling, and callback registration.
 *
 * The ADC driver includes the following functionalities:
 * - Initialization based on voltage reference, prescaler, mode, and interrupt config.
 * - Start conversion without blocking and read results separately.
 * - Combined start-and-read functions for both 8-bit and 10-bit modes.
 * - Auto trigger and interrupt enable/disable control.
 * - User-defined callback registration with result pointer linkage.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `ADC_config.h` for macro-based configuration.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../../LIB/BIT_MATH.h"
#include "ADC_config.h"


/*
 * @brief Initializes the ADC based on configuration options.
 *
 * This function sets up the ADC voltage reference, adjustment mode,
 * prescaler, ADC mode (auto trigger or single conversion), and interrupt status.
 * It configures the ADC registers according to the defined macros in `ADC_config.h`.
 *
 * @see `ADC_config.h` for configuration options.
 */
void ADC_Init( void );


/*
 * @brief Starts the ADC conversion for the specified channel without reading the result.
 *
 * This function initiates the conversion process for the given ADC channel.
 * It does not wait for the conversion to complete.
 * The result can be read later using the appropriate read function ( uint16 ADC_OnlyRead( void ) ).
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 */
void ADC_OnlyStartConversion( uint8 ADC_channel );


/*
 * @brief Reads the ADC result without starting a new conversion.
 *
 * This function returns the ADC result without starting a new conversion.
 * The ADC conversion must be completed before calling this function.
 * It checks for a timeout condition if specified and returns 0 in case of a timeout.
 *
 * @return: The ADC result. The return value depends on the adjustment mode (10-bit or 8-bit).
 */
uint16 ADC_OnlyRead( void );


/*
 * @brief Starts an ADC conversion and returns the 10-bit result.
 *
 * This function starts a conversion for the specified ADC channel and waits for the result to be ready.
 * It returns the result as a 10-bit value.
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 *
 * @return: The 10-bit ADC result.
 */
uint16 ADC_Read_10_Bits( uint8 ADC_channel );


/*
 * @brief Starts an ADC conversion and returns the 8-bit result.
 *
 * This function starts a conversion for the specified ADC channel and waits for the result to be ready.
 * It returns the result as an 8-bit value.
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 *
 * @return: The 8-bit ADC result.
 */
uint8 ADC_Read_8_Bits( uint8 ADC_channel );


/*
 * @brief Enables the ADC.
 *
 * This function enables the ADC by setting the ADEN bit in the ADCSRA register.
 */
void ADC_Enable( void );


/*
 * @brief Disables the ADC.
 *
 * This function disables the ADC by clearing the ADEN bit in the ADCSRA register.
 */
void ADC_Disable( void );


/*
 * @brief Enables ADC Auto Triggering.
 *
 * This function enables ADC auto triggering by setting the appropriate bits in the ADCSRA and SFIOR registers.
 */
void ADC_AutoTriggerEnable( void );


/*
 * @brief Disables ADC Auto Triggering.
 *
 * This function disables ADC auto triggering by clearing the ADATE bit in the ADCSRA register.
 */
void ADC_AutoTriggerDisable( void );


/*
 * @brief Enables ADC Interrupt.
 *
 * This function enables the ADC interrupt by setting the ADIE bit in the ADCSRA register.
 */
void ADC_InterruptEnable( void );


/*
 * @brief Disables ADC Interrupt.
 *
 * This function disables the ADC interrupt by clearing the ADIE bit in the ADCSRA register.
 */
void ADC_InterruptDisable( void );


/*
 * @brief Sets the callback function for the ADC interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the ADC conversion completes (interrupt-based).
 * The ADC result (10-bit) is passed as a parameter to the callback function.
 *
 * @example
 * void ADC_InterruptHandler(uint16 result)
 * {
 *     // Process ADC result
 * }
 * ...
 * ADC_SetCallback( ADC_InterruptHandler );
 *
 * @param CopyFuncPtr Pointer to the callback function.
 *        The function must have a uint16 parameter and void return type.
 */
void ADC_SetCallback( void (*CopyFuncPtr)(uint16) );


#endif /* ADC_H_ */

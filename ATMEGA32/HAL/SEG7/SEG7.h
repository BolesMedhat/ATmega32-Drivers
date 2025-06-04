/****************************************************************************
 * @file    SEG7.h
 * @author  Boles Medhat
 * @brief   7-Segment Display Driver Header File
 * @version 2.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides complete control for 7-segment displays.
 * It supports both single-digit and multiplexed multi-digit displays,
 * as well as dot LED control.
 *
 * The SEG7 driver includes the following functionalities:
 * - Initialization of segment and control pins.
 * - Display of individual digits (0–9).
 * - Multiplexed display of multi-digit numbers.
 * - Dot LED control (enable/disable).
 * - Segment disabling for power-saving or blanking.
 *
 * @note
 * - Requires `SEG7_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SEG7_H_
#define SEG7_H_

#include "../../LIB/STD_TYPES.h"
#include "../SEG7/SEG7_config.h"
#include <util/delay.h>


/*
 * @brief Initializes the specified 7-segment port as output.
 *
 * This function sets the direction of all pins in the specified port as output
 * to be used with a 7-segment display.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_Init( uint8 seg7_port );


/*
 * @brief Initializes the pins required for a multiplexed 7-segment display.
 *
 * This function sets the direction of all digit control pins and the segment data port
 * to output mode, preparing the 7-segment display for multiplexed operation.
 *
 * It ensures that the control pins (used to enable each digit) stay within the valid
 * pin range (0 to 7) before proceeding.
 *
 * @param segments   A structure of type `Seg7` containing:
 *              	 - DataPort:	   Port connected to segment data lines (A to G, DP)
 *      	         - EnablePort:	   Port connected to digit control pins
 *          	     - FirstEnablePin: The first digit control pin (0–7)
 *              	 - DigitsNum:	   Number of digits used in the display
 */
void SEG7_Multiplex_Init( Seg7 segments );


/*
 * @brief Displays the specified digit on the 7-segment display.
 *
 * This function turns on the appropriate segments to show the digit from 0 to 9.
 *
 * @param Digit: Digit to display (0 to 9).
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_DisplayDigit( uint8 seg7_port , uint8 Digit );


/*
 * @brief Displays a multi-digit number using multiplexing on a 7-segment display.
 *
 * This function takes a `SEG7` configuration structure and a number to be displayed.
 * It loops through the digits of the number, enables each corresponding digit control pin,
 * and sets the appropriate segment values for display. The multiplexing technique is used
 * to display each digit sequentially for a short time, creating the appearance of a stable display.
 *
 * @param segments   A structure of type `Seg7` containing:
 *              	 - DataPort:	   Port connected to segment data lines (A to G, DP)
 *      	         - EnablePort:	   Port connected to digit control pins
 *          	     - FirstEnablePin: The first digit control pin (0–7)
 *              	 - DigitsNum:	   Number of digits used in the display
 *
 * @param number: The numeric value to be displayed (e.g., 0–65535 depending on DigitsNum).
 */
void SEG7_Multiplex_Display( Seg7 segments , uint16 number );


/*
 * @brief Turns off all segments (LEDs) in the specified 7-segment display.
 *
 * This function clears the port to disable the entire 7-segment display.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_Disable( uint8 seg7_port );


/*
 * @brief Disables the dot LED in the specified 7-segment display.
 *
 * This function turns off the decimal point/dot LED segment.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_DisableDot( uint8 seg7_port );


/*
 * @brief Enables the dot LED in the specified 7-segment display.
 *
 * This function turns on the decimal point/dot LED segment.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_EnableDot( uint8 seg7_port );


#endif /* SEG7_H_ */

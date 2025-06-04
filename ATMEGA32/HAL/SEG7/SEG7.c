/****************************************************************************
 * @file    SEG7.c
 * @author  Boles Medhat
 * @brief   7-Segment Display Driver Source File
 * @version 2.0
 * @date    [2024-09-4]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides complete control for 7-segment displays.
 * It supports both single-digit and multiplexed multi-digit displays,
 * as well as dot LED control.
 *
 * @note
 * - Requires `SEG7_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/


#include "../SEG7/SEG7.h"

/* Array for Digit Patterns on a 7-Segment Display */
static const uint8 SEG7_DigitArray[10] = SEG7_ARRAY;





/*
 * @brief Initializes the specified 7-segment port as output.
 *
 * This function sets the direction of all pins in the specified port as output
 * to be used with a 7-segment display.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_Init( uint8 seg7_port )
{
	/* Initialization the Specified 7-Segment Port Direction */
	DIO_SetPortDirection( seg7_port , OUTPUT_PORT );
}





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
void SEG7_Multiplex_Init( Seg7 segments )
{

	/* Check if the Last Control Pin Stays within Valid 0–7 pin Range */
	if ( ( segments.FirstEnablePin + segments.DigitsNum - 1 ) <= 7 )
	{
		/* Loop on Control Pins to Initialize each Control Pin */
		/* From First Pin (first_control_pin) to Last Pin (first_control_pin + seg7_digits_num - 1)*/
		for(uint8 pin = segments.FirstEnablePin ; pin < segments.FirstEnablePin + segments.DigitsNum  ; pin++)
		{
			/* Initialize the Control Pin Direction as Output */
			DIO_SetPinDirection( segments.EnablePort , pin , OUTPUT );
		}

		/* Initialization the Specified 7-Segment Port Direction */
		DIO_SetPortDirection( segments.DataPort , OUTPUT_PORT );
	}
}





/*
 * @brief Displays the specified digit on the 7-segment display.
 *
 * This function turns on the appropriate segments to show the digit from 0 to 9.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 * @param Digit: Digit to display (0 to 9).
 */
void SEG7_DisplayDigit( uint8 seg7_port , uint8 Digit )
{

	/* Check that the Digit is in the Range of the Array */
	if(Digit < 10)
	{
		/* Display Specified Digit on the Specified 7-Segment Port */
		DIO_SetPortValue( seg7_port , SEG7_DigitArray[ Digit ] );
	}
}





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
 * @param number: The numeric value to be displayed (e.g., 0–65536 depending on DigitsNum).
 */
void SEG7_Multiplex_Display( Seg7 segments , uint16 number )
{
	/* Check if the Last Control Pin Stays within Valid 0–7 pin Range */
	if ( ( segments.FirstEnablePin + segments.DigitsNum - 1 ) <= 7 )
	{
		/* Loop on Control Pins to Clear each Control Pin */
		/* From First Pin (first_control_pin) to Last Pin (first_control_pin + seg7_digits_num - 1)*/
		for(uint8 pin = segments.FirstEnablePin ; pin < segments.FirstEnablePin + segments.DigitsNum  ; pin++)
		{
			/* Initialize the Control Pin Direction as Output */
			DIO_SetPinValue( segments.EnablePort , pin , LOW );
		}


		/* Loop on each Digit */
		for(sint8 pin = segments.FirstEnablePin + segments.DigitsNum - 1 ; pin >= segments.FirstEnablePin ; pin--)
		{

			/* Display Specified Digit on the Specified 7-Segment Port */
			DIO_SetPortValue( segments.DataPort , SEG7_DigitArray[ number % 10 ] );

			/* To go to Next Digit */
			number /= 10;

			/* Enable the Digit */
			DIO_SetPinValue( segments.EnablePort , pin , SEG7_PIN_ENABLE );

			/* Delay for Persistence */
			_delay_ms( SEG7_MULTIPLEX_DELAY );

			/* Disable the Digit */
			DIO_SetPinValue( segments.EnablePort , pin , SEG7_PIN_DISABLE );

		}
	}
}





/*
 * @brief Turns off all segments (LEDs) in the specified 7-segment display.
 *
 * This function clears the port to disable the entire 7-segment display.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_Disable( uint8 seg7_port )
{
	/* Turns off All the Segments(LEDS) in the Specified 7-Segment Port */
	DIO_SetPortValue( seg7_port , SEG7_DISABLE_msk );
}





/*
 * @brief Disables the dot LED in the specified 7-segment display.
 *
 * This function turns off the decimal point/dot LED segment.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_DisableDot( uint8 seg7_port )
{
	/* Disable the Dot LED in the Specified 7-Segment Port */
	DIO_SetPinValue( seg7_port , SEG7_DOT_PIN , !SEG7_PIN_DISABLE );
}





/*
 * @brief Enables the dot LED in the specified 7-segment display.
 *
 * This function turns on the decimal point/dot LED segment.
 *
 * @param seg7_port: Port connected to the 7-segment display.
 *                        Use one of: DIO_PORTA, DIO_PORTB, DIO_PORTC, DIO_PORTD.
 */
void SEG7_EnableDot( uint8 seg7_port )
{
	/* Enable the Dot LED in the Specified 7-Segment Port */
	DIO_SetPinValue( seg7_port , SEG7_DOT_PIN , !SEG7_PIN_ENABLE );
}





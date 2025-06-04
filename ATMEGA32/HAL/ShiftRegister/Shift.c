/****************************************************************************
 * @file	Shift.c
 * @author  Boles Medhat
 * @brief   Shift Register Driver Source File
 * @version 1.0
 * @date	[2024-09-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file demonstrates the use of shift register driver functions with:
 * - 74HC595: Serial to Parallel (Shift-Out)
 * - 74HC165: Parallel to Serial (Shift-In)
 *
 * @note
 * - Requires `Shift_config.h` for macro-based configuration.
 *
 * @example for two 74HC595 (Shift-Out):
 * 		SHIFT_OUT_Init();
 * 		SHIFT_OUT_Byte( 0xAA );
 * 		SHIFT_OUT_Byte( 0x55 );
 * 		SHIFT_OUT_Latch();
 *
 * @example for two 74HC165 (Shift-In):
 *		SHIFT_IN_Init();
 * 		SHIFT_IN_Latch();
 * 		uint8 high_byte = SHIFT_IN_Byte();
 * 		uint8 low_byte = SHIFT_IN_Byte();
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "Shift.h"





/*
 * @brief Initializes the pins for shifting data out to the shift register.
 *
 * This function configures the clock, load, and data pins for the shift-out
 * operations. All pins are set to low initially.
 */
void SHIFT_OUT_Init(void)
{
	/* Set the Pins Direction as Output */
	DIO_SetPinDirection(SHIFT_OUT_PORT, SHIFT_OUT_CLOCK_PIN, OUTPUT);
	DIO_SetPinDirection(SHIFT_OUT_PORT, SHIFT_OUT_LOAD_PIN, OUTPUT);
	DIO_SetPinDirection(SHIFT_OUT_PORT, SHIFT_OUT_DATA_PIN, OUTPUT);

	/* set the Pins as Low Value */
	DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_CLOCK_PIN, LOW);
	DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_LOAD_PIN, LOW);
	DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_DATA_PIN, LOW);
}





/*
 * @brief Initializes the pins for shifting data in from the shift register.
 *
 * This function configures the clock, load, and data pins for the shift-in
 * operations. The data pin is configured as an input, while the clock and load
 * pins are configured as outputs. All pins are set to low initially.
 */
void SHIFT_IN_Init(void)
{
	/* Set the Pins Direction as Output */
	DIO_SetPinDirection(SHIFT_IN_PORT, SHIFT_IN_CLOCK_PIN, OUTPUT);
	DIO_SetPinDirection(SHIFT_IN_PORT, SHIFT_IN_LOAD_PIN, OUTPUT);

	/* Set the Pin Direction as Input */
	DIO_SetPinDirection(SHIFT_IN_PORT, SHIFT_IN_DATA_PIN, INPUT);

	/* set the Pins as Low Value */
	DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_CLOCK_PIN, LOW);
	DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_LOAD_PIN, LOW);
}





/*
 * @brief Sends one byte of data to the shift register.
 *
 * This function shifts out one byte of data to the shift register, sending
 * one bit at a time in the specified bit order (LSBFIRST or MSBFIRST).
 *
 * @param data: The byte of data to be sent to the shift register.
 */
void SHIFT_OUT_Byte(uint8 data)
{

	/* Loop through each bit in the byte */
	for (uint8 bit_num = 0; bit_num < 8; bit_num++)
	{

		/* Shift out based on configured bit order */
		#if   SHIFT_ORDER == SHIFT_LSB_FIRST

			/* Write the Shifted-out bit (least significant bit first) */
			DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_DATA_PIN, GET_BIT(data, 0));

			/* Get the next bit */
			data >>= 1;

		#elif SHIFT_ORDER == SHIFT_MSB_FIRST

			/* Write the Shifted-out bit (most significant bit first) */
			DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_DATA_PIN, GET_BIT(data, 7));

			/* Get the next bit */
			data <<= 1;
		#else
			/* Make an Error */
			#error "Wrong \"SHIFT_ORDER\" configuration option"
		#endif

		/* Pulse the clock pin to shift the next bit into the register */
		DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_CLOCK_PIN, HIGH);
		_delay_us(5);

		/* Pulse the clock pin low to complete the bit shift */
		DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_CLOCK_PIN, LOW);
		_delay_us(5);
	}
}





/*
 * @brief Reads one byte of data from the shift register.
 *
 * This function shifts in one byte of data from the shift register by sending
 * clock pulses. The data is returned in the specified bit order (SHIFT_LSB_FIRST or SHIFT_MSB_FIRST).
 *
 * @return (uint8) The data read from the shift register.
 */
uint8 SHIFT_IN_Byte(void)
{
	uint8 data = 0;

	/* Loop through each bit in the byte */
	for (uint8 bit_num = 0; bit_num < 8; bit_num++)
	{

		/* Shift in based on configured bit order */
		#if   SHIFT_ORDER == SHIFT_LSB_FIRST

			/* Read the Shifted-in bit (least significant bit first) */
			data |= DIO_GetPinValue(SHIFT_IN_PORT, SHIFT_IN_DATA_PIN) << bit_num;

		#elif SHIFT_ORDER == SHIFT_MSB_FIRST

			/* Read the Shifted-in bit (most significant bit first) */
			data |= DIO_GetPinValue(SHIFT_IN_PORT, SHIFT_IN_DATA_PIN) << (7 - bit_num);
		#else
			/* Make an Error */
			#error "Wrong \"SHIFT_ORDER\" configuration option"
		#endif

		/* Pulse the clock pin to shift the next bit into the register */
		DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_CLOCK_PIN, HIGH);
		_delay_us(5);

		/* Pulse the clock pin low to complete the bit shift */
		DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_CLOCK_PIN, LOW);
		_delay_us(5);
	}

	return data;
}





/*
 * @brief Latches data to 74HC595 output pins.
 *
 * This function pulses the latch pin (RCLK) to move the shifted serial data
 * into the output register, making it visible on the parallel output pins.
 */
void SHIFT_OUT_Latch(void)
{
	/* Enable the Latch by Setting the Load pin High */
	DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_LOAD_PIN, HIGH);

	_delay_us(5);

	/* Disable the Latch by Setting the Load pin Low */
	DIO_SetPinValue(SHIFT_OUT_PORT, SHIFT_OUT_LOAD_PIN, LOW);
}





/*
 * @brief Latches data from 74HC165 input pins.
 *
 * This function pulses the latch pin (SH/LD) to load the current state of
 * the parallel input pins into the shift register for serial reading.
 */
void SHIFT_IN_Latch(void)
{

	/* Enable the Latch by Setting the Load pin Low */
	DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_LOAD_PIN, LOW);

	_delay_us(5);

	/* Disable the Latch by Setting the Load pin High */
	DIO_SetPinValue(SHIFT_IN_PORT, SHIFT_IN_LOAD_PIN, HIGH);
}




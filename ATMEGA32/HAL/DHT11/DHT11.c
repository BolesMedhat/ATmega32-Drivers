/****************************************************************************
 * @file    DHT11.c
 * @author  Boles Medhat
 * @brief   DHT11 Driver Source File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides an interface to communicate with the DHT11 temperature
 * and humidity sensor using a single-wire protocol. It supports reading the
 * sensor values and validating them using the built-in checksum mechanism.
 *
 * @note
 * - Requires `DHT11_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "DHT11.h"





/*
 * @brief Reads temperature and humidity data from the DHT11 sensor.
 *
 * This function initiates communication with the DHT11 sensor using a start signal,
 * then reads a 40-bit response (5 bytes) containing humidity, temperature, and a checksum.
 * It verifies the checksum and returns the data in a `DHT11_Data` structure.
 *
 * @return (DHT11_Data) structure containing:
 * - `temperature` (uint8): Temperature in Celsius.
 * - `humidity` (uint8): Relative humidity percentage.
 * - `status` (uint8):
 *    - 0: Success.
 *    - 1: Checksum mismatch.
 *    - 2: Timeout or no response from sensor.
 */
DHT11_Data DHT11_Read(void)
{

	/* Struct to hold the final temperature, humidity, and status */
	DHT11_Data result = { 0 , 0 , 0 };

	/* Array to hold raw 5 bytes from sensor */
    uint8 data[5] = { 0 };


    /*=== Step 1: Start Signal ===*/

    /* Set pin as output to send start signal */
	DIO_SetPinDirection( DHT11_PORT , DHT11_PIN , OUTPUT );

	/* Set the pin LOW to send first part of start signal (pin low for ≥18ms)*/
	DIO_SetPinValue( DHT11_PORT , DHT11_PIN , LOW );
	_delay_ms( 18 );

	/* Set the pin HIGH to send second part of start signal (pin high for 20–40µs) */
	DIO_SetPinValue( DHT11_PORT , DHT11_PIN , HIGH );
	_delay_us( 20 );

	/* Set pin as input to read  from DHT11 sensor in step 2 */
	DIO_SetPinDirection( DHT11_PORT, DHT11_PIN, INPUT );



	/*=== Step 2: Wait for DHT11 Response ===*/

	uint16 timeout = 0;
	/* Wait for sensor to set pin LOW for first part of Sensor Response (pin low for 80µs) */
	while ( DIO_GetPinValue( DHT11_PORT , DHT11_PIN ) && timeout++ < DHT11_COUNTOUT );

	/* Check if the wait is end by time out */
	if ( timeout >= DHT11_COUNTOUT )
	{
		/* Set the status to time out and return it */
		result.status = DHT11_TIMEOUT_ERROR;
		return result;
	}

	/* Reset the time out */
	timeout = 0;

	/* Wait for sensor to set pin HIGH for second part of Sensor Response (pin high for 80µs) */
	while ( !DIO_GetPinValue( DHT11_PORT , DHT11_PIN ) && timeout++ < DHT11_COUNTOUT );

	/* Wait for sensor to finish setting the pin to HIGH */
	while ( DIO_GetPinValue( DHT11_PORT , DHT11_PIN ) && timeout++ < DHT11_COUNTOUT );

	/* Check if the wait is end by time out */
	if ( timeout >= DHT11_COUNTOUT )
	{
		/* Set the status to time out and return it */
		result.status = DHT11_TIMEOUT_ERROR;
		return result;
	}



	/* === Step 3: Read 40 Bits (5 Bytes) === */

	/* Loop over each byte of the 5 bytes */
	for ( uint8 byte = 0 ; byte < 5 ; byte++ )
	{
		/* Loop over each bit in the byte */
		for ( uint8 bit = 0 ; bit < 8 ; bit++ )
		{
			/* Make room for the next bit */
			data[ byte ] <<= 1;

			/* Waits for the start of the bit (DHT11 set the pin LOW for ~50 µs) */
		    while ( DIO_GetPinValue( DHT11_PORT , DHT11_PIN ) == 0 );

		    /* The DHT11 keeps the line HIGH for ~26–28 µs → logic 0, ~70 µs → logic 1 */
		    _delay_us( 30 );

		    /* If pin is still HIGH after 30us, it's likely a '1', otherwise it's a '0' */
		    data[ byte ] |= DIO_GetPinValue( DHT11_PORT , DHT11_PIN );

		    /* Waits until the line goes LOW again, which means the current bit is done */
		    while ( DIO_GetPinValue( DHT11_PORT , DHT11_PIN ) );
		}
	}



	/*=== Step 4: Verify Checksum ===*/

	/* Check that the last byte (Checksum) equal the sum for the first 4 bytes */
	uint8 checksum = data[0] + data[1] + data[2] + data[3];
	if ( checksum == data[4] )
	{
		/* Store and return the result */
		result.humidity = data[0];
		result.temperature = data[2];
		result.status = DHT11_SUCCESS;
		return result;
	}
	else
	{
		/* Set the status to Checksum mismatch and return it */
		result.status = DHT11_CHECKSUM_ERROR;
		return result;
	}


}




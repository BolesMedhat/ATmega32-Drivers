/****************************************************************************
 * @file    USONIC.c
 * @author  Boles Medhat
 * @brief   Ultrasonic Sensor Driver Sensor File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides functionality for interfacing with ultrasonic sensors
 * (such as HC-SR04). It allows the measurement of distances by triggering
 * the sensor and measuring the time taken for the echo to return.
 * The distance is calculated in centimeters.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module **before** calling any
 * 				   SERVO driver function. This driver does not initialize
 *	 	 	 	   TIMER1 module internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#include "USONIC.h"





/*
 * @brief  Reads the distance from the ultrasonic sensor.
 *
 * This function triggers the ultrasonic sensor to emit a pulse, waits for the echo
 * signal, and calculates the pulse width. The pulse width is then used to compute
 * the distance in centimeters.
 *
 * @param usonic   A structure of type `Usonic` containing:
 *                 - port_id:  Port connected to the ultrasonic sensor trigger and echo pins
 *                 - trig_pin: Pin ID for the trigger signal
 *                 - echo_pin: Pin ID for the echo signal
 *
 * @return: The distance in centimeters.
 */
uint16 USONIC_Read( Usonic usonic )
{
	uint16 start_time = 0;
	uint16 end_time = 0;
	uint32 pulse_width = 0;

	/* Set TRIG pin as output to send trigger signal */
	DIO_SetPinDirection( usonic.port_id , usonic.trig_pin , OUTPUT );

	/* Set ECHO pin as input to receive echo signal */
	DIO_SetPinDirection( usonic.port_id , usonic.echo_pin , INPUT );

	 /* Send trigger pulse: HIGH for 10us */
	DIO_SetPinValue( usonic.port_id , usonic.trig_pin , HIGH );
	_delay_us(10);

	 /* End trigger pulse */
	DIO_SetPinValue( usonic.port_id , usonic.trig_pin , LOW );

	/* Wait until ECHO pin goes HIGH (start of echo pulse) */
	while( DIO_GetPinValue( usonic.port_id , usonic.echo_pin ) == LOW );

	 /* Capture timer value at the start of pulse */
	start_time = TIMER1_GetTimerValue();

	/* Wait until ECHO pin goes LOW (end of echo pulse) */
	while( DIO_GetPinValue( usonic.port_id , usonic.echo_pin ) == HIGH );

	/* Capture timer value at the end of pulse */
	end_time = TIMER1_GetTimerValue();

	 /* Calculate pulse width */
	if (end_time >= start_time)
	{
		/* Pulse_width = end time - start time (no timer overflow) */
		pulse_width = end_time - start_time;
	}


	else
	{
		/* Pulse_width = (timer overflow value)- start time +  end time (timer overflow) */
		#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE

				pulse_width = ((TIMER1_GetCompare_A_Value() + 1) - start_time) + end_time;

		#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE

				pulse_width = ((ICU_GetICUvalue() + 1) - start_time) + end_time;

		#else

				pulse_width = (65536UL  - start_time) + end_time;

		#endif
	}

	/* Calculate distance in centimeters
	 * Formula: Distance = (pulse_width * prescaler * speed_of_sound) / F_CPU
	 * 17241.4 comes from (34300 cm/s) / 2 to account for round trip
	 * 0.2758624 is offset for more accuracy
	 */
	uint16 distance_cm = (pulse_width*TIMER1_PRESCALER  * 17241.4)/F_CPU + 0.2758624;

	 /* Wait for sensor to reset before next trigger */
	_delay_ms(60);

	/* Return the distance */
	return distance_cm;
}

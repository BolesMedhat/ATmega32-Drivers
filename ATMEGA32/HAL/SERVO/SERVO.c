/****************************************************************************
 * @file    SERVO.c
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Source File
 * @version 2.0
 * @date    [2025-04-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file provides an abstraction for controlling servo motors.
 * It includes functions for initializing a servo motor, setting its
 * angle, and controlling multiple servos using unique IDs or by pin assignments.
 * The servo can be connected to any pin, and each servo is assigned a unique ID
 * during initialization. The system supports up to 9 servo motors.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module in normal mode **before**
 * 				   calling any SERVO driver function. This driver does not initialize
 *	 	 	 	   TIMER1 module in normal mode internally.
 * - This driver supports up to 9 servo motors.
 * - It uses software PWM for controlling multiple servos, allowing for efficient
 *   management of a large number of servos.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#include "SERVO.h"


/* Array to Store Information about the Servos */
Servo servos[SERVO_MAX_NUM];


/* Counter to Track the Number of Servos Initialized */
uint8 servo_count = 0;





/*
 * @brief Interrupt service routine for handling servo PWM generation.
 *
 * This function is not intended for direct use by the user. It is called automatically
 * by Timer1's Compare B interrupt to update the PWM signal for each servo based on
 * its configured ticks. It manages the timing for each servo and sets the corresponding
 * pin HIGH or LOW to generate the correct pulse width.
 *
 * The function cycles through all initialized servos, updates the timer for the next
 * servo activation, and resets the timer once all servos have been processed.
 */
static void SERVO_Interrupt( void )
{

	/* Static Variable to Track the Active Servo ID, Initialized one time only in the First Call */
	static uint8 servo_id = 0xFF;


	/* Check if the Servo ID is Valid (used) */
	if ( servo_id < servo_count )
	{
		/* Set the Corresponding Servo Pin to LOW to Complete the Previous pulse */
		DIO_SetPinValue( servos[ servo_id ].port , servos[ servo_id ].pin , LOW );
		
		/* Move to the Next Servo */
		servo_id++;
	}
	else
	{
		/* Reset the Timer1 if All Servos have been Processed (to Start New Pulse for Eath Servo) */
		TIMER1_SetTimerValue( 0 );

		/* Reset the Servo ID to Start From the First Servo Again */
		servo_id = 0;
	}


	 /* Check if the New Servo ID is Still valid */
	if ( servo_id < servo_count )
	{
		/* Check if there are Ticks Set for this Servo */
		if ( servos[ servo_id ].ticks > 0 )
		{
			/* Set the Timer1 Compare Value to the Next Tick After Current Tick */
			TIMER1_SetCompare_B_Value( TIMER1_GetTimerValue() + servos[ servo_id ].ticks );

			/* Activate the Current Servo Pin to Generate Pulse Signal */
			DIO_SetPinValue( servos[ servo_id ].port , servos[ servo_id ].pin , HIGH );
		}
	}
	else
	{
		/* Check if the Interval Tick is Will Not Missed */
		if ( TIMER1_GetTimerValue() + 50 < SERVO_PWM_INTERVAL_TICKS )
		{
			/* Set the Timer1 Compare Value to the Interval Tick to Restting the Cycle */
			TIMER1_SetCompare_B_Value( SERVO_PWM_INTERVAL_TICKS );
		}
		else
		{
			/* Restting the Cycle */
			TIMER1_SetCompare_B_Value( TIMER1_GetTimerValue() + 20 );
		}
	}
}





/*
 * @brief Initializes a servo motor on a specific pin.
 *
 * This function is used to add a new servo to the system. Each servo is
 * assigned a unique ID and can be connected to any pin, not limited to timer pins.
 *
 * The maximum number of servos that can be added is 9.
 *
 * @param port: The port on which the servo is connected.
 * @param pin:  The pin on the specified port for controlling the servo.
 *
 * @return:     The assigned servo ID if initialization is successful,
 *                 or 0xFF if there are too many servos already initialized.
 */
uint8 SERVO_Init( uint8 port , uint8 pin )
{

	/* Check if the Maximum Number of Servos has been Reached */
	if (servo_count >= SERVO_MAX_NUM)
	{
		/* Return 0xFF as an Invalid Servo ID */
		return 0xFF;
	}


	/* Check if it is the First Servo Initialization */
	if ( servo_count == 0 )
	{
		/* Set the Interrupt Callback */
		TIMER1_SetCallback( TIMER1_COMPB_ID , & SERVO_Interrupt );

		/* Reset the Timer1 Value */
		TIMER1_SetTimerValue( 0 );
	}


	/* Initialize and Store the Servo Data */
	servos[servo_count].port = port;
	servos[servo_count].pin = pin;
	servos[servo_count].ticks = 0;


	/* Set teh Servo Pin to Output Low */
	DIO_SetPinDirection(port, pin, OUTPUT);
	DIO_SetPinValue(port, pin, LOW);


	/* Return the Assigned Servo ID and Increment the Count */
	return servo_count++;
}





/*
 * @brief Sets the angle of a servo motor by its unique ID.
 *
 * This function sets the desired angle of the servo specified by its unique ID.
 * The angle must be within the valid range of 0 to 180 degrees.
 *
 * @param servo_id: The unique ID of the servo to be controlled.
 * @param angle:    The desired angle for the servo (in degrees).
 */
void SERVO_SetAngleByID( uint8 servo_id , uint8 angle )
{

	/* Check if the Angle is within the Valid Range and the Servo ID is Valid */
	if ( ( angle >= SERVO_MIN_ANGLE ) && ( angle <= SERVO_MAX_ANGLE ) && ( servo_id < servo_count ) )
	{
		/* Convert the angle to microseconds ( 0 -> 1000 US  , 180 -> 2000 US ) */
		uint16 microseconds = SERVO_MIN_PULSE_US + angle * ( 1000.0 / 180 );

		/* Convert the microseconds to Timer Ticks for the PWM signal and Store it */
		servos[ servo_id ].ticks = SERVO_US_TO_TICKS( microseconds );
	}
}





/*
 * @brief Sets the angle of a servo motor by its connected pin.
 *
 * This function sets the desired angle of the servo specified by the port and pin
 * it is connected to. The angle must be within the valid range of 0 to 180 degrees.
 *
 * @param port:  The port on which the servo is connected.
 * @param pin:   The pin on the specified port for controlling the servo.
 * @param angle: The desired angle for the servo (in degrees).
 */
void SERVO_SetAngleByPin( uint8 port , uint8 pin , uint8 angle )
{

	/* Searches for the Servo Matching the Specified Port and Pin */
	for ( uint8 servo_id = 0 ; servo_id < servo_count ; servo_id++ )
	{
		if ( ( servos[ servo_id ].pin == pin ) && ( servos[ servo_id ].port == port ) )
		{
			/* Set the Angle for the specified Servo */
			SERVO_SetAngleByID( servo_id , angle );
		}
	}
}


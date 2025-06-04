/****************************************************************************
 * @file    SERVO_def.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Definitions Header File
 * @version 1.0
 * @date    [2025-04-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file contains the macro definitions, types, and constants used by the
 * Servo Motor Driver to control servo motors via PWM signals. It supports up
 * to 9 servos and utilizes Timer1 in normal mode for generating timing intervals.
 * The driver uses software PWM to handle multiple servos efficiently.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module in normal mode **before**
 * 				   calling any SERVO driver function. This driver does not initialize
 *	 	 	 	   TIMER1 module in normal mode internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef SERVO_DEF_H_
#define SERVO_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   macros    ----------------------------------------*/

/*Convert Microseconds to Timer Ticks*/
#define SERVO_US_TO_TICKS( US )				( ( ( US ) * ( F_CPU / 1000000UL ) ) / ( TIMER1_PRESCALER ) )
/*_______________________________________________________________________________________________*/


/*------------------------------------------   types    -----------------------------------------*/

/*Structure to hold Servo information (port ID, pin ID, ticks number)*/
typedef struct {
	uint32 port  : 2;						/*Port from [ DIO_PORTA  , DIO_PORTB , DIO_PORTC , DIO_PORTD ]*/
	uint32 pin   : 3;						/*Pin from  [ DIO_PIN0 to DIO_PIN7 ]*/
	uint32 ticks : 27;						/*number of timer ticks*/
}Servo;
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*Servo Number Limit*/
#define SERVO_MAX_NUM						9											/*Maximum number of servos that can be initialized (used)*/

/*Servo Angles*/
#define SERVO_MIN_ANGLE						0											/*Minimum servo angle (0   degrees)*/
#define SERVO_MAX_ANGLE						180											/*Maximum servo angle (180 degrees)*/

/*Servo PWM Interval*/
#define SERVO_PWM_INTERVAL_US				20000										/*Number of microseconds in PWM interval (20ms)*/
#define SERVO_PWM_INTERVAL_TICKS			SERVO_US_TO_TICKS( SERVO_PWM_INTERVAL_US )	/*Number of timer ticks in PWM interval*/

/*Servo Min pulse width*/
#define SERVO_MIN_PULSE_US					1000										/*Number of microseconds in minimum pulse width (1ms)*/
#define SERVO_MIN_PULSE_TICKS				SERVO_US_TO_TICKS( SERVO_MIN_PULSE_US )		/*Number of timer ticks in minimum pulse width*/

/*Servo Max pulse width*/
#define SERVO_MAX_PULSE_US					200										/*Number of microseconds in maximum pulse width (2ms)*/
#define SERVO_MAX_PULSE_TICKS				SERVO_US_TO_TICKS( SERVO_MAX_PULSE_US )		/*Number of timer ticks in maximum pulse width*/
/*_______________________________________________________________________________________________*/


#endif /* SERVO_DEF_H_ */

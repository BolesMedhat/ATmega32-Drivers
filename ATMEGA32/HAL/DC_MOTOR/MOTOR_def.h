/****************************************************************************
 * @file    MOTOR_def.h
 * @author  Boles Medhat
 * @brief   DC Motor Driver Definitions Header File
 * @version 1.0
 * @date    [2024-07-08]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This header file defines the data structures and constants used for controlling
 * DC motors in an embedded system. It provides the `Motor` structure that holds
 * information about the port and pin assignments for motor control, as well as
 * various configuration options for motor direction and steering modes.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef MOTOR_DEF_H_
#define MOTOR_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Moteor type for use in function parameter*/
typedef struct
{
	uint8 motor_port : 2;	/*Select MOTOR_PORT from [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]*/
	uint8 first_pin  : 3;	/*Select FIRST_PIN  from [ DIO_PIN0 to DIO_PIN7 ]*/
	uint8 second_pin : 3;	/*Select SECOND_PIN from [ DIO_PIN0 to DIO_PIN7 ]*/
}Motor;
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*Steering mode*/
#define MOTOR_REVERSE_ON_TURN				0	/*Make one Motor Moves Forward and the other Moves Backward during a turn*/
#define MOTOR_STOP_ON_TURN					1	/*Make one Motor Moves Forward and the other Moves Stop 	during a turn*/

/*DC MOTOR Directions (for DC_MOTOR_SET_Direction functions)*/
#define MOTOR_FORWARD						0	/*Moves the motors in the forward direction*/
#define MOTOR_BACKWARD						1	/*Moves the motors in the backward direction*/
#define MOTOR_STOP							2	/*Stops the motors (no movement)*/
#define MOTOR_TURN_RIGHT					3	/*Moves the motors to turn right*/
#define MOTOR_TURN_LEFT						4	/*Moves the motors to turn left*/
/*_______________________________________________________________________________________________*/


#endif /* MOTOR_DEF_H_ */

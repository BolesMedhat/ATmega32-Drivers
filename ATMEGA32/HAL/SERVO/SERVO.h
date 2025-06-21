/****************************************************************************
 * @file    SERVO.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Header File
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
 * The SERVO driver includes the following functionalities:
 * - Initialization of a servo motor on a specific port and pin.
 * - Setting the servo angle (0 to 180 degrees) by unique ID.
 * - Setting the servo angle by its connected port and pin.
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

#ifndef SERVO_H_
#define SERVO_H_

#include "../../MCAL/TIMER1/TIMER1.h"
#include "../../MCAL/DIO/DIO.h"
#include "SERVO_def.h"


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


/*
 * @brief Sets the angle of a servo motor by its unique ID.
 *
 * This function sets the desired angle of the servo specified by its unique ID.
 * The angle must be within the valid range of 0 to 180 degrees.
 *
 * @param servo_id: The unique ID of the servo to be controlled.
 * @param angle:    The desired angle for the servo (in degrees).
 */
void SERVO_SetAngleByID( uint8 servo_id , uint8 angle );


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
void SERVO_SetAngleByPin( uint8 port , uint8 pin , uint8 angle );


#endif /* SERVO_H_ */

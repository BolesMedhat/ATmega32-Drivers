/****************************************************************************
 * @file    MOTOR.h
 * @author  Boles Medhat
 * @brief   DC Motor Driver Header File
 * @version 1.0
 * @date    [2024-07-08]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides an interface to control DC motors using H-Bridge logic
 * via two control pins per motor. It supports forward, backward, stop, and
 * turning operations for single or dual motor setups, with configurable
 * steering behavior during turns.
 *
 * The MOTOR driver includes the following functionalities:
 * - Initialization of motor control pins.
 * - Functions to set the motor direction (forward, backward, stop).
 * - Coordinated control of two motors for forward/backward movement or turns.
 * - Configurable steering modes for turning (right or left).
 *
 * @note
 * - Requires `MOTOR_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_

#include "MOTOR_config.h"
#include "../../MCAL/DIO/DIO.h"


/*
 * @brief Initializes the DC motor by setting up the control pins.
 *
 * This function sets the direction of the specified control pins to output mode.
 *
 * @param motor: a `Motor` structure containing the motor's port and pin information.
 */
void MOTOR_Init( Motor motor );


/*
 * @brief Sets the DC motor to move forward.
 *
 * Configures the motor control pins to drive the motor forward.
 *
 * @param motor: a `Motor` structure containing the motor's port and pin information.
 */
void MOTOR_Forward( Motor motor );


/*
 * @brief Sets the DC motor to move backward.
 *
 * Configures the motor control pins to drive the motor in reverse.
 *
 * @param motor: a `Motor` structure containing the motor's port and pin information.
 */
void MOTOR_Backward( Motor motor );


/*
 * @brief Stops the DC motor.
 *
 * Configures the motor control pins to stop the motor's movement.
 *
 * @param motor: a `Motor` structure containing the motor's port and pin information.
 */
void MOTOR_Stop( Motor motor );


/*
 * @brief Sets both DC motors to move forward.
 *
 * Configures the control pins of the left and right motors to drive them forward.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 */
void MOTOR_BothForward( Motor right_motor , Motor left_motor );


/*
 * @brief Sets both DC motors to move backward.
 *
 * Configures the control pins of the left and right motors to drive them in reverse.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 */
void MOTOR_BothBackward( Motor right_motor , Motor left_motor );


/*
 * @brief Stops both DC motors.
 *
 * Configures the control pins of the left and right motors to stop their movement.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 */
void MOTOR_BothStop( Motor right_motor , Motor left_motor );


/*
 * @brief Controls both DC motors to make the vehicle turn right.
 *
 * Configures the motors based on the steering mode to achieve a right turn.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 */
void MOTOR_TurnRight( Motor right_motor , Motor left_motor );


/*
 * @brief Controls both DC motors to make the vehicle turn left.
 *
 * Configures the motors based on the steering mode to achieve a left turn.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 */
void MOTOR_TurnLeft( Motor right_motor , Motor left_motor );


/*
 * @brief Sets the direction of both DC motors based on the specified direction.
 *
 * Controls the motors to move forward, backward, stop, or turn based on the `MOTOR_Direction` parameter.
 *
 * @param right_motor: a `Motor` structure for the right motor's port and pin information.
 * @param left_motor:  a `Motor` structure for the left motor's port and pin information.
 * @param Direction:   Direction for the motors to move. Possible values:
 *        - `MOTOR_FORWARD` to move forward,
 *        - `MOTOR_BACKWARD` to move backward,
 *        - `MOTOR_STOP` to stop,
 *        - `MOTOR_TURN_RIGHT` to turn right,
 *        - `MOTOR_TURN_LEFT` to turn left.
 */
void MOTOR_SET_Direction( Motor right_motor , Motor left_motor , uint8 Direction );


#endif /* MOTOR_H_ */

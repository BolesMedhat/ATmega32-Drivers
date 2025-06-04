/****************************************************************************
 * @file    MOTOR_CONFIG.h
 * @author  Boles Medhat
 * @brief   DC Motor Configuration Header File
 * @version 1.0
 * @date    [2024-07-08]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This header file provides configuration options for controlling the DC motors.
 * It includes the selection of the steering mode, which defines how the motors
 * behave during turns. The configuration is crucial for motor control in systems
 * that involve vehicle-like movement, such as robots or mobile platforms.
 *
 * @note
 * - available choices are defined in `MOTOR_def.h` and explained with comments there.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef MOTOR_CONFIG_H_
#define MOTOR_CONFIG_H_

#include "MOTOR_def.h"


/*Set Steering mode
 * choose between:
 * 1. MOTOR_REVERSE_ON_TURN			<--the most used
 * 2. MOTOR_STOP_ON_TURN
 */
#define MOTOR_STEERING_MODE					MOTOR_REVERSE_ON_TURN


#endif /* MOTOR_CONFIG_H_ */

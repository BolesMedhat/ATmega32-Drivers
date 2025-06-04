/****************************************************************************
 * @file    JoyStick.c
 * @author  Boles Medhat
 * @brief   Joystick Driver Header File
 * @version 1.0
 * @date    [2024-09-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for interfacing with a 2-axis
 * analog joystick and button using the ADC and digital I/O peripherals.
 * It supports dead zone filtering and rescaling of analog values to signed
 * integer ranges, as well as direction detection based on X and Y positions.
 *
 * The joystick driver includes the following functionalities:
 * - Initialization of joystick button pin.
 * - Read and process joystick X-axis value with dead zone filtering.
 * - Read and process joystick Y-axis value with dead zone filtering.
 * - Read joystick button state.
 * - Determine directional input from joystick analog position.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the ADC module **before** using this driver.
 *   			   The joystick driver assumes the ADC is configured for 10-bit readings.
 * - Requires `JoyStick_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "JoyStick_config.h"
#include "../../LIB/MAPPING/MAPPING.h"


/*
 * @brief Initializes the joystick by configuring the ADC and button.
 *
 * This function configures the joystick button pin as an input with an internal pull-up resistor.
 */
void JOYSTICK_InitButton( void );


/*
 * @brief Reads and processes the joystick's X-axis value.
 *
 * This function reads the raw ADC value for the X-axis, applies a dead zone filter, and maps
 * the value to a defined range. The function returns 0 if the joystick is within the dead zone.
 * the full Range is -JOYSTICK_X_ABS_MAX to JOYSTICK_X_ABS_MAX.
 *
 * @return: The processed X-axis value.
 */
sint16 JOYSTICK_Read_X_Axis( void );


/*
 * @brief Reads and processes the joystick's Y-axis value.
 *
 * This function reads the raw ADC value for the Y-axis, applies a dead zone filter, and maps
 * the value to a defined range. The function returns 0 if the joystick is within the dead zone.
 * the full Range is -JOYSTICK_Y_ABS_MAX to JOYSTICK_Y_ABS_MAX.
 *
 * @return: The processed Y-axis value.
 */
sint16 JOYSTICK_Read_Y_Axis( void );


/*
 * @brief Reads the state of the joystick button.
 *
 * This function returns the state of the joystick button.
 *
 * @return: The button state; 1 if pressed, 0 if not pressed.
 */
uint8 JOYSTICK_ReadButton( void );


/*
 * @brief Determines the direction of the joystick based on its X and Y-axis values.
 *
 * This function reads the raw ADC values for both the X and Y axes of the joystick. It then
 * compares these values against the joystick's center position and dead zone to determine
 * the direction in which the joystick is currently pushed.
 *
 * @return: The direction of the joystick:
 *         - JOYSTICK_DIRECTION_UP if the joystick is pushed up,
 *         - JOYSTICK_DIRECTION_DOWN if the joystick is pushed down,
 *         - JOYSTICK_DIRECTION_RIGHT if the joystick is pushed right,
 *         - JOYSTICK_DIRECTION_LEFT if the joystick is pushed left,
 *         - JOYSTICK_DIRECTION_CENTER if the joystick is within the dead zone.
 */
uint8 JOYSTICK_GetDirection( void );


#endif /* JOYSTICK_H_ */

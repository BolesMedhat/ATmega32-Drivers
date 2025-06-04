/****************************************************************************
 * @file    KEYPAD.h
 * @author  Boles Medhat
 * @brief   Keypad Driver Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides the implementation for interfacing a matrix keypad.
 * It supports flexible configurations for number of rows and columns,
 * customizable key mapping, and selectable return modes (character or index).
 *
 * The KEYPAD driver includes the following functionalities:
 * - Initialization of keypad row and column pins.
 * - Return of pressed key as character or index based on configuration.
 *
 * @note
 * - Requires `KEYPAD_config.h` for macro-based configuration.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "Keypad_config.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>


/*
 * @brief Initializes the keypad by configuring row and column pins.
 *
 * This function sets up the keypad rows and columns:
 * - The row pins are configured as outputs and set to high.
 * - The column pins are configured as inputs with internal pull-up resistors enabled.
 */
void KEYPAD_Init( void );


/*
 * @brief Detects and returns the key that is currently pressed on the keypad.
 *
 * This function checks each row and column of the keypad to determine if a key is pressed.
 * It returns the corresponding key based on the configuration:
 * - Returns a character based on the button map if `KEYPAD_RETURN_MODE` is set to `KEYPAD_RETURN_CHAR`.
 * - Returns an index value of the key in the keypad matrix if `KEYPAD_RETURN_MODE` is set to `KEYPAD_RETURN_INDEX`.
 *
 * @return The pressed key as defined in the button map or an index if no key is pressed.
 */
uint8 KEYPAD_GetPressedKey( void );


#endif /* KEYPAD_H_ */

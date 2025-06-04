/****************************************************************************
 * @file    KEYPAD_config.h
 * @author  Boles Medhat
 * @brief   Keypad Driver Configuration Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration macros for the Keypad driver. It allows
 * the user to customize the keypad behavior, such as the number of rows and
 * columns, port and pin assignments, return type, and the button mapping.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_

#include "Keypad_def.h"


/*Set the Value Returned when No Key is Pressed on the Keypad*/
#define KEYPAD_NOT_PRESSED					0xFF


/*Set the Number of Rows in the Keypad*/
#define KEYPAD_ROWS_NUM						4


/*Set the Number of Columns in the Keypad*/
#define KEYPAD_COLS_NUM						4


/*Set the DIO Port For the Keypad Rows
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define KEYPAD_ROW_PORT						DIO_PORTC


/*Set the DIO Port For the Keypad Columns
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define KEYPAD_COL_PORT						DIO_PORTC


/*Set the Starting DIO Pin For the Keypad Rows
 * choose between:
 * 1. DIO_PIN0
 * 2. DIO_PIN1
 * 3. DIO_PIN2
 * 4. DIO_PIN3
 * 5. DIO_PIN4
 * 6. DIO_PIN5
 * 7. DIO_PIN6
 * 8. DIO_PIN7
 */
#define KEYPAD_FIRST_ROW_PIN				DIO_PIN0


/*Set the Starting DIO Pin For the Keypad Columns
 * choose between:
 * 1. DIO_PIN0
 * 2. DIO_PIN1
 * 3. DIO_PIN2
 * 4. DIO_PIN3
 * 5. DIO_PIN4
 * 6. DIO_PIN5
 * 7. DIO_PIN6
 * 8. DIO_PIN7
 */
#define KEYPAD_FIRST_COL_PIN				DIO_PIN4


/*Set the Keypad Return mode
 * choose between:
 * 1. KEYPAD_RETURN_CHAR					<--the most used
 * 2. KEYPAD_RETURN_INDEX
 */
#define KEYPAD_RETURN_MODE					KEYPAD_RETURN_CHAR


/*Set the Keypad Buttons Mapping Array (for KEYPAD_RETURN_CHAR mode)*/
#define KEYPAD_BUTTONS_ARRAY				\
{{'1','2','3','A'},							\
 {'4','5','6','B'},							\
 {'7','8','9','C'},							\
 {'*','0','#','D'}}


/*Error if config is invalid (out of range 1-8 or zero)*/
#if   (KEYPAD_ROWS_NUM + KEYPAD_FIRST_ROW_PIN > 8) || (KEYPAD_ROWS_NUM == 0)
	#error "KEYPAD_ROWS_NUM + KEYPAD_FIRST_ROW_PIN must be between 1 and 8"
#elif (KEYPAD_COLS_NUM + KEYPAD_FIRST_COL_PIN > 8) || (KEYPAD_COLS_NUM == 0)
	#error "KEYPAD_COLS_NUM + KEYPAD_FIRST_COL_PIN must be between 1 and 8"
#endif


#endif /* KEYPAD_CONFIG_H_ */

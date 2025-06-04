/****************************************************************************
 * @file    KEYPAD.c
 * @author  Boles Medhat
 * @brief   Keypad Driver Source File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides the implementation for interfacing a matrix keypad.
 * It supports flexible configurations for number of rows and columns,
 * customizable key mapping, and selectable return modes (character or index).
 *
 * @note
 * - Requires `KEYPAD_config.h` for macro-based configuration.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/


#include "Keypad.h"


/* Define the Buttons Map Array if the Return Mode is Set to Return Characters */
#if KEYPAD_RETURN_MODE == KEYPAD_RETURN_CHAR
static const uint8 KEYPAD_ButtonsMap[KEYPAD_ROWS_NUM][KEYPAD_COLS_NUM] = KEYPAD_BUTTONS_ARRAY;
#endif





/*
 * @brief Initializes the keypad by configuring row and column pins.
 *
 * This function sets up the keypad rows and columns:
 * - The row pins are configured as outputs and set to high.
 * - The column pins are configured as inputs with internal pull-up resistors enabled.
 */
void KEYPAD_Init( void )
{

	/* Loop on Keypad Row Pins to Initialize each Row Pin */
	/* From First Pin (KEYPAD_FIRST_ROW_PIN) to Last Pin (KEYPAD_FIRST_ROW_PIN + KEYPAD_ROWS_NUM - 1)*/
	for(uint8 row_num = 0 ; row_num < KEYPAD_ROWS_NUM ; row_num++)
	{
		/* Initialize the Keypad Row Pin Direction as Output */
		DIO_SetPinDirection( KEYPAD_ROW_PORT , KEYPAD_FIRST_ROW_PIN + row_num , OUTPUT );

		/* Set the Keypad Row Pin as High */
		DIO_SetPinValue( KEYPAD_ROW_PORT , KEYPAD_FIRST_ROW_PIN + row_num , HIGH );
	}

	/* Loop on Keypad column Pins to Initialize each column Pin */
	/* From First Pin (KEYPAD_FIRST_COL_PIN) to Last Pin (KEYPAD_FIRST_COL_PIN + KEYPAD_COLS_NUM - 1)*/
	for(uint8 col_num = 0 ; col_num < KEYPAD_COLS_NUM ; col_num++)
	{
		/* Initialize the Keypad column Pin Direction as Input with Internal Pull-up Resistors */
		DIO_SetPinDirection( KEYPAD_COL_PORT , KEYPAD_FIRST_COL_PIN + col_num , INPUT_PULLUP );
	}
}





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
uint8 KEYPAD_GetPressedKey( void )
{

	/* Initialize the Pressed Key to Return if No Key Pressed */
	uint8 Pressed_key = KEYPAD_NOT_PRESSED;

	/* Variables to Iterate Over Rows and Columns */
	uint8 row,col;

	/* Loop through each Row to Detect a Pressed Key */
	for(row = 0 ; row < KEYPAD_ROWS_NUM ; row++)
	{

		/* Set the Row by Low to Check if the Pressed Key in This Row */
		/* When one of the Input Pull-up Columns Read as Low, it indicates that the Pressed Key in this Row */
		DIO_SetPinValue( KEYPAD_ROW_PORT , KEYPAD_FIRST_ROW_PIN + row , LOW );

		/* Loop through each Column to Check if a Key is Pressed */
		for(col = 0 ; col < KEYPAD_COLS_NUM ; col++)
		{

			/* Check if the Key in the Current Row and Column is Pressed (Column Pin Reads LOW) */
			if(DIO_GetPinValue( KEYPAD_COL_PORT , KEYPAD_FIRST_COL_PIN + col ) == LOW)
			{
				/* Check on the Return mode Depending on the Configuration */
				#if   KEYPAD_RETURN_MODE == KEYPAD_RETURN_CHAR

					/* Return the Pressed Key as a Character from the Buttons Map Array */
					Pressed_key = KEYPAD_ButtonsMap[row][col];

				#elif KEYPAD_RETURN_MODE == KEYPAD_RETURN_INDEX

					/* Return the Pressed Key as a calculated Index of the Pressed Key */
					Pressed_key = row * KEYPAD_COLS_NUM + col;

				#else
					/* Make an Error */
					#error "Wrong \"KEYPAD_RETURN_MODE\" configuration option"
				#endif

				/* Exit the Column Loop Since a Key has been Detected */
				break;
			}
		}

		/* Restore the row Pin to HIGH, Returning it to its Default State */
		DIO_SetPinValue( KEYPAD_ROW_PORT , KEYPAD_FIRST_ROW_PIN + row , HIGH );

		/* If a Key has been Detected, Exit the Row Loop */
		if(Pressed_key != KEYPAD_NOT_PRESSED)
		{
			/* Exit the Row Loop Since a Key has been Detected */
			break;
		}

	}

	/* Return the Pressed Key Value */
	return Pressed_key;
}




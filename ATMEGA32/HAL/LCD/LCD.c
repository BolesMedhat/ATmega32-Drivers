/****************************************************************************
 * @file    LCD.c
 * @author  Boles Medhat
 * @brief   LCD Driver Source File
 * @version 2.0
 * @date    [2024-06-27]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for interfacing with character
 * LCD modules (16x2 or 16x4) based on the HD44780 controller. It supports both
 * 4-bit and 8-bit communication modes, initialization, and includes cursor tracking,
 * automatic row shifting, and custom character handling.
 *
 * @note
 * - Requires `LCD_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "LCD.h"

/* Stores the Current Cursor Position on the LCD (Row: 0 to LCD_NUMBER_OF_ROWS, Col: 0 to 15) */
uint8 LCD_CurrentRow = 0 , LCD_CurrentCol = 0;





/*
 * @brief Initializes the LCD display based on configuration settings from LCD_config.h.
 *
 * This function sets the direction of the control and data pins, selects the LCD mode (4-bit or 8-bit),
 * and sends initialization commands to the LCD to configure it properly.
 */
void LCD_Init( void )
{

	/* Set the RS Pin Direction to OUTPUT */
	DIO_SetPinDirection( LCD_RS_PORT , LCD_RS_PIN , OUTPUT );

	/* Set the E Pin Direction to OUTPUT */
	DIO_SetPinDirection( LCD_E_PORT  , LCD_E_PIN  , OUTPUT );

	/* Check the LCD mode */
	#if   LCD_MODE == LCD_4_BITS_MODE

		/*  Set the Direction of the Data Pins to OUTPUT for 4-bit mode */
		DIO_SetPinDirection( LCD_DATA_PORT , LCD_DATA_PIN0 , OUTPUT );
		DIO_SetPinDirection( LCD_DATA_PORT , LCD_DATA_PIN1 , OUTPUT );
		DIO_SetPinDirection( LCD_DATA_PORT , LCD_DATA_PIN2 , OUTPUT );
		DIO_SetPinDirection( LCD_DATA_PORT , LCD_DATA_PIN3 , OUTPUT );

	#elif LCD_MODE == LCD_8_BITS_MODE

		/*  Set the Direction of the Data Port to OUTPUT for 8-bit mode */
		DIO_SetPortDirection( LCD_DATA_PORT , OUTPUT_PORT );

	#else
		/* Make an Error */
		#error "Wrong \"LCD_MODE\" configuration option"
	#endif

	/* Delay to Allow the LCD to Power up and Stabilize */
	_delay_ms( 50 );


	/* Send Commands to Initialize the LCD with the Specified Settings based on LCD_config.h file choices */

	/* Return Home */
	LCD_SendCommand( LCD_RETURN_TO_HOME );

	/* delay to Ensure the LCD Processes the Return Home Command*/
	_delay_ms( 2 );

	/* Set the Number of Data Bits mode (4-bit or 8-bit) */
	LCD_SendCommand( LCD_MODE );

	/* Configure the Cursor Display Status (On, Off, or Blinking) */
	LCD_SendCommand( LCD_CURSOR_STATUS );

	/* Set the Cursor Shift Direction (Left or Right) */
	LCD_SendCommand( LCD_CURSOR_SHIFT_RIGHT );

	/* Clear the LCD Screen */
	LCD_SendCommand( LCD_CLEAR_SCREEN );

	/* delay to Ensure the LCD Processes the Clear Screen Command*/
	_delay_ms( 2 );

}





/*
 * @brief Prints a single character on the LCD at the current cursor position.
 *
 * This function sends the specified character to the LCD and updates the cursor
 * position accordingly. It handles automatic row switching based on the defined
 * `LCD_AUTO_MOVE_MODE` configuration, either disabling or enabling automatic row
 * movement when the cursor exceeds the column limit of the first row.
 *
 * @param character: The character to be displayed on the LCD.
 */
void LCD_PrintCharacter( char character )
{

	/* Send the Character Data to the LCD */
	LCD_SendData( character );

	/* Update the Stored Cursor Column */
	LCD_CurrentCol++;


	#if LCD_AUTO_MOVE_MODE == LCD_AUTO_MOVE_ROW_ENABLE

		/* Check if the Cursor is on the Row and has Reached or Passed the End (16 character) */
		if ( LCD_CurrentRow < LCD_NUMBER_OF_ROWS && LCD_CurrentCol >=  LCD_COLS_NUM )
		{
			/* Move to the Second Row */
			LCD_SetCursor( LCD_CurrentRow + 1 , LCD_CurrentCol - LCD_COLS_NUM );
		}

	#endif

}





/*
 * @brief Prints a string on the LCD starting at the current cursor position.
 *
 * This function iterates through each character of the provided string and
 * prints them one by one on the LCD.
 *
 * @param str: The string to be printed on the LCD. The string should be null-terminated.
 */
void LCD_PrintString( const char * str )
{

	/*  Loop through each Character of the String Until the NULL Character is found */
	for(uint8 CharacterIndex = 0 ; str[CharacterIndex] != '\0' ; CharacterIndex++)
	{
		/* Print each Character on the LCD */
		LCD_PrintCharacter( str[CharacterIndex] );
	}
}





/*
 * @brief Prints a signed integer number on the LCD at the current cursor position.
 *
 * This function converts the given integer number to a string in base 10
 * and then prints it on the LCD starting at the current cursor position.
 *
 * @param number: The signed integer number to be printed on the LCD.
 */
void LCD_PrintNumber( sint32 number )
{

	/* Store the integer number to arr & 10 is for decimal numbering system*/
	char str[12];
	DC_itoa( number , str , 10 );

	/* Print the String on the LCD */
	LCD_PrintString( str );
}





/*
 * @brief Sets the cursor to a specific row and column on the LCD.
 *
 * This function moves the cursor to the specified row and column on the LCD screen.
 * The row can be range 0 to LCD_MAX_ROWS-1, and the column can range from 0 to 15.
 * The cursor's position is updated globally to track the current position.
 *
 * @param row: The row number (0 to LCD_MAX_ROWS-1) to position the cursor on.
 * @param col: The column number (0 to 15) to position the cursor at.
 */
void LCD_SetCursor( uint8 row , uint8 col )
{

	/* Check if the Specified Row and Column are Within the Valid Range */
	if( ( row < LCD_NUMBER_OF_ROWS ) && ( col < LCD_COLS_NUM ) )
	{
		/* Update the Global Variables to Track the Current Cursor Position */
		LCD_CurrentRow = row;
		LCD_CurrentCol = col;

		/* Initialize the Position Command with the base Command for Setting DDRAM Address */
		uint8 position = LCD_SET_DDRAM_ADDRESS;


		/* First LCD Row */
		if ( row == 0 )
		{
			/* Set Position for the First Row (Row 0) */
			position |= LCD_FIRST_ROW_ADDRESS;
		}
		else if ( row == 1 )
		{
			/* Set Position for the Second Row (Row 1) */
			position |= LCD_SECOND_ROW_ADDRESS;
		}
		else if ( row == 2 )
		{
			/* Set Position for the third Row (Row 2) */
			position |= LCD_THIRD_ROW_ADDRESS;
		}
		else
		{
			/* Set Position for the fourth Row (Row 3) */
			position |= LCD_FOURTH_ROW_ADDRESS;
		}

		/* Adding the Column Offset */
		position += col;

		/* Send the Command to the LCD to Set the Cursor to the Calculated Position */
		LCD_SendCommand( position );
	}
}




/*
 * @brief Clears the entire LCD screen and sets the cursor to the home position (0,0).
 *
 * This function clears the LCD display and resets the cursor position to the top-left corner
 * (row 0, column 0).
 */
void LCD_ClearScreen( void )
{

	/* Clear the LCD Screen and Sets the Cursor to the Home Position (0,0) */
	LCD_SendCommand( LCD_CLEAR_SCREEN );

	/* Update the Global Variables to Cursor to the Home Position (0,0) */
	LCD_CurrentRow = 0;
	LCD_CurrentCol = 0;

	/* delay to Ensure the LCD Processes the Clear Screen Command*/
	_delay_ms(2);
}





/*
 * @brief Saves a custom character to the LCD's CGRAM (Character Generator RAM).
 *
 * This function stores a custom character defined by the user in the CGRAM of the LCD.
 * The custom character data is passed in an array, and it is saved at the specified CGRAM address
 * (ranging from 0 to 7).
 *
 * @param custom_char_arr: Pointer to an array containing 8 bytes representing the custom character.
 * @param CGRAM_address:   The address (0 to 7) in the CGRAM where the custom character will be stored.
 */
void LCD_SaveCustomChar( uint8 * custom_char_arr , uint8 CGRAM_address )
{

	/* Check if the Specified Address is Within the Valid Range (0 to 7) */
	if( CGRAM_address < LCD_CHAR_SIZE )
	{

		/* Send the Command to Set the CGRAM Address, Shifting the Address to the Correct Position */
		LCD_SendCommand( LCD_SET_CGRAM_ADDRESS | (CGRAM_address << 3) );

		/* Loop through each Byte of the Custom Character Array (8 bytes) */
		for(uint8 byteIndex = 0 ; byteIndex < 8 ; byteIndex++)
		{
			/* Write each Byte to the CGRAM to form the Custom Character */
			LCD_SendData(custom_char_arr[byteIndex]);
		}

		/* Restore Cursor to the Previous Position */
		LCD_SetCursor( LCD_CurrentRow , LCD_CurrentCol );
	}
}





/*
 * @brief Returns the current row position of the cursor on the LCD.
 *
 * This function retrieves the current row where the cursor is positioned on the LCD screen.
 *
 * @return uint8 The current row (0 or 1) of the cursor on the LCD.
 */
uint8 LCD_GetRow( void )
{
	return LCD_CurrentRow;
}





/*
 * @brief Returns the current column position of the cursor on the LCD.
 *
 * This function retrieves the current column where the cursor is positioned on the LCD screen.
 *
 * @return uint8 The current column (0 to 15) of the cursor on the LCD.
 */
uint8 LCD_GetColumn( void )
{
	return LCD_CurrentCol;
}





/*
 * @brief Shifts the entire display content one position to the left.
 *
 * This function moves the content of the LCD display one position to the left.
 * It also adjusts the cursor position if necessary.
 */
void LCD_ShiftDisplayLeft( void )
{
	/* Shifts the Entire Display Content One Position to the Left */
	LCD_SendCommand( LCD_SHIFT_DISPLAY_LEFT );

	/* Check if the Column is in Valid Range */
	if( LCD_CurrentCol > 0 )
	{
		/* Update the Stored Cursor Column */
		LCD_CurrentCol--;
	}

}





/*
 * @brief Shifts the entire display content one position to the right.
 *
 * This function moves the content of the LCD display one position to the right. It also
 * adjusts the cursor position and handles automatic row movement based on the configuration.
 */
void LCD_ShiftDisplayRight( void )
{
	/* Shifts the Entire Display Content One Position to the Right */
	LCD_SendCommand( LCD_SHIFT_DISPLAY_RIGHT );

	/* Update the Stored Cursor Column */
	LCD_CurrentCol++;


	#if LCD_AUTO_MOVE_MODE == LCD_AUTO_MOVE_ROW_ENABLE

		/* Check if the Cursor is on the Row and has Reached or Passed the End (0x10) */
		if ( LCD_CurrentRow < LCD_NUMBER_OF_ROWS && LCD_CurrentCol >=  LCD_COLS_NUM )
		{
			/* Move to the Second Row */
			LCD_SetCursor( LCD_CurrentRow + 1 , LCD_CurrentCol - LCD_COLS_NUM );
		}

	#endif

}





/*
 * @brief Sends a command to the LCD to control its operation.
 *
 * This function sends a command byte to the LCD. The command can either be in 4-bit or 8-bit mode,
 * depending on the LCD configuration. The function sets the appropriate pins for the command,
 * and includes necessary delays for the LCD to process the command.
 *
 * @param command: The command byte to be sent to the LCD.
 */
void LCD_SendCommand( uint8 command )
{
	/* Sends a Command to the LCD to Control its Operation */

	/* Check the LCD mode */
	#if   LCD_MODE == LCD_4_BITS_MODE
		/* LCD 4 Bits Data mode */

		/* Set RS Pin to LOW for Command mode */
		DIO_SetPinValue( LCD_RS_PORT , LCD_RS_PIN , LOW );


		/* Send the Higher Nibble (4 Bits) of the Command */
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN0 , GET_BIT( command , 4 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN1 , GET_BIT( command , 5 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN2 , GET_BIT( command , 6 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN3 , GET_BIT( command , 7 ) );


		/* Set Enable Pin to High to Signal the LCD that Command is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT  , LCD_E_PIN  , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Command is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(10);

		/* Send the Lower Nibble (4 Bits) of the Command */
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN0 , GET_BIT( command , 0 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN1 , GET_BIT( command , 1 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN2 , GET_BIT( command , 2 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN3 , GET_BIT( command , 3 ) );

		/* Set Enable Pin to High to Signal the LCD that Command is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Command is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(60);


	#elif LCD_MODE == LCD_8_BITS_MODE
		/* LCD 8 Bits Data mode */

		/* Set RS Pin to LOW for Command mode */
		DIO_SetPinValue( LCD_RS_PORT , LCD_RS_PIN , LOW );

		/* Send the Command */
		DIO_SetPortValue( LCD_DATA_PORT , command );

		/* Set Enable Pin to High to Signal the LCD that Command is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT  , LCD_E_PIN  , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Command is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Command */
		_delay_us(60);

	#endif

}





/*
 * @brief Sends a data to the LCD to control its operation.
 *
 * This function sends a data byte to the LCD. The data can either be in 4-bit or 8-bit mode,
 * depending on the LCD configuration. The function sets the appropriate pins for the data,
 * and includes necessary delays for the LCD to process the data.
 *
 * @param data: The data byte to be sent to the LCD.
 */
void LCD_SendData( char data )
{
	/* Sends a Data to the LCD to Control its Operation */

	/* Check the LCD mode */
	#if   LCD_MODE == LCD_4_BITS_MODE
		/* LCD 4 Bits Data mode */

		/* Set RS Pin to LOW for Data mode */
		DIO_SetPinValue( LCD_RS_PORT , LCD_RS_PIN , HIGH );


		/* Send the Higher Nibble (4 Bits) of the Data */
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN0 , GET_BIT( data , 4 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN1 , GET_BIT( data , 5 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN2 , GET_BIT( data , 6 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN3 , GET_BIT( data , 7 ) );


		/* Set Enable Pin to High to Signal the LCD that Data is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT  , LCD_E_PIN  , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Data is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(10);

		/* Send the Lower Nibble (4 Bits) of the Data */
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN0 , GET_BIT( data , 0 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN1 , GET_BIT( data , 1 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN2 , GET_BIT( data , 2 ) );
		DIO_SetPinValue( LCD_DATA_PORT , LCD_DATA_PIN3 , GET_BIT( data , 3 ) );

		/* Set Enable Pin to High to Signal the LCD that Data is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Data is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(60);


	#elif LCD_MODE == LCD_8_BITS_MODE
		/* LCD 8 Bits Data mode */

		/* Set RS Pin to LOW for Data mode */
		DIO_SetPinValue( LCD_RS_PORT , LCD_RS_PIN , HIGH );

		/* Send the Data */
		DIO_SetPortValue( LCD_DATA_PORT , data );

		/* Set Enable Pin to High to Signal the LCD that Data is Ready to be Sent */
		DIO_SetPinValue( LCD_E_PORT  , LCD_E_PIN  , HIGH );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(10);

		/* Set Enable Pin to Low to Make a Falling Edge to Signal the LCD that Data is Sent */
		DIO_SetPinValue( LCD_E_PORT , LCD_E_PIN , LOW );

		/* Short Delay to Allow the LCD to Process the Received Data */
		_delay_us(60);

	#endif

}






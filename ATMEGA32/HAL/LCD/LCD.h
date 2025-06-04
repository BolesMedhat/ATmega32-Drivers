/****************************************************************************
 * @file    LCD.h
 * @author  Boles Medhat
 * @brief   LCD Driver Header File
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
 * The LCD driver includes the following functionalities:
 * - Initialization of LCD with configurable data/control pin mapping.
 * - Print characters, strings, and numbers.
 * - Cursor positioning and screen clearing.
 * - Custom character creation using CGRAM.
 * - Shift display left/right and get current cursor position.
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

#ifndef LCD_H_
#define LCD_H_

#include "LCD_config.h"
#include "../../MCAL/DIO/DIO.h"
#include "../../LIB/DataConvert/DataConvert.h"
#include <util/delay.h>


/*
 * @brief Initializes the LCD display based on configuration settings from LCD_config.h.
 *
 * This function sets the direction of the control and data pins, selects the LCD mode (4-bit or 8-bit),
 * and sends initialization commands to the LCD to configure it properly.
 */
void LCD_Init( void );


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
void LCD_PrintCharacter( char character );


/*
 * @brief Prints a string on the LCD starting at the current cursor position.
 *
 * This function iterates through each character of the provided string and
 * prints them one by one on the LCD.
 *
 * @param str: The string to be printed on the LCD. The string should be null-terminated.
 */
void LCD_PrintString( const char * str );


/*
 * @brief Prints a signed integer number on the LCD at the current cursor position.
 *
 * This function converts the given integer number to a string in base 10
 * and then prints it on the LCD starting at the current cursor position.
 *
 * @param number: The signed integer number to be printed on the LCD.
 */
void LCD_PrintNumber( sint32 number );


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
void LCD_SetCursor( uint8 row , uint8 col );


/*
 * @brief Clears the entire LCD screen and sets the cursor to the home position (0,0).
 *
 * This function clears the LCD display and resets the cursor position to the top-left corner
 * (row 0, column 0).
 */
void LCD_ClearScreen( void );


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
void LCD_SaveCustomChar( uint8 * custom_char_arr , uint8 CGRAM_address );


/*
 * @brief Returns the current row position of the cursor on the LCD.
 *
 * This function retrieves the current row where the cursor is positioned on the LCD screen.
 *
 * @return uint8 The current row (0 or 1) of the cursor on the LCD.
 */
uint8 LCD_GetRow( void );


/*
 * @brief Returns the current column position of the cursor on the LCD.
 *
 * This function retrieves the current column where the cursor is positioned on the LCD screen.
 *
 * @return uint8 The current column (0 to 15) of the cursor on the LCD.
 */
uint8 LCD_GetColumn( void );


/*
 * @brief Shifts the entire display content one position to the left.
 *
 * This function moves the content of the LCD display one position to the left.
 * It also adjusts the cursor position if necessary.
 */
void LCD_ShiftDisplayLeft( void );


/*
 * @brief Shifts the entire display content one position to the right.
 *
 * This function moves the content of the LCD display one position to the right. It also
 * adjusts the cursor position and handles automatic row movement based on the configuration.
 */
void LCD_ShiftDisplayRight( void );


/*
 * @brief Sends a command to the LCD to control its operation.
 *
 * This function sends a command byte to the LCD. The command can either be in 4-bit or 8-bit mode,
 * depending on the LCD configuration. The function sets the appropriate pins for the command,
 * and includes necessary delays for the LCD to process the command.
 *
 * @param command: The command byte to be sent to the LCD.
 */
void LCD_SendCommand( uint8 command );


/*
 * @brief Sends a data to the LCD to control its operation.
 *
 * This function sends a data byte to the LCD. The data can either be in 4-bit or 8-bit mode,
 * depending on the LCD configuration. The function sets the appropriate pins for the data,
 * and includes necessary delays for the LCD to process the data.
 *
 * @param data: The data byte to be sent to the LCD.
 */
void LCD_SendData( char data );


#endif /* LCD_H_ */

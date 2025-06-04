/****************************************************************************
 * @file    LCD_def.h
 * @author  Boles Medhat
 * @brief   LCD Definitions Header File
 * @version 2.0
 * @date    [2024-06-27]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains essential macros and definitions used by the LCD driver.
 * It includes instruction command codes, memory address mappings, and configuration
 * constants for various display modes and LCD sizes. These values are based on the
 * HD44780 LCD controller datasheet and are compatible with common LCD modules
 * such as 16x2 and 16x4.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef LCD_DEF_H_
#define LCD_DEF_H_


/*------------------------------------------   values    ----------------------------------------*/

/*LCD Commands*/
#define LCD_CLEAR_SCREEN					0x01	/*Clears the entire display and sets the cursor to the home position (top-left corner)*/
#define LCD_RETURN_TO_HOME					0x02	/*Returns the cursor to the home position (top-left corner) without clearing the display content*/

#define LCD_CURSOR_SHIFT_LEFT				0X04	/*Decrement cursor (shift to the left) without shifting display*/
#define LCD_CURSOR_SHIFT_RIGHT				0X06	/*Increment cursor (shift to the right) without shifting display*/

#define LCD_DISPLAY_OFF						0x08	/*Display off, cursor off, blink off*/
#define LCD_CURSOR_OFF						0x0C	/*Display on, cursor off, blink off*/
#define LCD_CURSOR_ON						0x0E	/*Display on, cursor on, blink off*/
#define LCD_CURSOR_BLINK					0x0F	/*Display on, cursor on, blink on*/

#define LCD_SHIFT_CURSOR_LEFT				0x10	/*Shift cursor left*/
#define LCD_SHIFT_CURSOR_RIGHT				0x14	/*Shift cursor right*/

#define LCD_SHIFT_DISPLAY_LEFT				0x18	/*Shift entire display left*/
#define LCD_SHIFT_DISPLAY_RIGHT				0x1C	/*Shift entire display right*/

#define LCD_4_BITS_MODE						0x28	/*4-bit interface, 2 lines, 5x8 dots*/
#define LCD_8_BITS_MODE						0x38	/*8-bit interface, 2 lines, 5x8 dots*/


/*LCD Memory Address*/
#define LCD_SET_DDRAM_ADDRESS				0x80	/*Starting address in DDRAM (Display Data RAM) for writing data (like characters) to the screen*/
#define LCD_SET_CGRAM_ADDRESS				0X40	/*Starting address in CGRAM (Character Generator RAM) for creating custom characters*/

/*LCD Rows Address*/
#define LCD_FIRST_ROW_ADDRESS				0x00	/*First  Row (Row 0) address*/
#define LCD_SECOND_ROW_ADDRESS				0x40	/*Second Row (Row 1) address*/
#define LCD_THIRD_ROW_ADDRESS				0x10	/*Third  Row (Row 2) address*/
#define LCD_FOURTH_ROW_ADDRESS				0x50	/*Fourth Row (Row 3) address*/

/*LCD Char Size*/
#define LCD_CHAR_SIZE						8		/*Number of bytes used in one LCD char (digit)*/

/*LCD Column Number*/
#define LCD_COLS_NUM						16		/*Number of columns in one LCD line*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*the Number of LCD Rows*/
#define LCD_2_ROWS							2		/*For LCD with 2 display rows (16x2)*/
#define LCD_4_ROWS							4		/*For LCD with 4 display rows (16x4)*/

/*the Automatic Move Mode*/
#define LCD_AUTO_MOVE_ROW_DISABLE			0		/*Do not move to the second row automatically*/
#define LCD_AUTO_MOVE_ROW_ENABLE			1		/*Automatically move to the second row When the first row ends (current column is number 16 in first row)*/
/*_______________________________________________________________________________________________*/


#endif /* LCD_DEF_H_ */

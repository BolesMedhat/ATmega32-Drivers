/****************************************************************************
 * @file    OLED.h
 * @author  Boles Medhat
 * @brief   OLED Driver Header File
 * @version 1.0
 * @date    [2025-03-06]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides an abstraction layer for controlling OLED displays
 * based on the SSD1306 controller using I2C communication protocol.
 * It includes initialization, command/data transmission, screen control,
 * and basic character printing functionalities.
 *
 * The OLED driver includes the following functionalities:
 * - OLED initialization and power control.
 * - Text rendering: characters, strings, and numbers.
 * - Cursor control with paging and column addressing.
 * - Scrolling capabilities: horizontal, vertical, and diagonal.
 * - Screen clearing and logic inversion.
 * - Low-level I2C command and data sending.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 * - Requires `EEPROM_I2C_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef OLED_H_
#define OLED_H_

#include "OLED_config.h"
#include "OLED_font.h"
#include "../../MCAL/I2C/I2C.h"
#include "../../LIB/DataConvert/DataConvert.h"


/*
 * @brief Initializes the OLED display module.
 *
 * This function configures the OLED display by sending initialization commands over I2C.
 */
void OLED_Init( void );


/*
 * @brief Turns on the OLED display.
 *
 * This function sends a command to power on the OLED display, making it active
 * and ready to show content.
 */
void OLED_DisplayON( void );


/*
 * @brief Turns off the OLED display.
 *
 * This function sends a command to power off the OLED display, putting it into
 * sleep mode to reduce power consumption.
 */
void OLED_DisplayOFF( void );


/*
 * @brief Inverts or restores the display colors.
 *
 * This function sets the display mode to either normal or inverse. In inverse mode,
 * pixels that are normally lit will be turned off, and pixels that are normally off
 * will be lit.
 *
 * @param invert: If `true`, the display is set to inverse mode. If `false`, it is set to normal mode.
 */
void OLED_LogicInvertDisplay( uint8 invert );


/*
 * @brief Sets the cursor position on the OLED display.
 *
 * This function updates the current page and column positions based on the selected
 * memory addressing mode.
 *
 * @param page:   The target page (row) for the cursor position (valid range: 0 to OLED_TOTAL_PAGES - 1).
 * @param colunm: The target column for the cursor position (valid range: 0 to OLED_TOTAL_COLS - 1).
 */
void OLED_SetCursor( uint8 page , uint8 col );


/*
 * @brief Moves the cursor to the next line (page) on the OLED display.
 *
 * This function increments the current page and resets the column to the first position.
 * If the cursor is on the last page, it wraps around to the first page.
 */
void OLED_GoToNextLine( void );


/*
 * @brief Clears the OLED display by writing zeros to all pixels.
 *
 * This function turns off the display, writing zeros to all pixels,
 * and Finally, it turns the display back on.
 */
void OLED_ClearScreen( void );


/*
 * @brief Deactivates any active scrolling on the OLED display.
 *
 * This function stops the scrolling effect if it is enabled,
 * ensuring the display remains static.
 */
void OLED_DeactiveScrolling( void );


/*
 * @brief Activates scrolling on the OLED display.
 *
 * This function enables scrolling based on the previously configured
 * scrolling parameters.
 */
void OLED_ActiveScrolling( void );


/*
 * @brief Configures and starts horizontal scrolling on the OLED display.
 *
 * This function sets up horizontal scrolling in the specified direction
 * between the given start and end pages at the defined speed.
 * It first deactivates any existing scrolling before applying new settings.
 *
 * @param direction:    The scroll direction (OLED_RIGHT_SCROLL or OLED_LEFT_SCROLL).
 * @param start_page:   The starting page for scrolling (valid values: 0 to 7).
 * @param end_page:     The ending page for scrolling (valid values: 0 to 7, must be greater than start_page).
 * @param scroll_speed: The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 */
void OLED_ScrollHorizontal( uint8 direction , uint8 start_page , uint8 end_page , uint8 scroll_speed );


/*
 * @brief Initiates vertical scrolling on the OLED display.
 *
 * This function scrolls the content vertically by a specified offset.
 * It utilizes the `OLED_Scroll` function with a predefined horizontal scroll setting.
 *
 * @param scroll_speed:    The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 * @param vertical_offset: The number of vertical rows to scroll per step (valid values: 0-63).
 */
void OLED_ScrollVertical( uint8 scroll_speed, uint8 vertical_offset );


/*
 * @brief Configures and starts diagonal scrolling on the OLED display.
 *
 * This function sets up diagonal scrolling by combining horizontal and vertical movements.
 * It first deactivates any existing scrolling before applying new settings.
 *
 * @param direction:       The scroll direction (OLED_RIGHT_SCROLL or OLED_LEFT_SCROLL).
 * @param start_page:      The starting page for scrolling (valid values: 0 to 7).
 * @param end_page:        The ending page for scrolling (valid values: 0 to 7, must be greater than or equal to start_page).
 * @param scroll_speed:    The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 * @param vertical_offset: The number of vertical rows to scroll per step (valid values: 0-63).
 */
void OLED_Scroll( uint8 direction , uint8 start_page, uint8 end_page, uint8 scroll_speed, uint8 vertical_offset );


/*
 * @brief Sends a command to the OLED display without restarting communication.
 *
 * This function writes a command to the OLED display in a continued sequence without
 * sending a start condition, slave address, or stop condition. It is typically used
 * when multiple commands need to be sent within an active I2C communication session.
 *
 * @param command: The command byte to be sent to the OLED display.
 */
void I2C_WriteOLEDCommand( uint8 command );


/*
 * @brief Sends a single command to the OLED display.
 *
 * This function initiates an I2C communication sequence, sends a command to the OLED display,
 * and then stops communication. It is used for standalone command transmissions.
 *
 * @param command: The command byte to be sent to the OLED display.
 */
void OLED_WriteCommand( uint8 command );


/*
 * @brief Prints a single character on the OLED display at the current cursor position.
 *
 * This function retrieves the character's font data from program memory (PROGMEM)
 * and writes it to the display. If the character is '\n' or if there is not enough
 * space on the current line, it moves to the next line before printing.
 *
 * @param character: The ASCII character to be printed.
 */
void OLED_PrintCharacter( uint8 character );


/*
 * @brief Prints a null-terminated string on the OLED display.
 *
 * This function iterates through each character in the provided string
 * and prints.
 *
 * @param Str: Pointer to the null-terminated string to be displayed.
 */
void OLED_PrintString( const char * Str );


/*
 * @brief Prints an integer number on the OLED display.
 *
 * This function prints the given integer number on the OLED display.
 * If the number does not fit in the current line, it moves to the next line before printing.
 *
 * @param Number: The integer value to be displayed.
 */
void OLED_PrintNumber( sint32 Number );


/*
 * @brief Sends a single byte of data to the OLED display.
 *
 * This function writes a raw byte to the OLED display, which can be used
 * for direct data transfer, such as drawing custom graphics or sending
 * raw pixel data.
 *
 * @param byte: The byte value to be sent to the display.
 */
void OLED_PrintByte( uint8 byte );


/*
 * @brief Retrieves the current page position of the cursor on the OLED display.
 *
 * This function returns the current page where the cursor is positioned.
 *
 * @return: The current page position (0-7).
 */
uint8 OLED_GetPage( void );


/*
 * @brief Retrieves the current column position of the cursor on the OLED display.
 *
 * This function returns the current column where the cursor is positioned.
 *
 * @return: The current column position (0-127).
 */
uint8 OLED_GetColumn( void );


#endif /* OLED_H_ */

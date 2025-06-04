/****************************************************************************
 * @file    LCD_config.h
 * @author  Boles Medhat
 * @brief   LCD Driver Configuration Header File
 * @version 2.0
 * @date    [2024-06-27]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the LCD driver.
 * It allows the user to define the LCD's operational mode, pin connections,
 * cursor behavior, and auto row movement features. Adjusting these settings
 * tailors the driver to specific hardware configurations and display preferences.
 *
 * @note
 * - All available choices are defined in `LCD_def.h` and explained with comments there.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "LCD_def.h"


/*Set number rows in the LCD
 * choose between:
 * 1. LCD_2_ROWS							<--the most used
 * 2. LCD_4_ROWS
 */
#define LCD_NUMBER_OF_ROWS					LCD_2_ROWS


/*Set number of data bits mode
 * choose between:
 * 1. LCD_4_BITS_MODE						<--the most used
 * 2. LCD_8_BITS_MODE
 */
#define LCD_MODE							LCD_4_BITS_MODE



/*Set the DIO Port For the LCD RS Pin
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define LCD_RS_PORT							DIO_PORTC


/*Set the DIO Pin For the LCD RS Pin
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
#define LCD_RS_PIN							DIO_PIN0



/*Set the DIO Port For the LCD E Pin
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define LCD_E_PORT							DIO_PORTC


/*Set the DIO Pin For the LCD E Pin
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
#define LCD_E_PIN							DIO_PIN1



/*Set the DIO Port For the LCD Data Pins
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define LCD_DATA_PORT						DIO_PORTC


/*Set the DIO Pin For the LCD Data Pins
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
#if (LCD_MODE == LCD_4_BITS_MODE)
#define LCD_DATA_PIN0						DIO_PIN2
#define LCD_DATA_PIN1						DIO_PIN3
#define LCD_DATA_PIN2						DIO_PIN4
#define LCD_DATA_PIN3						DIO_PIN5
#endif



/*Set the LCD Cursor Status
 * choose between:
 * 1. LCD_CURSOR_OFF						<--the most used
 * 2. LCD_CURSOR_ON
 * 3. LCD_CURSOR_BLINK
 */
#define LCD_CURSOR_STATUS					LCD_CURSOR_OFF



/*Set the Automatic Move Mode
 * Choose between:
 * 1. LCD_AUTO_MOVE_ROW_DISABLE				<--the default
 * 2. LCD_AUTO_MOVE_ROW_ENABLE
 */
#define LCD_AUTO_MOVE_MODE					LCD_AUTO_MOVE_ROW_DISABLE


#endif /* LCD_CONFIG_H_ */

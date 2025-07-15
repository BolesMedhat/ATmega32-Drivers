/****************************************************************************
 * @file    OLED_config.h
 * @author  Boles Medhat
 * @brief   OLED Configuration Header File
 * @version 1.0
 * @date    [2025-03-06]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file contains configuration options for the SSD1306 controller via I2C.
 * It allows for setting up various parameters such as Clock divider,
 * oscillator frequency settings, Clock divider Multiplex ratio, display offset,
 * start row settings, Display contrast, memory addressing mode, scan direction,
 * Segment and COM remapping options, and Display mode.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 * - All available choices are defined in `OLED_def.h` and explained with comments there.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef OLED_CONFIG_H_
#define OLED_CONFIG_H_

#include "OLED_def.h"


/* Set the Clock Divider Value (valid range: 0x00 - 0x0F) */
#define OLED_CLK_DIVIDER					0x00	//<--the most used 0x00


/* Set the Oscillator Frequency Value (valid range: 0x00 - 0x0F) */
#define OLED_OSCIL_FREQ						0x08	//<--the most used 0x08



/* Set the Multiplex Ratio (valid values: 15 - 63) */
#define OLED_MUX_VALUE						0x3F	//<--the most used 0x3F



/* Set the Display Offset (valid range: 0x00 - 0x3F) */
#define OLED_ROWS_OFFSET					0x00	//<--the most used 0x00


/* Set the Display Start Line Offset (valid range: 0x00 - 0x3F) */
#define OLED_START_ROW_OFFSET				0x00	//<--the most used 0x00



/* Set the Display Contrast Value (valid range: 0x00 - 0xFF) */
#define OLED_CONTRAST_VALUE					0x7F	//<--the most used 0x7F


/* Set the Memory Addressing Mode
 * choose between:
 * 1. OLED_MEMORY_MODE_HORIZONTAL					<--the most used
 * 2. OLED_MEMORY_MODE_VERTICAL
 * 3. OLED_MEMORY_MODE_PAGE
 */
#define OLED_MEMORY_MODE					OLED_MEMORY_MODE_HORIZONTAL



/* Set Segment (column) Re-map
 * choose between:
 * 1. OLED_SEG_REMAP_NORMAL
 * 2. OLED_SEG_REMAP_REVERSE						<--the most used
*/
#define OLED_SEG_REMAP						OLED_SEG_REMAP_REVERSE


/* Set COM (row) Re-map
 * choose between:
 * 1. OLED_COM_REMAP_NORMAL
 * 2. OLED_COM_REMAP_REVERSE						<--the most used
*/
#define OLED_COM_REMAP						OLED_COM_REMAP_REVERSE



/* Set the Display Mode
 * choose between:
 * 1. OLED_NORMAL_DISPLAY							<--the most used
 * 2. OLED_INVERT_DISPLAY
*/
#define OLED_DISPALY_MODE					OLED_NORMAL_DISPALY



/* You must initialize I2C manually "I2C_Init()" before using this driver */
#ifndef I2C_IN_HAL
#define I2C_IN_HAL
	#warning "⚠️ Initialize I2C manually before using this driver."
#endif



/* Enable I2C overflow interrupt */
#if I2C_INT_STATUS != I2C_INT_DISABLE
	#warning "⚠️ Disable I2C interrupt."
#endif



/* Error checking for invalid configurations */
#if	( OLED_CLK_DIVIDER > OLED_LAST_ROW ) || ( OLED_OSCIL_FREQ > 0x0F)
	#error "the OLED_CLK_DIVIDER or OLED_OSCIL_FREQ value not in range"
#else
	#define OLED_CLK_DIV_OSCI_FREQ			(OLED_OSCIL_FREQ << 4) | (OLED_CLK_DIVIDER)
#endif

#if ( OLED_MUX_VALUE > OLED_LAST_ROW ) ||  ( OLED_MUX_VALUE < 15 )
	#error "the Multiplex Ratio value not in range"
#endif

#endif /* OLED_CONFIG_H_ */

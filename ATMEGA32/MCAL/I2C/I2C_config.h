/****************************************************************************
 * @file    I2C_config.h
 * @author  Boles Medhat
 * @brief   I2C (TWI) Configuration File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-06]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the I2C (TWI) driver for ATmega32
 * microcontroller. It allows for setting up various parameters such as clock frequency,
 * interrupt behavior, general call handling, internal pull-up usage, and device address.
 *
 * @note
 * - All available choices (e.g., clock sources, modes, output settings) are
 *   defined in `I2C_def.h` and explained with comments there.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include "I2C_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*Set I2C Clock Frequency in Master Mode
 * choose between:
 * 1. 100000UL
 * 2. 400000UL
 * 3. any other value
 */
#define I2C_SCL_CLOCK_FREQUENCY  			400000UL



/*Set the I2C module Address*/
#define I2C_MODULE_ADDRESS					0x01



/*Set the I2C Interrupt Status
 * choose between:
 * 1. I2C_INT_DISABLE
 * 2. I2C_INT_ENABLE
 */
#define I2C_INT_STATUS						I2C_INT_DISABLE



/*Set the I2C general call Status
 * choose between:
 * 1. I2C_GENERAL_CALL_DISABLE
 * 2. I2C_GENERAL_CALL_ENABLE
 */
#define I2C_GENERAL_CALL_STATUS				I2C_GENERAL_CALL_ENABLE



/*Set the I2C Internal pull-up Status
 * choose between:
 * 1. I2C_INTERNAL_PULLUP_DISABLE			<--the most used
 * 2. I2C_INTERNAL_PULLUP_ENABLE
 */
#define I2C_INTERNAL_PULLUP_STATUS			I2C_INTERNAL_PULLUP_ENABLE



/*the I2C prescaler Set Automatically*/
#if		(((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 1)) < 256 && (((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 1)) >= 0

	#define I2C_PRESCALER				I2C_PRESCALER_1

#elif	(((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 4)) < 256 && (((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 4)) >= 0

	#define I2C_PRESCALER				I2C_PRESCALER_4

#elif	(((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 16)) < 256 && (((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 16)) >= 0

	#define I2C_PRESCALER				I2C_PRESCALER_16

#elif	(((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 64)) < 256 && (((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / (2 * 64)) >= 0

	#define I2C_PRESCALER				I2C_PRESCALER_64

#else
	#error "No valid I2C_PRESCALER found!"
#endif


#endif /* I2C_CONFIG_H_ */

/******************************************************************************
 * @file    SPI_config.h
 * @author  Boles Medhat
 * @brief   SPI Driver Configuration Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the SPI driver for the ATmega32
 * microcontroller. It allows the user to configure various SPI settings including
 * clock rate, data order, clock polarity, phase, and interrupt handling.
 *
 * @note
 * - All available choices (e.g., clock rate, data order, clock polarity) are
 *   defined in `SPI_def.h` and explained with comments there.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

#include "SPI_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*The Value that Will Transmit When you Want to Receive Only*/
#define SPI_DEFAULT_TRANSMIT_DATA			0xFF


/*Set the SPI Clock Rate
 * choose between:
 * 1. SPI_FREQ_DIVIDED_BY_2					//HINT: Do not use with Slave AVR
 * 2. SPI_FREQ_DIVIDED_BY_4
 * 3. SPI_FREQ_DIVIDED_BY_8
 * 4. SPI_FREQ_DIVIDED_BY_16
 * 5. SPI_FREQ_DIVIDED_BY_32
 * 6. SPI_FREQ_DIVIDED_BY_64
 * 7. SPI_FREQ_DIVIDED_BY_128
 */
#define SPI_CLOCK_RATE						SPI_FREQ_DIVIDED_BY_16



/*Set the SPI Mode
 * choose between:
 * 1. SPI_SLAVE
 * 2. SPI_MASTER
 */
#define SPI_MODE							SPI_MASTER



/*Set the SPI Data Order
 * choose between:
 * 1. SPI_MSB_FIRST							<--the most used
 * 2. SPI_LSB_FIRST
 */
#define SPI_DATA_ORDER						SPI_MSB_FIRST



/*Set the SPI Clock Polarity
 * choose between:
 * 1. SPI_LEADING_RISING					<--the most used
 * 2. SPI_LEADING_FALLING
 */
#define SPI_CLOCK_POLARITY					SPI_LEADING_RISING



/*Set the SPI Clock Phase
 * choose between:
 * 1. SPI_LEADING_SAMPLE					<--the most used
 * 2. SPI_LEADING_SETUP
 */
#define SPI_CLOCK_PHASE						SPI_LEADING_SAMPLE



/*Set the SPI Interrupt Status
 * choose between:
 * 1. SPI_INT_DISABLE
 * 2. SPI_INT_ENABLE
 */
#define SPI_INT_STATUS						SPI_INT_DISABLE



/*Max Time to Waiting for the Transfer to Finish
 * choose between:
 * 1. SPI_WAIT_FOREVER						<--recommended
 * 2. any number (for example 10000)
 */
#define  SPI_COUNTOUT						SPI_WAIT_FOREVER


#endif /* SPI_CONFIG_H_ */

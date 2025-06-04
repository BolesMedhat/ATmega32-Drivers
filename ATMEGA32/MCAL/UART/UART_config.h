/******************************************************************************
 * @file    UART_config.h
 * @author  Boles Medhat
 * @brief   UART Driver Configuration Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-1]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the UART driver for ATmega32
 * microcontroller. It allows for setting up various parameters such as
 * baud rate, parity mode, stop bits, character size, UART operation mode,
 * and interrupt enable/disable control.
 *
 * @note
 * - All available choices (e.g., baud rate, parity mode, stop bits) are
 *   defined in `UART_def.h` and explained with comments there.
 * - Refer to datasheet page 163 (Table 68) for baud rate settings.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#include  "UART_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*Hint : check table in 68 page 163 in data sheet*/
/*Set Baud Rate
 * choose between:
 * 1. UART_BAUD_RATE_2400
 * 2. UART_BAUD_RATE_4800
 * 3. UART_BAUD_RATE_9600					<--the most used
 * 4. UART_BAUD_RATE_14400
 * 5. UART_BAUD_RATE_19200
 * 6. UART_BAUD_RATE_28800
 * 7. UART_BAUD_RATE_38400
 * 8. UART_BAUD_RATE_57600
 * 9. UART_BAUD_RATE_76800
 * 10.UART_BAUD_RATE_115200
 * 11.UART_BAUD_RATE_230400
 */
#define UART_BAUD_RATE						UART_BAUD_RATE_9600


/*Set Parity Mode
 *  choose between:
 * 1. UART_PARITY_DISABLE					<--the most used
 * 2. UART_PARITY_EVEN
 * 3. UART_PARITY_ODD
 */
#define UART_PARITY_MODE					UART_PARITY_DISABLE


/*Set Stop Bit Mode
 *  choose between:
 * 1. UART_1_STOP_BIT						<--the most used
 * 2. UART_2_STOP_BIT
 */
#define UART_STOP_BIT						UART_1_STOP_BIT


/*Set Character Size
 *  choose between:
 * 1. UART_DATA_5_BIT_SIZE
 * 2. UART_DATA_6_BIT_SIZE
 * 3. UART_DATA_7_BIT_SIZE
 * 4. UART_DATA_8_BIT_SIZE					<--the most used
 * 5. UART_DATA_9_BIT_SIZE
 */
#define UART_DATA_SIZE						UART_DATA_8_BIT_SIZE


/*Set Receiver Enable
 * choose between:
 * 1. UART_DISABLE
 * 2. UART_ENABLE							<--the most used
 */
#define UART_RECEIVER_ENABLE				UART_ENABLE


/*Set Transmitter Enable
 * choose between:
 * 1. UART_DISABLE
 * 2. UART_ENABLE							<--the most used
 */
#define UART_TRANSMITTER_ENABLE				UART_ENABLE


/*Set Double the UART Transmission Speed effect with ASYNCHRONOUS mode only
 *  choose between:
 * 1. UART_U2X_DISABLE						<--the most used
 * 2. UART_U2X_ENABLE
 */
#define UART_U2X_MODE						UART_U2X_DISABLE


/*Set TX Complete Interrupt Status
 * choose between:
 * 1. UART_INT_DISABLE						<--the most used
 * 2. UART_INT_ENABLE
 */
#define UART_TX_INTERRUPT					UART_INT_DISABLE


/*Set RX Complete Interrupt Status
 * choose between:
 * 1. UART_INT_DISABLE						<--the most used
 * 2. UART_INT_ENABLE
 */
#define UART_RX_INTERRUPT					UART_INT_DISABLE


/*Set UDR Empty Interrupt Status
 * choose between:
 * 1. UART_INT_DISABLE						<--the most used
 * 2. UART_INT_ENABLE
 */
#define UART_UDR_INTERRUPT					UART_INT_DISABLE


/*Max Time to Waiting for the read to Finish
 * choose between:
 * 1. UART_WAIT_FOREVER
 * 2. any number (for example 200)
 */
#define  UART_COUNTOUT						UART_WAIT_FOREVER


/*value that return if timeout happens */
#define UART_TIMEOUT_BYTE 					'?'


#endif /* UART_CONFIG_H_ */

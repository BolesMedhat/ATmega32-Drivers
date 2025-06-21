/******************************************************************************
 * @file    UART.h
 * @author  Boles Medhat
 * @brief   UART Driver Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-1]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for the Universal Asynchronous
 * Receiver Transmitter (UART) in ATmega32 microcontroller. It enables full-duplex
 * communication with features including configurable baud rate, frame format
 * (data bits, stop bits, parity), polling and interrupt-based transmission,
 * timeout handling, and 9-bit data support.
 *
 * The UART driver includes the following functionalities:
 * - Initialization with configurable parameters via `UART_config.h`.
 * - Send and receive bytes, strings, and arrays.
 * - Timeout and stop byte-based reception control.
 * - Interrupt control and callback registration for TX and RX events.
 * - 9-bit data transmission and reception support.
 * - Error status checking (frame, overrun, and parity).
 * - Utility functions for checking data availability.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `UART_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "UART_config.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/DataConvert/DataConvert.h"


/*
 * @brief Initialize the UART peripheral based on configuration options.
 *
 * This function configures the UART module based on the defined macros
 * in the configuration file. It sets the baud rate, parity, stop bits,
 * data size, transmission speed mode, and enables/disables receiver,
 * transmitter, and interrupts as required.
 * It configures the UART registers according to the defined macros in `UART_config.h`.
 *
 * @see `UART_config.h` for configuration options.
 */
void UART_Init( void );


/*
 * @brief Disable the specified UART interrupt.
 *
 * This function disables a specific UART interrupt based on the provided ID.
 *
 * @param interrupt_id: Interrupt ID to disable. Options:
 *        - UART_INT_TX_ID: TX Complete Interrupt
 *        - UART_INT_RX_ID: RX Complete Interrupt
 *        - UART_INT_UDR_ID: UDR Empty Interrupt
 */
void UART_InterruptDisable( uint8 interrupt_id );


/**
 * @brief Enable the specified UART interrupt.
 *
 * This function enables a specific UART interrupt based on the provided ID.
 *
 * @param interrupt_id: Interrupt ID to enable. Options:
 *        - UART_INT_TX_ID: TX Complete Interrupt
 *        - UART_INT_RX_ID: RX Complete Interrupt
 *        - UART_INT_UDR_ID: UDR Empty Interrupt
 */
void UART_InterruptEnable( uint8 interrupt_id );


/*
 * @brief Transmit a single byte over UART.
 *
 * This function waits for the UART data register to be ready and then sends
 * the given byte. If timeout is configured, it waits up
 * to the timeout duration before aborting the transmission.
 *
 * @param byte: The btye to be transmitted.
 */
void UART_WriteByte( uint8 byte );


/*
 * @brief Transmit arrays of bytes over UART.
 *
 * This function transmits each byte from the `TX_Array`.
 *
 * @param TX_Array:	 Pointer to the array of data to transmit.
 * @param ArraySize: Number of bytes to write.
 */
void UART_WriteArray( const uint8 * TX_Array , uint16 ArraySize );


/*
 * @brief Transmit a null-terminated string over UART.
 *
 * Sends each character in the provided string one by one
 * until the null terminator '\0' is encountered. Also sends the
 * null terminator to indicate the end of the string.
 *
 * @param TX_String: Pointer to the string to be sent.
 */
void UART_WriteString( const char * TX_String );


/*
 * @brief Send an integer number over UART.
 *
 * This function converts the given integer into a string and sends it
 * using the UART_SendString function.
 *
 * @param number: The integer number to send.
 */
void UART_WriteNumber( sint32 number );


/*
 * @brief receives one byte from the UART.
 *
 * This function waits for a byte to be received through UART. If the wait time exceeds
 * the `UART_COUNTOUT` value (when defined), it returns a timeout character `UART_TIMEOUT_BYTE`.
 * If `UART_COUNTOUT` is set to `UART_WAIT_FOREVER`, it waits indefinitely.
 *
 * @return (uint8) Received byte, or `UART_TIMEOUT_BYTE` if no data received within timeout period.
 */
uint8 UART_ReadByte( void );


/*
 * @brief receive arrays of bytes from the UART.
 *
 * This function receives each byte and stores them in the `RX_String`.
 *
 * @param RX_Array:  Pointer to the buffer where the received string is stored.
 * @param ArraySize: Number of bytes to read.
 */
void UART_ReadArray( uint8 * RX_Array , uint16 ArraySize );


/*
 * @brief receive string from the UART until a null terminator is received.
 *
 * This function receives characters and stores them in the provided buffer
 * until the received byte is a null terminator `\0`.
 *
 * @param String_pointer: Pointer to the buffer where the received string is stored.
 */
void UART_ReadString( char * RX_String );


/*
 * @brief receive string from the UART until a specific stop byte or null terminator is received.
 *
 * This function keeps receives characters from UART and storing them in the provided buffer
 * until it encounters the specified `stop_Byte` or a null terminator `\0`.
 *
 * @param RX_String: Pointer to the buffer where the received string is stored.
 * @param Stop_Byte: character to stop reading when encountered.
 */
void UART_ReadStringUntil( char * RX_String , uint8 Stop_Byte );


/*
 * @brief Checks if data is available to read from UART.
 *
 * This function checks if there data received and ready to read.
 *
 * @return (uint8) 1 if data is available, 0 otherwise.
 */
uint8 UART_IsAvailableToRead( void );


/*
 * @brief Checks UART status flags for errors.
 *
 * This function returns the bits related to errors (Frame Error, Data Overrun, Parity Error)
 * from the UCSRA register.
 *
 * @return (uint8) Bitmask of error flags from UCSRA (bits 4, 3, 2).
 */
uint8 UART_CheckErrors( void );


/*
 * @brief Writes the 9th bit in UART 9-bit mode.
 *
 * This function sets or clears the TXB8 bit in UCSRB register to transmit the 9th data bit.
 * It must be called **before** writing the lower 8 bits to the UDR register.
 *
 * @param NinthBit: The value of the 9th bit to send (use HIGH or LOW).
 */
void UART_WritetheNinthBit( uint8 NinthBit );


/*
 * @brief Reads the 9th bit received in UART 9-bit mode.
 *
 * This function reads the RXB8 bit from the UCSRB register, which represents
 * the 9th bit of received data. It must be called **before** reading the lower 8 bits from UDR.
 *
 * @return (uint8) Value of the received 9th bit (0 or 1).
 */
uint8 UART_ReadtheNinthBit( void );


/*
 * @brief Sets a callback function for a UART TX (Transmit) interrupt and start sending a data.
 *
 * This function sets a user-defined callback function to be called
 * when the UART transmission is complete.
 * It also loads the first byte to start transmission and initializes internal buffers.
 *
 * @example UART_Set_TX_Callback( TX_Interrupt_Function , TX_String , TX_StringLength );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 							void return type and no parameters.
 * @param TX_Array:		Pointer to the array to transmit.
 * @param TX_ArraySize: Size of the data array.
 */
void UART_Set_TX_Callback ( void (*CopyFuncPtr)(void) , uint8 * TX_Array , uint16 TX_ArraySize );


/*
 * @brief Sets a callback function for a UART RX (Receive) interrupt and start sending a data.
 *
 * This function sets a user-defined callback function to be called
 * when the UART reception is complete (by size) or a stop byte is received.
 * It also stores a buffer to hold received data and store the stop byte that terminates reception.
 *
 * @example UART_Set_RX_Callback( RX_Interrupt_Function , RX_String , 100 , '\0' );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 							void return type and no parameters.
 * @param RX_Array    : Pointer to the buffer where received data will be stored.
 * @param RX_ArraySize: Maximum size of the receive buffer.
 * @param Stop_Byte   : Byte that indicates the end of reception.
 */
void UART_Set_RX_Callback ( void (*CopyFuncPtr)(void) , uint8 * RX_Array , uint16 RX_ArraySize , uint8 Stop_Byte );


#endif /* UART_H_ */

/******************************************************************************
 * @file    SPI.h
 * @author  Boles Medhat
 * @brief   SPI Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file implements the SPI (Serial Peripheral Interface) driver for the
 * ATmega32 microcontroller. The driver supports both master and slave modes,
 * and it allows full-duplex, interrupt-driven communication.
 *
 * The SPI driver includes the following functionalities:
 * - SPI initialization with configurable options.
 * - Functions for transmitting and receiving single bytes or arrays.
 * - Support for interrupt-driven communication with user-defined callback functions.
 * - Timeout management for transfers when configured.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `SPI_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "../../LIB/BIT_MATH.h"
#include "SPI_config.h"


/*
 * @brief Initialize the SPI peripheral based on configuration options.
 *
 * This function configures the SPI as Master or Slave, data order,
 * clock polarity, clock phase, interrupt settings, and clock rate,
 * and sets the appropriate pin directions (MISO, MOSI, SCK, SS) on PORTB.
 * It configures the SPI registers according to the defined macros in `SPI_config.h`.
 *
 * @see `SPI_config.h` for configuration options.
 */
void SPI_Init( void );


/*
 * @brief Disable SPI interrupt.
 *
 * This function disables the SPI interrupt by clearing the SPIE bit in the SPCR register.
 */
void SPI_InterruptDisable( void );


/*
 * @brief Enable SPI interrupt.
 *
 * This function enables the SPI interrupt by setting the SPIE bit in the SPCR register.
 */
void SPI_InterruptEnable( void );


/*
 * @brief Transmit a single byte over SPI and receive a byte simultaneously.
 *
 * This function sends the specified byte and waits until transmission is complete.
 * If a timeout counter is enabled (SPI_COUNTOUT != SPI_WAIT_FOREVER),
 * the function will return 0xFF if the transfer fails.
 *
 * @param TX_Byte: Byte to send.
 * @return (uint8) Received byte. Returns 0xFF if the transfer times out.
 */
uint8 SPI_TransferByte( uint8 TX_Byte );


/*
 * @brief Transmit a single byte over SPI.
 *
 * This function only sends the specified byte and waits until transmission is complete (no return value).
 *
 * @param TX_Byte: Byte to transmit.
 */
void SPI_TransmitByte( uint8 TX_Byte );


/*
 * @brief Receive a single byte over SPI.
 *
 * This function receiving data and sends a default transmit value.
 * If a timeout counter is enabled (SPI_COUNTOUT != SPI_WAIT_FOREVER),
 * the function will return 0xFF if the transfer fails.
 *
 * @return (uint8) Received byte. Returns 0xFF if the transfer times out.
 */
uint8 SPI_ReceiveByte( void );


/*
 * @brief Transmit and receive arrays of bytes simultaneously over SPI.
 *
 * This function transmits each byte from the `TX_Array`
 * and stores the received bytes in the `RX_Array` (Full-duplex communication).
 *
 * @param TX_Array:	Pointer to the array of data to transmit.
 * @param RX_Array:	Pointer to the array to store received data.
 * @param ArraySize:			Number of bytes to transmit/receive.
 */
void SPI_TransferArray( const uint8 * TX_Array , uint8 * RX_Array , uint16 ArraySize );


/*
 * @brief Transmit arrays of bytes over SPI.
 *
 * This function transmits each byte from the `TX_Array`.
 *
 * @param TX_Array:	Pointer to the array of data to transmit.
 * @param ArraySize:			Number of bytes to transmit.
 */
void SPI_TransmitArray( const uint8 * TX_Array , uint16 ArraySize );


/*
 * @brief Receive arrays of bytes over SPI.
 *
 * This function Stores the received bytes in the `RX_Array`
 * and sends default values.
 *
 * @param RX_Array:	Pointer to the array to store received data.
 * @param ArraySize:			Number of bytes to receive.
 */
void SPI_ReceiveArray( uint8 * RX_Array , uint16 ArraySize );


/*
 * @brief Set the SPI callback function and start interrupt-driven transfer.
 *
 * Initializes internal pointers and index counters to support interrupt-driven
 * SPI data transfer. The user-provided callback function will be called upon completion.
 *
 *@example SPI_SetCallback( SPI_Interrupt_Function , TransmitArray , ReceiveArray , ArraySize );
 *
 * @param CopyFuncPtr:			Pointer to the callback function. The function should have a
 * 								void return type and no parameters.
 * @param TX_Array: Pointer to data array to transmit (NULL if not used).
 * @param RX_Array:	Pointer to data array to store received data (NULL if not used).
 * @param ArraySize:			Size of the data arrays.
 */
void SPI_SetCallback( void (*CopyFuncPtr)(void) , uint8 * TX_Array , uint8 * RX_Array , uint16 ArraySize );


#endif /* SPI_H_ */

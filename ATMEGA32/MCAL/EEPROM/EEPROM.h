/****************************************************************************
 * @file    EEPROM.h
 * @author  Boles Medhat
 * @brief   EEPROM Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-03]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides functions to interact with the EEPROM of ATmega32 microcontroller.
 * It supports both synchronous and interrupt-driven operations for reading and writing
 * single bytes, arrays, 16-bit and 32-bit integers, and 32-bit floating point values.
 * Additionally, this driver includes interrupt support with a callback mechanism for
 * handling EEPROM operations asynchronously.
 *
 * The EEPROM driver includes the following functionalities:
 * - Write/Read a single byte.
 * - Write/Read an array of bytes.
 * - Write/Read 16-bit and 32-bit integers.
 * - Write/Read 32-bit floating-point values.
 * - EEPROM interrupt enable/disable.
 * - User-defined interrupt callback handler.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "../../LIB/BIT_MATH.h"
#include "EEPROM_def.h"


/*
 * @brief Write a byte of data to the specified EEPROM address.
 *
 * This function writes one byte of data to the EEPROM. It waits for the previous
 * write operation to complete before proceeding.
 *
 * @param address: The EEPROM address where the byte will be written (0-1023).
 * @param data:    The data byte to be written to the EEPROM.
 */
void EEPROM_WriteByte( uint16 address , uint8 data );


/*
 * @brief Read a byte of data from the specified EEPROM address.
 *
 * This function reads one byte of data from the EEPROM. It waits for the previous
 * write operation to complete before proceeding.
 *
 * @param address: The EEPROM address from which the byte will be read (0-1023).
 *
 * @return (uint8) data read from the specified EEPROM address. If the
 * 			address is invalid, the function returns 0.
 */
uint8 EEPROM_ReadByte( uint16 address );


/*
 * @brief Writes an array of bytes to EEPROM.
 *
 * This function writes `array_size` number of bytes from the provided array to
 * EEPROM starting at the specified address.
 *
 * @param address:    Start EEPROM address to write to.
 * @param data_array: Pointer to the array of bytes to write.
 * @param array_size:  Number of bytes to write.
 */
void EEPROM_WriteArray( uint16 address , const uint8 * data_array , uint8 array_size );


/*
 * @brief Reads an array of bytes from EEPROM.
 *
 * This function reads `array_size` number of bytes from EEPROM starting at
 * the specified address and stores them in the provided array.
 *
 * @param address:    Start EEPROM address to read from.
 * @param data_array: Pointer to the array to store read data.
 * @param array_size:  Number of bytes to read.
 */
void EEPROM_ReadArray( uint16 address , uint8 * data_array , uint8 array_size );


/*
 * @brief Writes a 16-bit integer (signed or unsigned) to EEPROM.
 *
 * This function splits the 16-bit data into 2 bytes and writes them
 * sequentially starting from the specified EEPROM address. It achieves this
 * by casting the data pointer to a byte pointer and iterating over each byte.
 *
 * @param address: EEPROM address where the data will be stored.
 * @param data:    16-bit integer (signed or unsigned) to be written.
 */
void EEPROM_WriteInt16(uint16 address, uint16 data);


/*
 * @brief Reads a 16-bit integer (signed or unsigned) from EEPROM.
 *
 * This function reads 2 bytes from the specified EEPROM address sequentially
 * and reconstructs the 16-bit integer by copying the bytes into the provided
 * variable. It achieves this by casting the data pointer to a byte pointer
 * and reading each byte sequentially from EEPROM.
 *
 * @param address: EEPROM address from which the data will be read.
 * @return 16-bit integer (signed or unsigned) read from EEPROM.
 */
uint16 EEPROM_ReadInt16(uint16 address);


/*
 * @brief Writes a 32-bit integer (signed or unsigned) to EEPROM.
 *
 * This function splits the 32-bit data into 4 bytes and writes them
 * sequentially starting from the specified EEPROM address. It achieves this
 * by casting the data pointer to a byte pointer and iterating over each byte.
 *
 * @param address: EEPROM address where the data will be stored.
 * @param data:    32-bit integer (signed or unsigned) to be written.
 */
void EEPROM_WriteInt32(uint16 address, uint32 data);


/*
 * @brief Reads a 32-bit integer (signed or unsigned) from EEPROM.
 *
 * This function reads 4 bytes from the specified EEPROM address sequentially
 * and reconstructs the 32-bit integer by copying the bytes into the provided
 * variable. It achieves this by casting the data pointer to a byte pointer
 * and reading each byte sequentially from EEPROM.
 *
 * @param address: EEPROM address from which the data will be read.
 * @return 32-bit integer (signed or unsigned) read from EEPROM.
 */
uint32 EEPROM_ReadInt32(uint16 address);


/*
 * @brief Writes a 32-bit float to EEPROM.
 *
 * This function splits the 32-bit float data into 4 bytes and writes them
 * sequentially starting from the specified EEPROM address. It achieves this
 * by casting the float pointer to a byte pointer and calling the EEPROM_WriteArray function
 * to handle the byte-by-byte writing process.
 *
 * @param address: EEPROM address where the float data will be stored.
 * @param data:    32-bit float to be written.
 */
void EEPROM_WriteFloat32( uint16 address , float32 data );


/*
 * @brief Reads a 32-bit float from EEPROM.
 *
 * This function reads 4 bytes from the specified EEPROM address sequentially
 * and reconstructs the 32-bit float by copying the bytes into the provided
 * variable. It achieves this by casting the float pointer to a byte pointer
 * and calling the EEPROM_ReadArray function to handle the byte-by-byte reading process.
 *
 * @param address: EEPROM address from which the float data will be read.
 * @return 32-bit float read from EEPROM.
 */
float32 EEPROM_ReadFloat32( uint16 address );


/*
 * @brief Enable the EEPROM interrupt.
 *
 * This function enables the interrupt for EEPROM operations.
 */
void EEPROM_InterruptEnable( void );


/*
 * @brief Disable the EEPROM interrupt.
 *
 * This function disables the interrupt for EEPROM operations.
 */
void EEPROM_InterruptDisable( void );


/*
 * @brief Sets the callback function for the EEPROM interrupt.
 *
 * This function sets a user-defined callback function to be called when the
 * EEPROM interrupt occurs.
 *
 * @example
 * void EEPROM_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * EEPROM_SetCallback( EEPROM_InterruptHandler );
 *
 * @param CopyFuncPtr: Pointer to the callback function. The function should have a
 * 					   void return type and no parameters.
 */
void EEPROM_SetCallback( void (*CopyFuncPtr)(void) );


#endif /* EEPROM_H_ */

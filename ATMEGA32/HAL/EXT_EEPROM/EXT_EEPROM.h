/****************************************************************************
 * @file    EXT_EEPROM.h
 * @author  Boles Medhat
 * @brief   EEPROM I2C Driver Header File
 * @version 1.0
 * @date    [2024-09-12]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides functions to interface with EEPROM devices over I2C.
 * It supports reading and writing both single bytes and arrays of data. The
 * driver handles EEPROM ICs that support 1-byte or 2-byte addressing modes
 * based on the configuration.
 *
 * The I2C EEPROM driver includes the following functionalities:
 * - Writing a single byte to a specified EEPROM address.
 * - Writing an array of bytes starting at a specified address in EEPROM.
 * - Reading a single byte from a specified EEPROM address.
 * - Reading an array of bytes starting at a specified address in EEPROM.
 * - Retrieving the status of I2C communication.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 *
 * - Requires the `EXT_EEPROM_config.h` for EEPROM-specific configuration.
 * - Ensure the correct EEPROM slave address and addressing mode are configured.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef EXT_EEPROM_H_
#define EXT_EEPROM_H_

#include "../../MCAL/I2C/I2C.h"
#include <util/delay.h>

#include "EXT_EEPROM_config.h"


/*
 * @brief Writes a single byte of data to a specified EEPROM address.
 *
 * This function handles I2C communication to write a byte to the EEPROM.
 * support both 1-byte and 2-byte address modes based on configuration.
 *
 * @param Address: The address in the EEPROM where the byte will be written.
 * @param Data: The byte value to be written to the EEPROM.
 * @return (uint8) Status code (SUCCESS or ERROR).
 */
uint8 EXT_EEPROM_WriteByte( uint16 Address , uint8 Data );


/*
 * @brief Writes an array of bytes to the EEPROM starting at the specified address.
 *
 * This function handles I2C communication to write multiple bytes to the EEPROM.
 * It supports both 1-byte and 2-byte address modes based on configuration.
 *
 * @param StartAddress: The starting address in the EEPROM where the array will be written.
 * @param DataArray: Pointer to the array of bytes to be written to the EEPROM.
 * @param ArraySize: The number of bytes to write from the array.
 * @return (uint8) Returns `SUCCESS` if the write operation is successful, or an error code if it fails.
 */
uint8 EXT_EEPROM_WriteArray( uint16 StartAddress , const uint8 * DataArray , uint16 ArraySize );


/*
 * @brief Reads a single byte of data from a specified EEPROM address.
 *
 * This function handles I2C communication to read a byte from the EEPROM.
 * It supports both 1-byte and 2-byte address modes based on configuration.
 *
 * @param Address: The address in the EEPROM from which the byte will be read.
 * @param Data: Pointer to a variable where the read byte will be stored.
 * @return (uint8) Returns `SUCCESS` if the read operation is successful, or an error code if it fails.
 */
uint8 EXT_EEPROM_ReadByte(uint16 Address, uint8 * Data);


/*
 * @brief Reads an array of bytes from a specified EEPROM starting address.
 *
 * This function handles I2C communication to read multiple bytes from the EEPROM.
 * It supports both 1-byte and 2-byte address modes based on configuration.
 *
 * @param StartAddress: The starting address in the EEPROM from which bytes will be read.
 * @param DataArray: Pointer to an array where the read bytes will be stored.
 * @param ArraySize: Number of bytes to read from the EEPROM.
 * @return (uint8) Returns `SUCCESS` if the read operation is successful, or an error code if it fails.
 */
uint8 EXT_EEPROM_ReadArray( uint16 StartAddress , uint8 * DataArray , uint16 ArraySize );


/*
 * @brief Retrieves the current status of the I2C communication.
 *
 * This function delegates the status retrieval to the I2C driver.
 * It returns the status code of the last I2C operation, which can be
 * used to determine the success or failure of I2C transactions involving
 * the EEPROM.
 *
 * @return (uint8) Status code from the I2C driver indicating the current status
 * of the I2C communication.
 */
uint8 EXT_EEPROM_GetStatus( void );


#endif /* EXT_EEPROM_H_ */

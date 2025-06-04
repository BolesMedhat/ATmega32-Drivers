/****************************************************************************
 * @file    EXT_EEPROM.c
 * @author  Boles Medhat
 * @brief   EEPROM I2C Driver Source File
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
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 *
 * - Requires `EXT_EEPROM_config.h` for macro-based configuration.
 * - Ensure the correct EEPROM slave address and addressing mode are configured.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "../EXT_EEPROM/EXT_EEPROM.h"





/*
 * @brief Writes a single byte of data to a specified EEPROM address.
 *
 * This function handles I2C communication to write a byte to the EEPROM.
 * support both 1-byte and 2-byte address modes based on configuration.
 *
 * @param Address: The address in the EEPROM where the byte will be written.
 * @param Data: The byte value to be written to the EEPROM.
 * @return (uint8) Returns `SUCCESS` if the write operation is successful, or an error code if it fails.
 */
uint8 EXT_EEPROM_WriteByte(uint16 Address, uint8 Data)
{

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return EXT_EEPROM_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return EXT_EEPROM_SLAW_ERROR;
	}


	/* Check the EEPROM Data Address Length */
	#if   EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_1_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Lower Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address & 0xFF) ) == ERROR )
		{

			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#elif EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_2_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Higher Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address >> 8) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_H_ADDR_ERROR;
		}

		/* Send the Lower Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address & 0xFF) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#else
			/* Make an Error */
			#error "Wrong \"EXT_EEPROM_ADDRESS_BYTES\" configuration option"
	#endif


	/* Send the Data Byte to be Written to the EEPROM and Check for Errors */
	if( I2C_WriteData( Data ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return EXT_EEPROM_W_DATA_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Wait for EEPROM to Complete the Write Cycle */
	_delay_ms( EXT_EEPROM_WRITE_DELAY_MS );

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





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
uint8 EXT_EEPROM_WriteArray( uint16 StartAddress , const uint8 * DataArray , uint16 ArraySize )
{

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return EXT_EEPROM_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return EXT_EEPROM_SLAW_ERROR;
	}


	/* Check the EEPROM Data Address Length */
	#if   EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_1_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Lower Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress & 0xFF) ) == ERROR )
		{

			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#elif EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_2_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Higher Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress >> 8) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_H_ADDR_ERROR;
		}

		/* Send the Lower Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress & 0xFF) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#else
			/* Make an Error */
			#error "Wrong \"EXT_EEPROM_ADDRESS_BYTES\" configuration option"
	#endif


	/* Write each Byte in the Data Array to the EEPROM and Check for Errors */
	for(uint16 byteIndex = 0 ; byteIndex < ArraySize ; byteIndex++)
	{
		/* Send the Data Byte to be Written to the EEPROM and Check for Errors */
		if( I2C_WriteData( DataArray[byteIndex] ) == ERROR )
		{
			/* Return Error if Writing Data Fails */
			return ERROR;
		}
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Wait for EEPROM to Complete the Write Cycle */
	_delay_ms( EXT_EEPROM_WRITE_DELAY_MS );

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





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
uint8 EXT_EEPROM_ReadByte(uint16 Address, uint8 * Data)
{

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return EXT_EEPROM_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return EXT_EEPROM_SLAW_ERROR;
	}


	/* Check the EEPROM Data Address Length */
	#if   EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_1_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Lower Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address & 0xFF) ) == ERROR )
		{

			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#elif EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_2_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Higher Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address >> 8) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_H_ADDR_ERROR;
		}

		/* Send the Lower Byte of the Address and Check for Errors */
		if( I2C_WriteData( (uint8)( Address & 0xFF) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#else
			/* Make an Error */
			#error "Wrong \"EXT_EEPROM_ADDRESS_BYTES\" configuration option"
	#endif


	/* Send a Repeated Start Condition and Check for Errors */
	if( I2C_RepeatedStart() == ERROR )
	{
		/* Return Error if Repeated Start Fails */
		return EXT_EEPROM_RE_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Read Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Read( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Read Fails */
		return EXT_EEPROM_SLAR_ERROR;
	}

	/* Read the Data Byte (With Not Acknowledgment) from the EEPROM and Check for Errors */
	if( I2C_ReadData_NACK( Data ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return EXT_EEPROM_R_DATA_N_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





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
uint8 EXT_EEPROM_ReadArray( uint16 StartAddress , uint8 * DataArray , uint16 ArraySize )
{

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return EXT_EEPROM_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return EXT_EEPROM_SLAW_ERROR;
	}


	/* Check the EEPROM Data Address Length */
	#if   EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_1_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Lower Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress & 0xFF) ) == ERROR )
		{

			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#elif EXT_EEPROM_ADDRESS_BYTES == EXT_EEPROM_2_BYTE_ADDRESS
		/* 1-Byte Addressing */

		/* Send the Higher Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress >> 8) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_H_ADDR_ERROR;
		}

		/* Send the Lower Byte of the Start Address and Check for Errors */
		if( I2C_WriteData( (uint8)( StartAddress & 0xFF) ) == ERROR )
		{
			/* Return Error if Writing Address Fails */
			return EXT_EEPROM_L_ADDR_ERROR;
		}

	#else
			/* Make an Error */
			#error "Wrong \"EXT_EEPROM_ADDRESS_BYTES\" configuration option"
	#endif


	/* Send a Repeated Start Condition and Check for Errors */
	if( I2C_RepeatedStart() == ERROR )
	{
		/* Return Error if Repeated Start Fails */
		return EXT_EEPROM_RE_START_ERROR;
	}

	/* Send the EEPROM Slave Address with Read Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Read( EXT_EEPROM_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Read Fails */
		return EXT_EEPROM_SLAR_ERROR;
	}

	/* Read the Array of Data bytes (Except Last Byte) from the EEPROM and Check for Errors */
	for(uint16 byteIndex = 0 ; byteIndex < ArraySize - 1 ; byteIndex++)
	{
		/* Read the Data Byte (With Acknowledgment) from the EEPROM and Check for Errors */
		if( I2C_ReadData_ACK( & DataArray[ byteIndex ] ) == ERROR )
		{
			/* Return Error if Reading Data (With Acknowledgment) Fails */
			return EXT_EEPROM_R_DATA_A_ERROR;
		}
	}

	/* Read the Last Data Byte (With Not Acknowledgment) from the EEPROM and Check for Errors */
	if( I2C_ReadData_NACK( & DataArray[ ArraySize - 1 ] ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return EXT_EEPROM_R_DATA_N_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





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
uint8 EXT_EEPROM_GetStatus( void )
{
	/* Return I2C Status Code */
	return I2C_GetStatus();
}





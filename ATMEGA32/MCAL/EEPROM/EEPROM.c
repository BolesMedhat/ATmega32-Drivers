/****************************************************************************
 * @file    EEPROM.c
 * @author  Boles Medhat
 * @brief   EEPROM Driver Source File - AVR ATmega32
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
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "EEPROM.h"

/* Pointer to the callback function for the EEPROM ISR */
void (* g_EEPROM_CallBack)(void) = NULL;





/*
 * @brief Write a byte of data to the specified EEPROM address.
 *
 * This function writes one byte of data to the EEPROM. It waits for the previous
 * write operation to complete before proceeding.
 *
 * @param address: The EEPROM address where the byte will be written (0-1023).
 * @param data:    The data byte to be written to the EEPROM.
 */
void EEPROM_WriteByte( uint16 address , uint8 data )
{

	/* Check that the address is valid */
	if ( address < EEPROM_SIZE )
	{
		/* Wait for completion of previous write */
		while (IS_BIT_SET( EECR , EEWE ));

		/* Set up address registers */
		EEAR = address;

		/* Set up data registers */
		EEDR = data;


		/* Set EEWE bit must be done within four clock cycles after set EEMWE bit */
		/* so we store the global interrupt flag then disable it */
		/* and restore the global interrupt flag in the end of function */


		/* Save global interrupt flag */
		uint8 sreg = SREG;

		/* Disable global interrupt */
		CLR_BIT( SREG , I );

		/* Start EEPROM write */
		EECR |= (1<<EEMWE);
		EECR |= (1<<EEWE);


		/* Restore global interrupt flag */
		SREG = sreg;
	}
}





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
uint8 EEPROM_ReadByte( uint16 address )
{

	/* Check that the address is valid */
	if ( address < EEPROM_SIZE )
	{
		/* Wait for completion of previous write */
		while (IS_BIT_SET( EECR , EEWE ));

		/* Set up address register */
		EEAR = address;

		/* Start EEPROM read from EERE */
		EECR |= (1<<EERE);

		/* Return data from data register */
		return EEDR;
	}

	/* Return 0 if the address is invalid */
	return 0;
}






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
void EEPROM_WriteArray( uint16 address , const uint8 * data_array , uint8 array_size )
{
	/* Check that the address of the array and the EEPROM address valid */
	if ( ( data_array == NULL ) || ( address + array_size > EEPROM_SIZE ) )
	{
		/* Stop if not valid */
		return;
	}

	/* Loops through each byte in the data array and writes it to EEPROM. */
	for (uint8 byte = 0 ; byte < array_size ; byte++ )
	{
		EEPROM_WriteByte( (address + byte) , data_array[byte] );
	}
}





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
void EEPROM_ReadArray( uint16 address , uint8 * data_array , uint8 array_size )
{
	/* Check that the address of the array and the EEPROM address valid */
	if ( ( data_array == NULL ) || ( address + array_size > EEPROM_SIZE ) )
	{
		/* Stop if not valid */
		return;
	}

	/* Loops through each byte in the data array and read it from EEPROM. */
	for (uint8 byte = 0 ; byte < array_size ; byte++ )
	{
		data_array[byte] = EEPROM_ReadByte( (address + byte) );
	}
}





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
void EEPROM_WriteInt16(uint16 address, uint16 data)
{
	/* Converts the 16-bit integer to a byte Array by Pointer Casting */
	EEPROM_WriteArray( address , (uint8 *)(&data) , 2 );
}





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
uint16 EEPROM_ReadInt16(uint16 address)
{
	uint16 data;

	/* Converts the 16-bit integer to a byte array by pointer casting */
	EEPROM_ReadArray( address , (uint8 *)(&data) , 2 );

	/* Return the 16-bit integer after read it */
	return data;
}





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
void EEPROM_WriteInt32(uint16 address, uint32 data)
{
	/* Converts the 32-bit integer to a byte array by pointer casting */
	EEPROM_WriteArray( address , (uint8 *)(&data) , 4 );
}





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
uint32 EEPROM_ReadInt32(uint16 address)
{
	uint32 data;

	/* Converts the 32-bit integer to a byte array by pointer casting */
	EEPROM_ReadArray( address , (uint8 *)(&data) , 4 );

	/* Return the 32-bit integer after read it */
	return data;
}





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
void EEPROM_WriteFloat32( uint16 address , float32 data )
{
	/* Converts the 32-bit float to a byte array by pointer casting */
	EEPROM_WriteArray( address , (uint8 *)(&data) , 4 );
}





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
float32 EEPROM_ReadFloat32( uint16 address )
{
	float32 data;

	/* Converts the 32-bit float to a byte array by pointer casting */
	EEPROM_ReadArray( address , (uint8 *)(&data) , 4 );

	/* Return the 32-bit float after Read it */
	return data;
}





/*
 * @brief Enable the EEPROM interrupt.
 *
 * This function enables the interrupt for EEPROM operations.
 */
void EEPROM_InterruptEnable( void )
{
	/* Enable the EEPROM interrupt */
	SET_BIT( EECR , EERIE );
}





/*
 * @brief Disable the EEPROM interrupt.
 *
 * This function disables the interrupt for EEPROM operations.
 */
void EEPROM_InterruptDisable( void )
{
	/* Disable the EEPROM interrupt */
	CLR_BIT( EECR , EERIE );
}





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
void EEPROM_SetCallback( void (*CopyFuncPtr)(void) )
{

	/* Copy the function pointer */
	g_EEPROM_CallBack = CopyFuncPtr;
}





/*
 * @brief ISR for the EEPROM interrupt.
 *
 * This ISR is triggered when an EEPROM interrupt occurs. It calls the user-defined callback function
 * set by the EEPROM_SetCallback function.
 *
 * @see EEPROM_SetCallback for setting the callback function.
 */
void __vector_17(void) __attribute__((signal));
void __vector_17(void)
{

	/* Check that the pointer is valid */
	if(g_EEPROM_CallBack != NULL)
	{
		/* Call The pointer to function */
		g_EEPROM_CallBack();
	}
}






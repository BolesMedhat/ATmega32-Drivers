/****************************************************************************
 * @file    I2C.c
 * @author  Boles Medhat
 * @brief   I2C (TWI) Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-06]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for the I2C (TWI) module
 * in ATmega32 microcontrollers, supporting Master and Slave operations.
 * It offers configurable initialization, start/stop conditions, address
 * transmission, data read/write (ACK/NACK), error handling, and interrupt
 * support through callback functions.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `I2C_config.h` for macro-based configuration.
 * - SDA/SCL pins should be properly pulled up for reliable communication.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "I2C.h"

/* Pointer to the callback function for the I2C ISR */
void (* g_I2C_CallBack)(void)= NULL;





/*
 * @brief  Initialize the I2C module based on configuration options.
 *
 * This function configures the SCL frequency using the selected prescaler and TWBR value,
 * I2C module address (7-bit), enables or disables General Call recognition,
 * internal pull-up resistors for SDA and SCL pins, enables or disables the I2C interrupt,
 * enables acknowledgment and the I2C module itself.
 * It configures the I2c registers according to the defined macros in `I2C_config.h`.
 *
 * @see `I2C_config.h` for configuration options.
 */
void I2C_Init( void )
{

	/* Calculate the I2C TWBR register */
	#if		I2C_PRESCALER == I2C_PRESCALER_1

		TWBR = ((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / 2;

	#elif	I2C_PRESCALER == I2C_PRESCALER_4

		TWBR = ((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / 8;

	#elif	I2C_PRESCALER == I2C_PRESCALER_16

		TWBR = ((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / 32;

	#elif	I2C_PRESCALER == I2C_PRESCALER_64

		TWBR = ((F_CPU/I2C_SCL_CLOCK_FREQUENCY) - 16) / 128;

	#endif


	/* Set the prescaler */
		TWSR = ( TWSR & I2C_STATUS_msk ) | I2C_PRESCALER;


	/* Check that the slave address is valid (not 1111xxx) */
	#if	(I2C_MODULE_ADDRESS & RESERVED_ADDRESS_MASK) != RESERVED_ADDRESS_MASK

		/* Set the required address in the 7 MSB of TWAR */
		TWAR = I2C_MODULE_ADDRESS << 1;

	#else
		/* Make an error */
		#error "Wrong \"I2C_MODULE_ADDRESS\" configuration option"
	#endif


	/* Check the general call address mode */
	#if   I2C_GENERAL_CALL_STATUS == I2C_GENERAL_CALL_DISABLE

		/* Disable general call address */
		CLR_BIT( TWAR , TWGCE );

	#elif I2C_GENERAL_CALL_STATUS == I2C_GENERAL_CALL_ENABLE

		/* Enable general call address */
		SET_BIT( TWAR , TWGCE );

	#else
		/* Make an error */
		#error "Wrong \"I2C_GENERAL_CALL_STATUS\" configuration option"
	#endif


	/* Check the I2C internal pull-up status */
	#if   I2C_INTERNAL_PULLUP_STATUS == I2C_INTERNAL_PULLUP_DISABLE

		/* Set SCL pin as floating */
		CLR_BIT( PORTC , SCL_PIN );

		/* Set SDA pin as floating */
		CLR_BIT( PORTC , SDA_PIN );

	#elif I2C_INTERNAL_PULLUP_STATUS == I2C_INTERNAL_PULLUP_ENABLE

		/* Set SCL pin as pull-up */
		SET_BIT( PORTC , SCL_PIN );

		/* Set SDA pin as pull-up */
		SET_BIT( PORTC , SDA_PIN );

	#else
		/* Make an error */
		#error "Wrong \"I2C_INTERNAL_PULLUP_STATUS\" configuration option"
	#endif


	/* Check the general call address mode */
	#if   I2C_INT_STATUS == I2C_INT_DISABLE

		/* Disable the I2C interrupt */
		CLR_BIT( TWCR , TWIE );

	#elif I2C_INT_STATUS == I2C_INT_ENABLE

		/* Enable the I2C interrupt */
		SET_BIT( TWCR , TWIE );

		/* Enable global interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an error */
		#error "Wrong \"I2C_INT_STATUS\" configuration option"
	#endif


	/* Enable acknowledge bit */
	SET_BIT( TWCR , TWEA );

	/* Enable the I2C */
	SET_BIT( TWCR , TWEN );
}





/*
 * @brief Disable the I2C interrupt.
 *
 * This function disables I2C (TWI) interrupt by clearing the TWIE bit in the TWCR register to disable
 */
void I2C_DisableInterrupt( void )
{
	CLR_BIT( TWCR , TWIE );
}





/*
 * @brief Enable the I2C interrupt.
 *
 * This function enables I2C (TWI) interrupt by set the TWIE bit in the TWCR register.
 */
void I2C_EnableInterrupt( void )
{
	SET_BIT( TWCR , TWIE );
}





/*
 * @brief Send an I2C start condition.
 *
 * This function initiates a start condition on the I2C bus to begin communication.
 *
 * @return (uint8) 0 if the start condition was transmitted successfully, 1 otherwise.
 */
uint8 I2C_Start( void )
{

	/* Initiate the start condition */
	SET_BIT( TWCR , TWSTA );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C end the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_START_TRANSMITTED_SC;
}





/*
 * @brief Send a repeated I2C start condition.
 *
 * This function useful when changing the direction of communication or restarting
 * without sending a stop condition.
 *
 * @return (uint8) 0 if the repeated start was transmitted successfully, 1 otherwise.
 */
uint8 I2C_RepeatedStart( void )
{

	/* Initiate the repeated start (start) condition */
	SET_BIT( TWCR , TWSTA );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C end the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_REPEATED_START_SC;
}





/*
 * @brief Send the slave address with write operation.
 *
 * This function sends a 7-bit slave address followed by a write bit (0) on the I2C bus.
 *
 * @param Address: The 7-bit address of the slave device.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_SendSlaveAddress_Write( uint8 Address )
{

	/* Set slave address to indicate a write operation */
	TWDR = (Address << 1) | I2C_WRITE;

	/* End the start condition */
	CLR_BIT( TWCR , TWSTA );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C ends the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_SLAW_ACK_SC;
}





/*
 * @brief Send the slave address with read operation.
 *
 * This function sends a 7-bit slave address followed by a read bit (1) on the I2C bus.
 *
 * @param Address: The 7-bit address of the slave device.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_SendSlaveAddress_Read( uint8 Address )
{

	/* Set slave address to indicate a read operation */
	TWDR = (Address << 1) | I2C_READ;

	/* End the start condition */
	CLR_BIT( TWCR , TWSTA );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C ends the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_SLAR_ACK_SC;
}





/*
 * @brief Write a byte of data to the I2C bus.
 *
 * This function transmits a byte of data to the slave device currently addressed.
 *
 * @param Data: The byte of data to be transmitted.
 *
 * @return (uint8) 0 if ACK received, 1 if NACK or error.
 */
uint8 I2C_WriteData( uint8 Data )
{

	/* Load data into the TWI data register to write to the bus */
	TWDR = Data;

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C ends the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_DATA_TRANSMITTED_ACK_SC;
}





/*
 * @brief Read a byte of data from the I2C bus and send ACK.
 *
 * This function receives a byte from the slave and sends an acknowledgment (ACK).
 *
 * @param[out] Data: Pointer to store the received byte.
 *
 * @return (uint8) 0 success, 1 otherwise.
 */
uint8 I2C_ReadData_ACK( uint8 * Data )
{

	/* Send acknowledge after reading the data */
	SET_BIT( TWCR , TWEA );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Wait until I2C ends the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* Load data from the TWI data register to read from the bus */
	*Data = TWDR;

	/* Return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_DATA_RECEIVED_ACK_SC;
}





/*
 * @brief Read a byte of data from the I2C bus and send NACK.
 *
 * This function receives a byte from the slave and sends a not acknowledgment (NACK).
 *
 * @param[out] Data: Pointer to store the received byte.
 *
 * @return (uint8) 0 success, 1 otherwise.
 */
uint8 I2C_ReadData_NACK( uint8 * Data )
{

	/* send not acknowledge after reading the data */
	CLR_BIT( TWCR , TWEA );

	/* clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );


	/* wait until I2C ends the operation and set the flag */
	while (IS_BIT_CLR( TWCR , TWINT ));

	/* load data from the TWI data register to read from the bus */
	*Data = TWDR;

	/* return 1 if the operation did not succeed, otherwise return 0 */
	return (TWSR & I2C_STATUS_msk) != I2C_DATA_RECEIVED_NACK_SC;
}





/*
 * @brief Send an I2C stop condition.
 *
 * This function Sends a stop condition to terminate communication on the I2C bus.
 */
void I2C_Stop( void )
{

	/* Initiate the stop condition */
	SET_BIT( TWCR , TWSTO );

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );
}





/*
 * @brief Get the current status of the I2C bus.
 *
 * This function reads and returns the status bits from the TWSR register.
 *
 * @return (uint8) The masked status code of the current I2C operation.
 */
uint8 I2C_GetStatus(void)
{
	return TWSR & I2C_STATUS_msk;
}





/*
 * @brief Handles I2C errors by executing the appropriate error-handling routines.
 *
 * This function checks the status code of the I2C interface and performs the appropriate error-handling actions:
 * - If an arbitration loss occurs, it will send a start condition to retry the operation.
 * - For other errors such as bus errors or NACK conditions, it sends a stop condition.
 * - For certain valid conditions, it enables the acknowledge bit and clear the interrupt flag to proceed with the next operation.
 */
void I2C_ErrorHandler( void )
{

	/* Check the status code */
	switch (TWSR & I2C_STATUS_msk)
	{
		case I2C_ARBITRATION_LOST_SC:

			/* Send start condition */
			I2C_Start();
			break;

		case I2C_BUS_ERROR_SC:
		case I2C_SLAW_NACK_SC:
		case I2C_SLAR_NACK_SC:
		case I2C_DATA_TRANSMITTED_NACK_SC:
		case I2C_DATA_RECEIVED_NACK_SC:

			/* Send stop condition */
			I2C_Stop();
			break;

		case I2C_STOP_OR_REPEATED_START_SC:
		case I2C_DATA_TRANSMITTED_NACK_SLAVE_SC:
		case I2C_LAST_DATA_TRANSMITTED_ACK_SC:
		case I2C_SLA_W_RECEIVED_SC:
		case I2C_ARBITRATION_LOST_SLA_W_SC:
		case I2C_GENERAL_CALL_ACK_SC:
		case I2C_ARBITRATION_LOST_GCALL_ACK_SC:

			/* Enable acknowledge bit */
			SET_BIT( TWCR ,TWEA );

			/* Clear the interrupt flag to allow the next operation */
			SET_BIT( TWCR , TWINT );
			break;
	}
}





/*
 * @brief Checks if the I2C slave has received a request from the master to read data.
 *
 * This function checks the current status of the I2C interface to determine if the slave device
 * has been addressed for reading by the master. It returns 1 if the slave has received a read request,
 * otherwise returns 0.
 *
 * @return (uint8) 1 if the slave has received a read request, otherwise 0.
 */
uint8 I2C_IsSlaveHasRead( void )
{

	/* check the status code */
	switch (TWSR & I2C_STATUS_msk)
	{
		case I2C_SLA_W_RECEIVED_SC:
		case I2C_ARBITRATION_LOST_SLA_W_SC:
		case I2C_GENERAL_CALL_ACK_SC:
		case I2C_ARBITRATION_LOST_GCALL_ACK_SC:

			/* enable acknowledge bit */
			SET_BIT( TWCR , TWEA );

			/* clear the interrupt flag to allow the next operation */
			SET_BIT( TWCR , TWINT );

			break;

		case I2C_PREVIOUS_ACK_SC:
		case I2C_PREVIOUS_NACK_SC:
		case I2C_GENERAL_CALL_DATA_ACK_SC:
		case I2C_GENERAL_CALL_DATA_NACK_SC:

			/* return 1 (true) */
			return 1;
	}

	/* return 0 (false) */
	return 0;
}





/*
 * @brief Checks if the I2C slave has received a request from the master to write data.
 *
 * This function checks the current status of the I2C interface to determine if the slave device
 * has been addressed for writing by the master. It returns 1 if the slave has received a write request,
 * otherwise returns 0.
 *
 * @return (uint8) 1 if the slave has received a write request, otherwise 0.
 */
uint8 I2C_IsSlaveHasWrite( void )
{

	/* Check the status code */
	switch (TWSR & I2C_STATUS_msk)
	{

		case I2C_SLA_R_RECEIVED_SC:
		case I2C_ARBITRATION_LOST_SLA_R_SC:
		case I2C_DATA_TRANSMITTED_ACK_SLAVE_SC:

			if(IS_BIT_SET( TWCR , TWINT ))
			{
				/* Return 1 (true) */
				return 1;
			}
	}

	/* Return 0 (false) */
	return 0;
}





/*
 * @brief Reads data from the master device as an I2C slave.
 *
 * This function waits until the I2C slave is addressed by the master to receive data. Once the request
 * is detected, the function reads the data byte from the data register, clear the interrupt flag to
 * allow further I2C operations, and returns the received data byte.
 *
 * @return (uint8) The data byte received from the master.
 */
uint8 I2C_SlaveRead( void )
{

	/* Wait until the I2C has request to read as a slave */
	while (I2C_IsSlaveHasRead() == 0);

	/* Read the Data */
	uint8 data = TWDR;

	/* Clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );

	/* Return the data */
	return data;
}





/*
 * @brief Writes data to the master device as an I2C slave.
 *
 * This function waits until the I2C slave is addressed by the master to write data. Once the request
 * is detected, the function loads the data byte into the data register, enables the acknowledge bit,
 * clear the interrupt flag to allow further I2C operations, and sends the data byte to the master.
 *
 * @param Data: The data byte to be written to the master.
 */
void I2C_SlaveWrite( uint8 Data )
{
	/* write data, as a slave, to the master */

	/* wait until the I2C has request to write as a slave */
	while (I2C_IsSlaveHasWrite() == 0);

	/* write the data */
	TWDR = Data;

	/* enable acknowledge bit */
	SET_BIT( TWCR , TWEA );

	/* clear the interrupt flag to allow the next operation */
	SET_BIT( TWCR , TWINT );
}





/*
 * @brief Sets a callback function for a I2C interrupt.
 *
 * This function set a user-defined callback function to be called when the I2C interrupt occurs.
 *
 * @example
 * void I2C_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * I2C_SetCallback( I2C_InterruptHandler );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void I2C_SetCallback( void (*CopyFuncPtr)(void) )
{
	/* Copy the data */
	g_I2C_CallBack = CopyFuncPtr;
}





/*
 * @brief ISR for the I2C interrupt.
 *
 * This ISR is triggered when a I2C interrupt occurs.
 * It calls the user-defined callback function set by the I2C_SetCallback function.
 *
 * @see I2C_SetCallback for setting the callback function.
 */
void __vector_19 (void)		__attribute__ ((signal)) ;
void __vector_19 (void)
{

	/* Check that the pointer is valid */
	if(g_I2C_CallBack != NULL)
	{
		/* Call The pointer to function */
		g_I2C_CallBack();
	}
}




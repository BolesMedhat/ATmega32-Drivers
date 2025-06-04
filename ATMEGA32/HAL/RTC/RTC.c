/****************************************************************************
 * @file    RTC_RTC.c
 * @author  Boles Medhat
 * @brief   RTC Driver Source File
 * @version 1.0
 * @date    [2024-09-15]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides an abstraction for controlling the Real-Time Clock (RTC)
 * IC DS1307 using I2C communication. It supports setting and retrieving both the time
 * (hours, minutes, seconds) and the date (day of the week, day, month, year).
 * The RTC operates with both decimal and Binary Coded Decimal (BCD) formats,
 * based on configuration.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 * - Requires the `RTC_config.h` for RTC-specific configuration.
 * - Ensure the correct RTC slave address and addressing mode are configured.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#include "RTC.h"





/*
 * @brief Sets the current time and date on the RTC.
 *
 * This function handles I2C communication to write the time and date to the RTC.
 *
 * @param time: Pointer to a `RTC_Time` structure containing the time to be set.
 * @param date: Pointer to a `RTC_Date` structure where the current date will be stored.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetTimeDate( RTC_Time * time , RTC_Date * date )
{

	/* Variable to Store Error Codes During Function Execution */
	uint8 _ERROR;

	/* Set the Time */
	_ERROR = RTC_SetTime( time );

	/* Check for Errors */
	if(_ERROR != SUCCESS)
	{
		/* Return the Error Code if Setting the Time Failed */
		return _ERROR;
	}

	/* Set the Date and Return the Error Code if Setting the Date Failed, else Return `SUCCESS` */
	return RTC_SetDate( date );
}





/*
 * @brief Retrieves the current time and date from the RTC.
 *
 * This function handles I2C communication to read the time and date from the RTC.
 * It supports both decimal and BCD formats based on configuration.
 * The retrieved values are stored in the provided `RTC_Time` and `RTC_Date` structures.
 *
 * @param time: Pointer to a `RTC_Time` structure where the retrieved time will be stored.
 * @param date: Pointer to a `RTC_Date` structure where the retrieved date will be stored.
 * @return: Returns `SUCCESS` if the date is retrieved successfully, or an error code if it fails.
 */
uint8 RTC_GetTimeDate( RTC_Time * time , RTC_Date * date )
{

	/* Variable to Store Error Codes During Function Execution */
	uint8 _ERROR;

	/* Get the Time */
	_ERROR = RTC_GetTime( time );

	/* Check for Errors */
	if(_ERROR != SUCCESS)
	{
		/* Return the Error Code if Getting the Time Failed */
		return _ERROR;
	}

	/* Get the Date and Return the Error Code if Getting the Date Failed, else Return `SUCCESS` */
	return RTC_GetDate( date );
}





/*
 * @brief Sets the current time on the RTC.
 *
 * This function handles I2C communication to write the time (seconds, minutes, and hours) to the RTC.
 *
 * @param time: Pointer to a `RTC_Time` structure containing the time to be set.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetTime( RTC_Time * time )
{

	/* Convert the Seconds, Minutes, and Hours to BCD Format for RTC */
	uint8 _Seconds = DC_decimal_to_hex( time -> seconds );
	uint8 _Minutes = DC_decimal_to_hex( time -> minutes );
	uint8 _Hours   = DC_decimal_to_hex( time -> hours );

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return RTC_START_ERROR;
	}

	/* Send the RTC Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return RTC_SLAW_ERROR;
	}

	/* Write the RTC Register Address for Seconds to Write to and Check for Errors */
	if( I2C_WriteData( RTC_SECONDS_REGISTER_ADDR ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Seconds to the RTC and Check for Errors */
	if( I2C_WriteData( _Seconds ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Minutes to the RTC and Check for Errors */
	if( I2C_WriteData( _Minutes ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Hours to the RTC and Check for Errors */
	if( I2C_WriteData( _Hours ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





/*
 * @brief Retrieves the current time from the RTC.
 *
 * This function handles I2C communication to read the time (seconds, minutes, and hours) from the RTC.
 * It supports both decimal and BCD formats based on configuration.
 * The retrieved values are stored in the provided `RTC_Time` structure.
 *
 * @param time: Pointer to a `RTC_Time` structure where the retrieved date will be stored.
 * @return: Returns `SUCCESS` if the date is retrieved successfully, or an error code if it fails.
 */
uint8 RTC_GetTime( RTC_Time * time )
{

	/* Temporary Variaibles to Store Seconds, Minutes, and Hours that retrieved from the RTC*/
	uint8 _Seconds = 0;
	uint8 _Minutes = 0;
	uint8 _Hours   = 0;

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return RTC_START_ERROR;
	}

	/* Send the RTC Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return RTC_SLAW_ERROR;
	}

	/* Write the RTC Register Address for Seconds to Write to and Check for Errors */
	if( I2C_WriteData( RTC_SECONDS_REGISTER_ADDR ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Send a Repeated Start Condition and Check for Errors */
	if( I2C_RepeatedStart() == ERROR )
	{
		/* Return Error if Repeated Start Fails */
		return RTC_RE_START_ERROR;
	}

	/* Send the RTC Slave Address with Read Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Read( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Read Fails */
		return RTC_SLAR_ERROR;
	}

	/* Read the Seconds (With Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_ACK( & _Seconds ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_A_ERROR;
	}

	/* Read the Minutes (With Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_ACK( & _Minutes ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_A_ERROR;
	}

	/* Read the Hours (With Not Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_NACK( & _Hours ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_N_ERROR;
	}


	/* End the I2C Communication */
	I2C_Stop();

	/* Check the RTC Data Return Format */
	#if   RTC_GET_FORMAT == RTC_GET_DECIMAL

		/* Convert BCD values to Decimal and Store in Date Structure */
		time -> seconds = DC_hex_to_decimal( _Seconds );
		time -> minutes = DC_hex_to_decimal( _Minutes );
		time -> hours	= DC_hex_to_decimal( _Hours );


	#elif RTC_GET_FORMAT == RTC_GET_BCD

		/* Store BCD values Directly in Date Structure */
		time -> seconds = _Seconds;
		time -> minutes = _Minutes;
		time -> hours	= _Hours;

	#else
		/* Make an Error */
		#error "Wrong \"RTC_GET_FORMAT\" configuration option"
	#endif


	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





/*
 * @brief Sets the date time on the RTC.
 *
 * This function handles I2C communication to write the date (day of week, day, month, and year) to the RTC.
 *
 * @param date: Pointer to a `RTC_Date` structure containing the date to be set.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetDate( RTC_Date * date )
{

	/* Ensure Day of Week is within 1 to 7 */
	uint8 _DayOfWeek = (date -> dayOfWeek) % 8;

	/* Convert the Day, Month, and Year to BCD Format for RTC */
	uint8 _Day		 = DC_decimal_to_hex( date -> day );
	uint8 _Month	 = DC_decimal_to_hex( date -> month );
	uint8 _Year		 = DC_decimal_to_hex( date -> year );

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return RTC_START_ERROR;
	}

	/* Send the RTC Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return RTC_SLAW_ERROR;
	}

	/* Write the RTC Register Address for Day of Week to Write to and Check for Errors */
	if( I2C_WriteData( RTC_DAY_OF_WEEK_REGISTER_ADDR ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Day of Week to the RTC and Check for Errors */
	if( I2C_WriteData( _DayOfWeek ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Day to the RTC and Check for Errors */
	if( I2C_WriteData( _Day ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Month to the RTC and Check for Errors */
	if( I2C_WriteData( _Month ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Write the Year to the RTC and Check for Errors */
	if( I2C_WriteData( _Year ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();

	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





/*
 * @brief Retrieves the current date from the RTC.
 *
 * This function handles I2C communication to read the date (day of week, day, month, and year) from the RTC.
 * It supports both decimal and BCD formats based on configuration.
 * The retrieved values are stored in the provided `RTC_Date` structure.
 *
 * @param date: Pointer to a `RTC_Date` structure where the retrieved date will be stored.
 * @return: Returns `SUCCESS` if the date is retrieved successfully, or an error code if it fails.
 */
uint8 RTC_GetDate( RTC_Date * date )
{

	/* Temporary Variaibles to Store Day of Week, Day, Month, and Year that retrieved from the RTC*/
	uint8 _DayOfWeek = 0;
	uint8 _Day		 = 0;
	uint8 _Month	 = 0;
	uint8 _Year		 = 0;

	/* Start the I2C Communication and Check for Errors */
	if( I2C_Start() == ERROR )
	{
		/* Return Error if I2C Start Fails */
		return RTC_START_ERROR;
	}

	/* Send the RTC Slave Address with Write Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Write( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Write Fails */
		return RTC_SLAW_ERROR;
	}

	/* Write the RTC Register Address for Day of Week to Write to and Check for Errors */
	if( I2C_WriteData( RTC_DAY_OF_WEEK_REGISTER_ADDR ) == ERROR )
	{
		/* Return Error if Writing Data Fails */
		return RTC_W_DATA_ERROR;
	}

	/* Send a Repeated Start Condition and Check for Errors */
	if( I2C_RepeatedStart() == ERROR )
	{
		/* Return Error if Repeated Start Fails */
		return RTC_RE_START_ERROR;
	}

	/* Send the RTC Slave Address with Read Instruction and Check for Errors */
	if( I2C_SendSlaveAddress_Read( RTC_SLAVE_ADDRESS ) == ERROR )
	{
		/* Return Error if Sending Slave Address for Read Fails */
		return RTC_SLAR_ERROR;
	}

	/* Read the Day of Week (With Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_ACK( & _DayOfWeek ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_A_ERROR;
	}

	/* Read the Day (With Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_ACK( & _Day ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_A_ERROR;
	}

	/* Read the Month (With Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_ACK( & _Month ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_A_ERROR;
	}

	/* Read the Year (With Not Acknowledgment) from the RTC and Check for Errors */
	if( I2C_ReadData_NACK( & _Year ) == ERROR )
	{
		/* Return Error if Reading Data (With Not Acknowledgment) Fails */
		return RTC_R_DATA_N_ERROR;
	}

	/* End the I2C Communication */
	I2C_Stop();


	/* Check the RTC Data Return Format */
	#if   RTC_GET_FORMAT == RTC_GET_DECIMAL

		/* Convert BCD values to Decimal and Store in Date Structure */
		date -> dayOfWeek = _DayOfWeek;
		date -> day		  = DC_hex_to_decimal( _Day );
		date -> month	  = DC_hex_to_decimal( _Month );
		date -> year	  = DC_hex_to_decimal( _Year );

	#elif RTC_GET_FORMAT == RTC_GET_BCD

		/* Store BCD values Directly in Date Structure */
		date -> dayOfWeek = _DayOfWeek;
		date -> day		  = _Day;
		date -> month	  = _Month;
		date -> year	  = _Year;

	#else
		/* Make an Error */
		#error "Wrong \"RTC_GET_FORMAT\" configuration option"
	#endif


	/* Return Success if All Operations are Completed Without Error */
	return SUCCESS;
}





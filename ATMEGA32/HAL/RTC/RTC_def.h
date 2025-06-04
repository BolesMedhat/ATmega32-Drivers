/****************************************************************************
 * @file    RTC_DEF.h
 * @author  Boles Medhat
 * @brief   RTC Driver Definitions Header File
 * @version 1.0
 * @date    [2024-09-15]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains the definitions and constants used by the RTC IC DS1307 driver,
 * including data structures, macros, error codes, and configuration settings.
 * It provides the necessary definitions to interact with the RTC hardware
 * using I2C communication. The file includes structure definitions for
 * time (hours, minutes, seconds) and date (day of week, day, month, year),
 * as well as various macros to convert between BCD and decimal formats.
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef RTC_DEF_H_
#define RTC_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Structure to hold time information (hours, minutes, seconds)*/
typedef struct
{
	uint8 seconds;			/*Stores the seconds (0-59)*/
	uint8 minutes;			/*Stores the minutes (0-59)*/
	uint8 hours;			/*Stores the hours in 24-hour format (0-23)*/
} RTC_Time;

/*Structure to hold date information (day of the week, day, month, year)*/
typedef struct
{
	uint8 dayOfWeek;		/*Stores the day of the week (1-7, where 1 = Sunday, 7 = Saturday)*/
	uint8 day;				/*Stores the day of the month (1-31, depending on the month)*/
	uint8 month;			/*Stores the month (1-12, where 1 = January, 12 = December)*/
	uint8 year;				/* Stores the year in two digits (0-99, representing 2000-2099)*/
} RTC_Date;
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*the RTC I2C Slave Address*/
#define RTC_SLAVE_ADDRESS					0x68	/*0x68 is the 7-bit address used for communication via I2C*/

/*RTC Register Addresses*/
#define RTC_SECONDS_REGISTER_ADDR			0x00	/*Address of the seconds register in the RTC*/
#define RTC_DAY_OF_WEEK_REGISTER_ADDR		0x03	/*Address of the day of the week register in the RTC*/

/*Day of Week*/
#define RTC_SUNDAY							1		/*Sunday*/
#define RTC_MONDAY							2		/*Monday*/
#define RTC_TUESDAY							3		/*Tuesday*/
#define RTC_WEDNESDAY						4		/*Wednesday*/
#define RTC_THURSDAY						5		/*Thursday*/
#define RTC_FRIDAY							6		/*Friday*/
#define RTC_SATURDAY						7		/*Saturday*/

/*RTC I2C ERRORS*/
#define RTC_START_ERROR						2		/*Error during I2C start condition*/
#define RTC_SLAW_ERROR						3		/*Error sending RTC slave address with write instruction*/
#define RTC_W_DATA_ERROR					6		/*Error writing data byte to EEPROM*/
#define RTC_RE_START_ERROR					7		/*Error during repeated start condition*/
#define RTC_SLAR_ERROR						8		/*Error sending RTC slave address with read instruction*/
#define RTC_R_DATA_A_ERROR					9		/*Error reading data byte with ACK*/
#define RTC_R_DATA_N_ERROR					10		/*Error reading data byte with NACK*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*RTC Data Return Format*/
#define RTC_GET_DECIMAL						0	/*Specifies that RTC Get functions should return data in decimal format (e.g., 25 as 25)*/
#define RTC_GET_BCD							1	/*Specifies that RTC Get functions should return data in BCD format (e.g., 25 as 0x25)*/
/*_______________________________________________________________________________________________*/


#endif /* RTC_DEF_H_ */

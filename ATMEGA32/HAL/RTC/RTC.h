/****************************************************************************
 * @file    RTC_RTC.h
 * @author  Boles Medhat
 * @brief   RTC Driver Header File
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
 * The RTC driver includes the following functionalities:
 * - Set and get the current time (hours, minutes, and seconds).
 * - Set and get the current date (day of the week, day, month, and year).
 * - Functions for setting and retrieving both time and date together.
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

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

#include "RTC_config.h"
#include "../../MCAL/I2C/I2C.h"
#include "../../LIB/DataConvert/DataConvert.h"


/*
 * @brief Sets the current time and date on the RTC.
 *
 * This function handles I2C communication to write the time and date to the RTC.
 *
 * @param Time: Pointer to a `RTC_Time` structure containing the time to be set.
 * @param date: Pointer to a `RTC_Date` structure containing the date to be set.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetTimeDate( RTC_Time * Time , RTC_Date * date );


/*
 * @brief Retrieves the current time and date from the RTC.
 *
 * This function handles I2C communication to read the time and date from the RTC.
 * It supports both decimal and BCD formats based on configuration.
 * The retrieved values are stored in the provided `RTC_Time` and `RTC_Date` structures.
 *
 * @param Time: Pointer to a `RTC_Time` structure where the retrieved time will be stored.
 * @param date: Pointer to a `RTC_Date` structure where the retrieved date will be stored.
 * @return: Returns `SUCCESS` if the date is retrieved successfully, or an error code if it fails.
 */
uint8 RTC_GetTimeDate( RTC_Time * Time , RTC_Date * date );


/*
 * @brief Sets the current time on the RTC.
 *
 * This function handles I2C communication to write the time (seconds, minutes, and hours) to the RTC.
 *
 * @param Time: Pointer to a `RTC_Time` structure containing the time to be set.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetTime( RTC_Time * Time );


/*
 * @brief Retrieves the current time from the RTC.
 *
 * This function handles I2C communication to read the time (seconds, minutes, and hours) from the RTC.
 * It supports both decimal and BCD formats based on configuration.
 * The retrieved values are stored in the provided `RTC_Time` structure.
 *
 * @param Time: Pointer to a `RTC_Time` structure where the retrieved date will be stored.
 * @return: Returns `SUCCESS` if the date is retrieved successfully, or an error code if it fails.
 */
uint8 RTC_GetTime( RTC_Time * Time );


/*
 * @brief Sets the date time on the RTC.
 *
 * This function handles I2C communication to write the date (day of week, day, month, and year) to the RTC.
 *
 * @param date: Pointer to a `RTC_Date` structure containing the date to be set.
 * @return: Returns `SUCCESS` if the time is set successfully, or an error code  if it fails.
 */
uint8 RTC_SetDate( RTC_Date * date );


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
uint8 RTC_GetDate( RTC_Date * date );


#endif /* RTC_RTC_H_ */

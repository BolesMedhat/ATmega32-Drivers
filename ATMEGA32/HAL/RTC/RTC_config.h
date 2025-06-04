/****************************************************************************
 * @file    RTC_CONFIG.h
 * @author  Boles Medhat
 * @brief   RTC Driver Configuration Header File
 * @version 1.0
 * @date    [2024-09-15]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration settings for the RTC IC DS1307 driver.
 * It allows customization of the data return format used by the RTC functions. The
 * configuration option defines how the RTC time and date values are returned,
 * either in decimal or BCD format.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any RTC
 *  			   driver function. This driver does not initialize I2C internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_

#include "RTC_def.h"


/*Set RTC Data Return Format
 * choose between:
 * 1. RTC_GET_DECIMAL				<--the most used
 * 2. RTC_GET_BCD
 */
#define RTC_GET_FORMAT				RTC_GET_DECIMAL


/* You must initialize I2C manually "I2C_Init()" before using this driver */
#ifndef I2C_IN_HAL
#define I2C_IN_HAL
	#warning "⚠️ Initialize I2C manually before using this driver."
#endif


/* Enable I2C overflow interrupt */
#if I2C_INT_STATUS != I2C_INT_DISABLE
	#warning "⚠️ Disable I2C interrupt."
#endif


#endif /* RTC_CONFIG_H_ */

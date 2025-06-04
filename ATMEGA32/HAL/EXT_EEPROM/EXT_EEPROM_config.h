/****************************************************************************
 * @file    EXT_EEPROM_config.h
 * @author  Boles Medhat
 * @brief   EEPROM I2C Driver Configuration Header File
 * @version 1.0
 * @date    [2024-09-12]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This configuration file provides compile-time settings for the EEPROM
 * I2C driver, allowing customization based on the target EEPROM device.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 *
 * - Ensure the selected address byte size matches the EEPROM IC.
 * - Adjust write delay based on the EEPROM datasheet specifications.
 * - Use 1-byte addressing for EEPROMs with up to 256 bytes of memory.
 * - Use 2-byte addressing for EEPROMs with more than 256 bytes of memory.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef EXT_EEPROM_CONFIG_H_
#define EXT_EEPROM_CONFIG_H_

#include "EXT_EEPROM_def.h"


/*Set the EEPROM I2C Slave Address*/
#define EXT_EEPROM_SLAVE_ADDRESS				0x50



/*Set the EEPROM Write Operation Delay (Adjust per Datasheet; 10 ms is often Sufficient)*/
#define EXT_EEPROM_WRITE_DELAY_MS				10



/*Set the EEPROM Data Address Word Size
 * choose between:
 * 1. EXT_EEPROM_1_BYTE_ADDRESS
 * 2. EXT_EEPROM_2_BYTE_ADDRESS			<--the most used
 */
#define EXT_EEPROM_ADDRESS_BYTES				EXT_EEPROM_2_BYTE_ADDRESS



/* You must initialize I2C manually "I2C_Init()" before using this driver */
#ifndef I2C_IN_HAL
#define I2C_IN_HAL
	#warning "⚠️ Initialize I2C manually before using this driver."
#endif



/* Enable I2C overflow interrupt */
#if I2C_INT_STATUS != I2C_INT_DISABLE
	#warning "⚠️ Disable I2C interrupt."
#endif


#endif /* EXT_EEPROM_CONFIG_H_ */

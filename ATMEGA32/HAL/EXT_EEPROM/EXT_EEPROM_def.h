/****************************************************************************
 * @file    EXT_EEPROM_def.h
 * @author  Boles Medhat
 * @brief   EEPROM I2C Driver Definitions Header File
 * @version 1.0
 * @date    [2024-09-12]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file defines macros for error codes and configuration constants used
 * in the I2C-based EEPROM driver. These definitions help abstract the status
 * codes and addressing modes to simplify error handling and configuration.
 *
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

#ifndef EXT_EEPROM_DEF_H_
#define EXT_EEPROM_DEF_H_


/*------------------------------------------   values    ----------------------------------------*/

/*EEPROM I2C ERRORS*/
#define EXT_EEPROM_START_ERROR					2	/*Error during I2C start condition*/
#define EXT_EEPROM_SLAW_ERROR					3	/*Error sending EEPROM slave address with write instruction*/
#define EXT_EEPROM_L_ADDR_ERROR					4	/*Error writing lower byte of address*/
#define EXT_EEPROM_H_ADDR_ERROR					5	/*Error writing higher byte of address*/
#define EXT_EEPROM_W_DATA_ERROR					6	/*Error writing data byte to EEPROM*/
#define EXT_EEPROM_RE_START_ERROR				7	/*Error during repeated start condition*/
#define EXT_EEPROM_SLAR_ERROR					8	/*Error sending EEPROM slave address with read instruction*/
#define EXT_EEPROM_R_DATA_A_ERROR				9	/*Error reading data byte with ACK*/
#define EXT_EEPROM_R_DATA_N_ERROR				10	/*Error reading data byte with NACK*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*EEPROM Data Address Length*/
#define EXT_EEPROM_1_BYTE_ADDRESS				1	/*Use 1-byte addressing for EEPROM (up to 256 bytes of memory)*/
#define EXT_EEPROM_2_BYTE_ADDRESS				2	/*Use 2-byte addressing for EEPROM (supports memory sizes larger than 256 bytes)*/
/*_______________________________________________________________________________________________*/


#endif /* EXT_EEPROM_DEF_H_ */

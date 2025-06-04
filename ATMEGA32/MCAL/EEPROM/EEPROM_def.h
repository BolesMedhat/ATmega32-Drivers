/****************************************************************************
 * @file    EEPROM.c
 * @author  Boles Medhat
 * @brief   EEPROM Driver Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-03]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register and bit-level definitions
 * required for controlling the internal EEPROM of the AVR ATmega32 microcontroller.
 * It provides direct access to EEPROM-related registers and bit masks for
 * configuring and accessing EEPROM memory.
 *
 * The EEPROM_def file includes:
 * - EEPROM address, data, and control registers.
 * - Bit positions for EEPROM control and global interrupt handling.
 * - EEPROM memory size definition.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef EEPROM_DEF_H_
#define EEPROM_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*EEPROM Address Registers*/
#define EEARL							*((volatile uint8 *)0x3E)	/*The EEPROM Address LOW Register*/
#define EEARH							*((volatile uint8 *)0x3F)	/*The EEPROM Address HIGH Register*/
#define EEAR							*((volatile uint16 *)0x3E)	/*The EEPROM Address Register*/

/*EEPROM Data Register*/
#define EEDR							*((volatile uint8 *)0x3D)	/*The EEPROM Data Register*/

/*EEPROM Control Register*/
#define EECR							*((volatile uint8 *)0x3C)	/*The EEPROM Control Register*/

/*Global Interrupt Register*/
#define SREG							*((volatile uint8 *)0x5F)	/*status register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*EECR Register*/
#define EERE							0	/*EEPROM Read Enable*/
#define EEWE							1	/*EEPROM Write Enable*/
#define EEMWE							2	/*EEPROM Master Write Enable*/
#define EERIE							3	/*EEPROM Ready Interrupt Enable*/

/*SREG Registers*/
#define	I								7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define EEPROM_SIZE						1024	/*The size of the EEPROM in bytes*/
/*_______________________________________________________________________________________________*/


#endif /* EEPROM_DEF_H_ */

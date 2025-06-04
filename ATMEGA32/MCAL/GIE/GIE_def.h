/****************************************************************************
 * @file    GIE_def.h
 * @author  Boles Medhat
 * @brief   Global Interrupt Enable Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains register and bit definitions for global interrupt control
 * on the AVR ATmega32 microcontroller.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef GIE_DEF_H_
#define GIE_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*Watchdog Control Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*Watchdog Timer Control Register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/


#endif /* GIE_DEF_H_ */

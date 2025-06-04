/****************************************************************************
 * @file    USONIC_def.h
 * @author  Boles Medhat
 * @brief   Ultrasonic Sensor Driver Definitions Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This header file defines the configuration structure `Usonic` that
 * holds information about the sensor's port and pin assignments.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module **before** calling any
 * 				   SERVO driver function. This driver does not initialize
 *	 	 	 	   TIMER1 module internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef USONIC_DEF_H_
#define USONIC_DEF_H_

#include "../../MCAL/DIO/DIO.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Usonic type for use in function parameter*/
typedef struct
{
	uint8 port_id  : 2;		/*Select port_id  from [  PORTB_ID  , PORTB_ID , PORTC_ID , PORTD_ID ]*/
	uint8 echo_pin : 3;		/*Select echo_pin from [ PIN0_ID to PIN7_ID ]*/
	uint8 trig_pin : 3;		/*Select trig_pin from [ PIN0_ID to PIN7_ID ]*/
}Usonic;
/*_______________________________________________________________________________________________*/


#endif /* USONIC_DEF_H_ */

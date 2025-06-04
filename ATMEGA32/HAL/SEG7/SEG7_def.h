/****************************************************************************
 * @file    SEG7_def.h
 * @author  Boles Medhat
 * @brief   7-Segment Display Definitions Header File
 * @version 2.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all definitions, macros, and types required for 7-segment
 * display operation, supporting both common anode and common cathode modes.
 * It includes port configuration options, logic levels, digit values, and masks.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SEG7_DEF_H_
#define SEG7_DEF_H_

#include "../../MCAL/DIO/DIO.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Structure to hold 7-Segment information*/
typedef struct{
	uint8 DataPort;	/*7-Segment data port from [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]*/
	uint8 EnablePort;	/*7-Segment enable port (for multiplexing) from [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ]*/
	uint8 FirstEnablePin;	/*First enable pin in 7-Segment enable port (for multiplexing) from [ DIO_PIN0 to DIO_PIN7 ]*/
	uint8 DigitsNum;	/*Number of 7-Segment digits that will multiplexing*/
}Seg7;
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define SEG7_DOT_PIN						7		/* Pin for the decimal point(dot) on the 7-segment display */

/*7-Segment Common Anode Logic*/
#define SEG7_ANODE_PIN_ENABLE				HIGH	/*Set pin LOW to enable (turn on) the Segment(LED) for Common Anode*/
#define SEG7_ANODE_PIN_DISABLE				LOW		/*Set pin HIGH to disable (turn off) the Segment(LED) for Common Anode*/

/*7-Segment Common Cathode Logic*/
#define SEG7_CATHODE_PIN_ENABLE				LOW		/*Set pin HIGH to enable (turn on) the Segment(LED) for Common Cathode*/
#define SEG7_CATHODE_PIN_DISABLE			HIGH	/*Set pin LOW to disable (turn off) the Segment(LED) for Common Cathode*/

/*7-Segment Digits Array (0-9) values for Common Anode*/
#define SEG7_ANODE_ARRAY					\
{0b11000000,			/*0*/				\
 0b11111001,			/*1*/				\
 0b10100100,			/*2*/				\
 0b10110000,			/*3*/				\
 0b10011001,			/*4*/				\
 0b10010010,			/*5*/				\
 0b10000010,			/*6*/				\
 0b11111000,			/*7*/				\
 0b10000000,			/*8*/				\
 0b10010000}			/*9*/

/*7-Segment Digits Array (0-9) values for Common Cathode*/
#define SEG7_CATHODE_ARRAY					\
{0b00111111,			/*0*/				\
 0b00000110,			/*1*/				\
 0b01011011,			/*2*/				\
 0b01001111,			/*3*/				\
 0b01100110,			/*4*/				\
 0b01101101,			/*5*/				\
 0b01111101,			/*6*/				\
 0b00000111,			/*7*/				\
 0b01111111,			/*8*/				\
 0b01101111}			/*9*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*7-Segment Type*/
#define SEG7_COMMON_ANODE					0	/*Common Anode:   Segments light up when the corresponding pin is set LOW*/
#define SEG7_COMMON_CATHODE					1	/*Common Cathode: Segments light up when the corresponding pin is set HIGH*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

/*7-Segment mask to turns off all the Segments(LEDS) */
#define SEG7_ANODE_DISABLE_msk				0xFF	/*Turns off All the Segments(LEDS) for Common Anode*/
#define SEG7_CATHODE_DISABLE_msk			0x00	/*Turns off All the Segments(LEDS) for Common Cathode*/
/*_______________________________________________________________________________________________*/

#endif /* SEG7_DEF_H_ */

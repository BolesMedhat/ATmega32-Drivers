/****************************************************************************
 * @file    EXTI_def.h
 * @author  Boles Medhat
 * @brief   External Interrupt (EXTI) Definitions Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * macros, and configuration values required for handling external interrupts
 * (INT0, INT1, INT2) on the ATmega32 microcontroller.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef EXTI_DEF_H_
#define EXTI_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*External Interrupt Control Registers*/
#define MCUCR								*((volatile uint8 *)0x55)	/*MCU Control Register*/
#define MCUCSR								*((volatile uint8 *)0x54)	/*MCU Control and Status Register*/

/*Interrupt Registers*/
#define GICR								*((volatile uint8 *)0x5B)	/*General Interrupt Control Register*/
#define GIFR								*((volatile uint8 *)0x5A)	/*General Interrupt Flag Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/

/*INT Pins Direction Registers*/
#define DDRD								*((volatile uint8 *)0x31)	/*Port D Data Direction Register (External Interrupt 0 and 1 Direction Register)*/
#define DDRB								*((volatile uint8 *)0x37)	/*Port B Data Direction Register (External Interrupt 2 Direction Register)*/

/*INT Pins Registers*/
#define PORTD								*((volatile uint8 *)0x32)	/*Port D Data Register (External Interrupt 0 and 1 Port Register)*/
#define PORTB								*((volatile uint8 *)0x38)	/*Port B Data Register (External Interrupt 2 Port Register)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*MCUCR Register*/
#define ISC00								0	/*Interrupt Sense Control 0 Bit 0*/
#define ISC01								1	/*Interrupt Sense Control 0 Bit 1*/
#define ISC10								2	/*Interrupt Sense Control 1 Bit 0*/
#define ISC11								3	/*Interrupt Sense Control 1 Bit 1*/

/*MCUCSR Register*/
#define ISC2								6	/*Interrupt Sense Control 2*/

/*GICR Register*/
#define INT0								6	/*External Interrupt Request 0 Enable*/
#define	INT1								7	/*External Interrupt Request 1 Enable*/
#define INT2								5	/*External Interrupt Request 2 Enable*/

/*GIFR Register*/
#define	INTF0								6	/*External Interrupt Flag 0*/
#define	INTF1								7	/*External Interrupt Flag 1*/
#define	INTF2								5	/*External Interrupt Flag 2*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/

/*DDRD and PORTD Register*/
#define INT0_PIN							2	/*External Interrupt 0 pin from pinout*/
#define INT1_PIN							3	/*External Interrupt 1 pin from pinout*/

/*DDRB and PORTB Register*/
#define INT2_PIN							2	/*External Interrupt 2 pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*External Interrupt IDs*/
#define EXTI_INT0_ID						0	/*External Interrupt 0 ID for functions parameters*/
#define EXTI_INT1_ID						1	/*External Interrupt 1 ID for functions parameters */
#define EXTI_INT2_ID						2	/*External Interrupt 2 ID for functions parameters */
#define EXTI_MAX_INTERRUPTS					3	/*Number of External Interrupts*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*the External Interrupt Status*/
#define EXTI_DISABLE						0	/*Disable the External Interrupt*/
#define EXTI_ENABLE							1	/*Enable  the External Interrupt*/

/*Interrupt Sense Control*/
#define EXTI_THE_LOW_LEVEL					0	/*The Low Level of		INTx generates an interrupt request*/
#define EXTI_ANY_LOGIC_CHANGE				1	/*Any Logical Change on INTx generates an interrupt request*/
#define EXTI_THE_FALLING_EDGE				2	/*The Falling Edge of 	INTx generates an interrupt request*/
#define EXTI_THE_RISING_EDGE				3	/*The Rising Edge of 	INTx generates an interrupt request*/

/*the External Interrupt PIN Mode*/
#define EXTI_INPUT							0	/*the External Interrupt PIN in normal  input mode*/
#define EXTI_INPUT_PULLUP					2	/*the External Interrupt PIN in pull-up input mode*/
/*_______________________________________________________________________________________________*/


#endif /* EXTI_DEF_H_ */

/****************************************************************************
 * @file    AC_def.h
 * @author  Boles Medhat
 * @brief   Analog Comparator (AC) Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * and constant macros for use with the Analog Comparator (AC) driver for the
 * ATmega32 microcontroller.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef AC_DEF_H_
#define AC_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/* Control Registers*/
#define ACSR								*((volatile uint8 *)0x28)	/*Analog Comparator Control and Status Register*/
#define SFIOR								*((volatile uint8 *)0x50)	/*Special Function IO Register*/

/*ADC Registers*/
#define ADCSRA								*((volatile uint8 *)0x26)	/*ADC Control and Status Register A*/
#define ADMUX								*((volatile uint8 *)0x27)	/*ADC Multiplexer Selection Register*/

/*Global Interrupt Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*ACSR Register*/
#define ACIS0								0	/*Analog Comparator Interrupt Mode Select Bit 0*/
#define ACIS1								1	/*Analog Comparator Interrupt Mode Select Bit 1*/
#define ACIC								2	/*Analog Comparator Input Capture Enable*/
#define ACIE								3	/*Analog Comparator Interrupt Enable*/
#define ACI									4	/*Analog Comparator Interrupt Flag*/
#define ACO									5	/*Analog Comparator Output*/
#define ACBG								6	/*Analog Comparator Bandgap Select*/
#define ACD									7	/*Analog Comparator Disable*/

/*SFIOR Register*/
#define ACME								3	/*Analog Comparator Multiplexer Enable*/

/*ADCSRA Register*/
#define ADEN    							7	/*ADC Enable*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*Analog Comparator Negative Input*/
#define AC_AIN1								8	/*AIN1*/
#define AC_ADC0								0	/*ADC0*/
#define AC_ADC1								1	/*ADC1*/
#define AC_ADC2								2	/*ADC2*/
#define AC_ADC3								3	/*ADC3*/
#define AC_ADC4								4	/*ADC4*/
#define AC_ADC5								5	/*ADC5*/
#define AC_ADC6								6	/*ADC6*/
#define AC_ADC7								7	/*ADC7*/

/*Analog Comparator Positive Input*/
#define AC_BG								0	/*fixed bandgap reference voltage. Min: 1.15V, Typ: 1.23V, Max: 1.35V*/
#define AC_AIN0								1	/*AIN0*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*Analog Comparator Interrupt Status*/
#define AC_INT_DISABLE						0	/*Analog Comparator Interrupt Disable*/
#define AC_INT_ENABLE						1	/*Analog Comparator Interrupt Enable*/

/*Analog Comparator Interrupt Mode*/
#define AC_INT_ON_TOGGLE					0	/*Comparator Interrupt on Output Toggle*/
#define AC_INT_ON_FALLING					2	/*Comparator Interrupt on Falling Output Edge*/
#define AC_INT_ON_RISING					3	/*Comparator Interrupt on Rising Output Edge*/

/*Analog Comparator Input Capture Enable*/
#define AC_TRIGGER_ICU_DISABLE				0	/*Disable trigger the Input Capture by the Analog Comparator*/
#define AC_TRIGGER_ICU_ENABLE				1	/*Enable  trigger the Input Capture by the Analog Comparator*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define ADC_CHANNEL_clr_msk 				0xE0	/*ADC channel clear mask*/
/*_______________________________________________________________________________________________*/


#endif /* AC_DEF_H_ */

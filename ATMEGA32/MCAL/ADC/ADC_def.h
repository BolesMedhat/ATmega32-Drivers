/****************************************************************************
 * @file    ADC_DEF.h
 * @author  Boles Medhat
 * @brief   ADC Driver  Definitions Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-16]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * ADC channels, modes, reference voltages, and prescalers. and configuration
 * macros for the ADC (Analog to Digital Converter) module in the ATmega32
 * microcontroller.
 *
 * These definitions are intended to be used by the `ADC` driver and other components
 * that require interaction with the ADC module.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef ADC_DEF_H_
#define ADC_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*ADC Registers*/
#define ADC									*((volatile uint16 *)0x24)	/*ADC 10-bit Result Register (combined ADCL and ADCH)*/
#define ADCL								*((volatile uint8 *)0x24)	/*ADC 8 BIT LOW Register*/
#define ADCH								*((volatile uint8 *)0x25)	/*ADC 8 BIT HIGH Register*/

/*ADC Control Registers*/
#define ADCSRA								*((volatile uint8 *)0x26)	/*ADC Control and Status Register A*/
#define ADMUX								*((volatile uint8 *)0x27)	/*ADC Multiplexer Selection Register*/
#define SFIOR								*((volatile uint8 *)0x50)	/*Special Function I/O Register*/

/*Interrupt Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*ADCSRA Register*/
#define ADPS0		  						0	/*ADC Prescaler Select Bit 0*/
#define ADPS1		  						1	/*ADC Prescaler Select Bit 1*/
#define ADPS2   							2	/*ADC Prescaler Select Bit 2*/
#define ADIE								3	/*ADC Interrupt Enable*/
#define ADIF								4	/*ADC Interrupt Flag*/
#define ADATE								5	/*ADC Auto Trigger Enable*/
#define ADSC    							6	/*ADC Start Conversion*/
#define ADEN    							7	/*ADC Enable*/

/*ADMUX Register*/
#define MUX0								0	/*Analog Channel and Gain Selection Bit 0*/
#define MUX1								1	/*Analog Channel and Gain Selection Bit 1*/
#define MUX2								2	/*Analog Channel and Gain Selection Bit 2*/
#define MUX3								3	/*Analog Channel and Gain Selection Bit 3*/
#define MUX4								4	/*Analog Channel and Gain Selection Bit 4*/
#define ADLAR								5	/*ADC Left Adjust Result*/
#define REFS0								6	/*Reference Selection Bit 0*/
#define REFS1								7	/*Reference Selection Bit 1*/

/*SFIOR Register*/
#define ADTS0								5	/*ADC Auto Trigger Source Bit 0*/
#define ADTS1								6	/*ADC Auto Trigger Source Bit 1*/
#define ADTS2								7	/*ADC Auto Trigger Source Bit 2*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define ADC_WAIT_FOREVER					0		/*finishing the conversion is the only thing that ends the waiting*/

/*ADC Channels*/

/*ADC frequency Range*/
#define ADC_FREQUENCY_MIN					50000	/*minimum clock frequency ADC can work with (50KHz)*/
#define ADC_FREQUENCY_MAX					200000	/*maximum clock frequency ADC can work with (200KHz)*/

/*Single Ended Input*/
#define ADC_Channel_0						0		/*ADC0*/
#define ADC_Channel_1						1		/*ADC1*/
#define ADC_Channel_2						2		/*ADC2*/
#define ADC_Channel_3						3		/*ADC3*/
#define ADC_Channel_4						4		/*ADC4*/
#define ADC_Channel_5						5		/*ADC5*/
#define ADC_Channel_6						6		/*ADC6*/
#define ADC_Channel_7						7		/*ADC7*/
#define ADC_Channel_30						30		/*1.22V*/
#define ADC_Channel_31						31		/*0V(GND)*/

#define ADC0								0		/*ADC0*/
#define ADC1								1		/*ADC1*/
#define ADC2								2		/*ADC2*/
#define ADC3								3		/*ADC3*/
#define ADC4								4		/*ADC4*/
#define ADC5								5		/*ADC5*/
#define ADC6								6		/*ADC6*/
#define ADC7								7		/*ADC7*/

/*Differential Input with Gain*/
#define ADC_Channel_9						9		/*10x(ADC1 - ADC0)*/
#define ADC_Channel_11						11		/*200x(ADC1 - ADC0)*/
#define ADC_Channel_13						13		/*10x(ADC3 - ADC2)*/
#define ADC_Channel_15						15		/*200x(ADC3 - ADC2)*/

/*Differential Input without Gain*/
#define ADC_Channel_16						16		/*(ADC0 - ADC1)*/
#define ADC_Channel_18						18		/*(ADC2 - ADC1)*/
#define ADC_Channel_19						19		/*(ADC3 - ADC1)*/
#define ADC_Channel_20						20		/*(ADC4 - ADC1)*/
#define ADC_Channel_21						21		/*(ADC5 - ADC1)*/
#define ADC_Channel_22						22		/*(ADC6 - ADC1)*/
#define ADC_Channel_23						23		/*(ADC7 - ADC1)*/

#define ADC_Channel_24						24		/*(ADC0 - ADC2)*/
#define ADC_Channel_25						25		/*(ADC1 - ADC2)*/
#define ADC_Channel_27						27		/*(ADC3 - ADC2)*/
#define ADC_Channel_28						28		/*(ADC4 - ADC2)*/
#define ADC_Channel_29						29		/*(ADC5 - ADC2)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*ADC Voltage Reference Select*/
#define ADC_VOLTAGE_REF_AREF	 			0		/*ADC Voltage Reference is AREF pin*/
#define ADC_VOLTAGE_REF_AVCC 				1		/*ADC Voltage Reference is AVCC pin (with external capacitor at AREF pin)*/
#define ADC_VOLTAGE_REF_2_56V		 		3		/*ADC Voltage Reference is Internal 2.56V (with external capacitor at AREF pin)*/

/*ADC ADJUST mode*/
#define ADC_RIGHT_ADJUSTED					0		/*(ADC = 0000 00XX	XXXX XXXX)*/
#define ADC_LEFT_ADJUSTED					1		/*(ADC = XXXX XXXX	XX00 0000)*/

/*ADC Interrupt Status*/
#define ADC_INT_DISABLE						0		/*ADC Interrupt Disable*/
#define ADC_INT_ENABLE						1		/*ADC Interrupt Enable*/

/*ADC Auto Trigger Enable*/
#define ADC_MODE_SINGLE_CONVERSION			0		/*Auto Trigger Disable*/
#define ADC_MODE_AUTO_TRIGGER				1		/*Auto Trigger Enable*/

/*ADC AUTO TRIGGER Source*/
#define ADC_ATS_FREE_RUNNING_msk			0x00	/*(0000 0000)	Free Running mode*/
#define ADC_ATS_ANALOG_COMP_msk				0x20	/*(0010 0000)	Analog Comparator*/
#define ADC_ATS_EXTI0_msk					0x40	/*(0100 0000)	External Interrupt Request 0*/
#define ADC_ATS_TIMER0_COMP_msk				0x60	/*(0110 0000)	Timer/Counter0 Compare Match*/
#define ADC_ATS_TIMER0_OVF_msk				0x80	/*(1000 0000)	Timer/Counter0 Overflow*/
#define ADC_ATS_TIMER1_COMP_msk				0xA0	/*(1010 0000)	Timer/Counter1 Compare Match B*/
#define ADC_ATS_TIMER1_OVF_msk				0xC0	/*(1100 0000)	Timer/Counter1 Overflow*/
#define ADC_ATS_TIMER1_CAPT_msk				0xE0	/*(1110 0000)	Timer/Counter1 Capture Event*/

/*ADC prescaler*/
#define ADC_PRESCALER_2_msk					0x00	/*ADC Frequency = F_CPU / 2	  (CLK/2)*/
#define ADC_PRESCALER_4_msk					0x02	/*ADC Frequency = F_CPU / 4	  (CLK/4)*/
#define ADC_PRESCALER_8_msk					0x03	/*ADC Frequency = F_CPU / 8	  (CLK/8)*/
#define ADC_PRESCALER_16_msk				0x04	/*ADC Frequency = F_CPU / 16  (CLK/16)*/
#define ADC_PRESCALER_32_msk				0x05	/*ADC Frequency = F_CPU / 32  (CLK/32)*/
#define ADC_PRESCALER_64_msk				0x06	/*ADC Frequency = F_CPU / 64  (CLK/64)*/
#define ADC_PRESCALER_128_msk				0x07	/*ADC Frequency = F_CPU / 128 (CLK/128)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define ADC_PRESCALER_clr_msk 				0xF8	/*ADC PRESCALER Clear mask*/
#define ADC_CHANNEL_clr_msk 				0xE0	/*ADC channel clear mask*/
#define ADC_AUTO_TRIG_clr_msk 				0x1F	/*ADC AUTO TRIGGER Source clear mask*/
/*_______________________________________________________________________________________________*/


#endif /* ADC_DEF_H_ */

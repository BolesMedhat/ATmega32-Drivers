/******************************************************************************
 * @file    TIMER1_def.h
 * @author  Boles Medhat
 * @brief   TIMER1 Driver Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * and mode macros required for configuring and interacting with the TIMER1
 * module on the ATmega32 microcontroller.
 *
 * These definitions are intended to be used by the `TIMER1` driver and other components
 * that require interaction with the TIMER1 module.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER1_DEF_H_
#define TIMER1_DEF_H_

#include "../../LIB/STD_TYPES.h"

/*---------------------------------------    Registers    ---------------------------------------*/

/*Timer/Counter1 Registers*/
#define TCNT1L								*((volatile uint8 *)0x4C)	/*Timer/Counter1 LOW Register*/
#define TCNT1H								*((volatile uint8 *)0x4D)	/*Timer/Counter1 HIGH Register*/
#define TCNT1								*((volatile uint16 *)0x4C)	/*Timer/Counter1 Register*/

/*Output Compare 1A Registers*/
#define OCR1AL								*((volatile uint8 *)0x4A)	/*Output Compare Register 1 A LOW*/
#define OCR1AH								*((volatile uint8 *)0x4B)	/*Output Compare Register 1 A HIGH*/
#define OCR1A								*((volatile uint16 *)0x4A)	/*Output Compare Register 1 A*/

/*Output Compare 1B Registers*/
#define OCR1BL								*((volatile uint8 *)0x48)	/*Output Compare Register 1 B LOW*/
#define OCR1BH								*((volatile uint8 *)0x49)	/*Output Compare Register 1 B HIGH*/
#define OCR1B								*((volatile uint16 *)0x48)	/*Output Compare Register 1 B*/

/*Input Capture 1 Registers*/
#define ICR1L								*((volatile uint8 *)0x46)	/*Input Capture Register 1 LOW*/
#define ICR1H								*((volatile uint8 *)0x47)	/*Input Capture Register 1 HIGH*/
#define ICR1								*((volatile uint16 *)0x46)	/*Input Capture Register 1*/

/*Timer/Counter1 Control Registers*/
#define TCCR1A								*((volatile uint8 *)0x4F)	/*Timer/Counter1 Control Register A*/
#define TCCR1B								*((volatile uint8 *)0x4E)	/*Timer/Counter1 Control Register B*/

/*Interrupt Registers*/
#define TIMSK								*((volatile uint8 *)0x59)	/*Timer/Counter Interrupt Mask Register*/
#define TIFR								*((volatile uint8 *)0x58)	/*Timer/Counter Interrupt Flag Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/

/*OC1A and OC1B pins Direction Register*/
#define DDRD 								*((volatile uint8 *)0x31)	/*Port D Data Direction Register (OC1A and OC1B pins Register)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*TCCR1A Register*/
#define WGM10								0	/*Waveform Generation Mode Bit 0*/
#define WGM11								1	/*Waveform Generation Mode Bit 1*/
#define FOC1B								2	/*Force Output Compare for Channel B*/
#define FOC1A								3	/*Force Output Compare for Channel A*/
#define COM1B0								4	/*Compare Output Mode for Channel B Bit 0*/
#define COM1B1								5	/*Compare Output Mode for Channel B Bit 1*/
#define COM1A0								6	/*Compare Output Mode for Channel A Bit 0*/
#define COM1A1								7	/*Compare Output Mode for Channel A Bit 1*/

/*TCCR1B Register*/
#define CS10								0	/*Clock Select Bit 0*/
#define CS11								1	/*Clock Select Bit 1*/
#define CS12								2	/*Clock Select Bit 2*/
#define WGM12								3	/*Waveform Generation Mode Bit 2*/
#define WGM13								4	/*Waveform Generation Mode Bit 3*/
#define ICES1								6	/*Input Capture Edge Select*/
#define ICNC1								7	/*Input Capture Noise Canceler*/

/*TIMSK Register*/
#define TOIE1								2	/*Timer/Counter1, Overflow Interrupt Enable*/
#define OCIE1B								3	/*Timer/Counter1, Output Compare B Match Interrupt Enable*/
#define OCIE1A								4	/*Timer/Counter1, Output Compare A Match Interrupt Enable*/
#define TICIE1								5	/*Timer/Counter1, Input Capture Interrupt Enable*/

/*TIFR Register*/
#define TOV1								2	/*Timer/Counter1, Overflow Flag*/
#define OCF1B								3	/*Timer/Counter1, Output Compare B Match Flag*/
#define OCF1A								4	/*Timer/Counter1, Output Compare A Match Flag*/
#define ICF1								5	/*Timer/Counter1, Input Capture Flag*/


/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/

/*DDRD Register*/
#define OC1B_PIN							4	/*Compare Match Output 1 B pin from pinout*/
#define OC1A_PIN							5	/*Compare Match Output 1 A pin from pinout*/
#define ICP1_PIN							6	/*Input Capture 1 pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*TIMER1 Interrupt labels*/
#define TIMER1_OVF_ID						0		/*TIMER1 Overflow 		 Interrupt ID for functions parameters*/
#define TIMER1_COMPA_ID						1		/*TIMER1 Compare Match A Interrupt ID for functions parameters */
#define TIMER1_COMPB_ID						2		/*TIMER1 Compare Match B Interrupt ID for functions parameters */
#define TIMER1_CAPT_ID						3		/*TIMER1 Capture Event 	 Interrupt ID for functions parameters */

/*TIMER1 Max Capacity*/
#define TIMER1_MAX_CAPACITY					0xFFFF	/*max capacity for Timer1 register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/


/*TIMER1 Clock Source*/
#define TIMER1_NO_CLOCK_SOURCE				0	/*No clock source (Timer/Counter stopped)*/
#define TIMER1_NO_PRESCALER					1	/*TIMER1 Frequency = F_CPU (No prescaling)*/
#define TIMER1_PRESCALER_8					2	/*TIMER1 Frequency = F_CPU / 8	  (CLK/8)*/
#define TIMER1_PRESCALER_64					3	/*TIMER1 Frequency = F_CPU / 64	  (CLK/64)*/
#define TIMER1_PRESCALER_256				4	/*TIMER1 Frequency = F_CPU / 256  (CLK/256)*/
#define TIMER1_PRESCALER_1024				5	/*TIMER1 Frequency = F_CPU / 1024 (CLK/1024)*/
#define TIMER1_EXT_CLOCK_FALLING			6	/*External clock source on T1 pin. Clock on falling edge*/
#define TIMER1_EXT_CLOCK_RISING				7	/*External clock source on T1 pin. Clock on rising  edge*/

/*TIMER1 Waveform Generation Mode (Timer mode)*/
#define TIMER1_NORMAL_MODE					0	/*Normal mode (TOP = 0xFFFF)*/
#define TIMER1_PWM_8BIT_MODE				1	/*PWM, Phase Correct, 8-bit (TOP = 0x00FF)*/
#define TIMER1_PWM_9BIT_MODE				2	/*PWM, Phase Correct, 9-bit (TOP = 0x01FF)*/
#define TIMER1_PWM_10BIT_MODE				3	/*PWM, Phase Correct, 10-bit (TOP = 0x03FF)*/
#define TIMER1_CTC_OCR1A_MODE				4	/*CTC mode (TOP = OCR1A)*/
#define TIMER1_FAST_PWM_8BIT_MODE			5	/*Fast PWM, 8-bit (TOP = 0x00FF)*/
#define TIMER1_FAST_PWM_9BIT_MODE			6	/*Fast PWM, 8-bit (TOP = 0x01FF)*/
#define TIMER1_FAST_PWM_10BIT_MODE			7	/*Fast PWM, 8-bit (TOP = 0x03FF)*/
#define TIMER1_PFC_PWM_ICR1_MODE			8	/*PWM, Phase and Frequency Correct (TOP = ICR1)*/
#define TIMER1_PFC_PWM_OCR1A_MODE			9	/*PWM, Phase and Frequency Correct (TOP = OCR1A)*/
#define TIMER1_PWM_ICR1_MODE				10	/*PWM, Phase Correct (TOP = ICR1)*/
#define TIMER1_PWM_OCR1A_MODE				11	/*PWM, Phase Correct (TOP = OCR1A)*/
#define TIMER1_CTC_ICR1_MODE				12	/*CTC mode (TOP = ICR1)*/
#define TIMER1_FAST_PWM_ICR1_MODE			14	/*Fast PWM (TOP = ICR1)*/
#define TIMER1_FAST_PWM_OCR1A_MODE			15	/*Fast PWM (TOP = OCR1A)*/

/*Compare Match Output Mode, non-PWM Mode (OC1A Pin)*/
#define TIMER1_COM_DISCONNECT_OC1A			0	/*Normal port operation, OC1A disconnected*/
#define TIMER1_COM_TOGGLE_OC1A				1	/*Toggle OC1A on compare match*/
#define TIMER1_COM_CLEAR_OC1A				2	/*Clear OC1A on compare match*/
#define TIMER1_COM_SET0_OC1A				3	/*Set OC1A on compare match*/

/*Compare Match Output Mode, non-PWM Mode (OC1B Pin)*/
#define TIMER1_COM_DISCONNECT_OC1B			0	/*Normal port operation, OC1B disconnected*/
#define TIMER1_COM_TOGGLE_OC1B				1	/*Toggle OC1B on compare match*/
#define TIMER1_COM_CLEAR_OC1B				2	/*Clear OC1B on compare match*/
#define TIMER1_COM_SET0_OC1B				3	/*Set OC1B on compare match*/

/*Compare Match Output Mode, any PWM Mode (OC1A Pin)*/
#define TIMER1_COM_DISCONNECT_OC1A			0	/*Normal port operation, OC1A disconnected*/
#define TIMER1_COM_NON_INVERTING_OC1A		2	/*OC1A in non inverting mode*/
#define TIMER1_COM_INVERTING_OC1A			3	/*OC1A in inverting mode*/

/*Compare Match Output Mode, any PWM Mode (OC1B Pin)*/
#define TIMER1_COM_DISCONNECT_OC1B			0	/*Normal port operation, OC1B disconnected*/
#define TIMER1_COM_NON_INVERTING_OC1B		2	/*OC1B in non inverting mode*/
#define TIMER1_COM_INVERTING_OC1B			3	/*OC1B in inverting mode*/

/*the Timer1 Overflow Interrupt Status*/
#define TIMER1_OVF_INT_DISABLE				0	/*Timer1 Overflow Interrupt Disable*/
#define TIMER1_OVF_INT_ENABLE				1	/*Timer1 Overflow Interrupt Enable*/

/*the Timer1 Compare Match A Interrupt Status*/
#define TIMER1_COMPA_INT_DISABLE			0	/*Timer1 Compare Match A Interrupt Disable*/
#define TIMER1_COMPA_INT_ENABLE				1	/*Timer1 Compare Match A Interrupt Enable*/

/*the Timer1 Compare Match B Interrupt Status*/
#define TIMER1_COMPB_INT_DISABLE			0	/*Timer1 Compare Match B Interrupt Disable*/
#define TIMER1_COMPB_INT_ENABLE				1	/*Timer1 Compare Match B Interrupt Enable*/

/*the Timer1 Capture Event Interrupt Status*/
#define TIMER1_CAPT_INT_DISABLE				0	/*Timer1 Capture Event Interrupt Disable*/
#define TIMER1_CAPT_INT_ENABLE				1	/*Timer1 Capture Event Interrupt Enable*/

/*the Capture Noise Canceler Status*/
#define ICU_NOISE_CANCELER_DISABLE			0	/*Input Capture Noise Canceler Disable*/
#define ICU_NOISE_CANCELER_ENABLE			1	/*Input Capture Noise Canceler Enable*/

/*the Input Capture Signal Start Edge Status*/
#define ICU_FALLING_EDGE					0	/*the Input Capture Signal Start Edge is falling Edge*/
#define ICU_RISING_EDGE						1	/*the Input Capture Signal Start Edge is rising Edge*/

/*the Count mode (for TIMER01GetTime_ms function)*/
#define TIMER1_COUNT_DISABLE				0	/*do not use TIMER1_Counter in ISR (TIMER1_GetTime_ms function will not work and TIMER1_Counter variable will be unused)*/
#define TIMER1_COUNT_ENABLE					1	/*use TIMER1_Counter in ISR (TIMER1_GetTime_ms function will work and TIMER1_Counter variable will be used)*/


/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define TIMER1_PRESCALER_clr_msk 			0xF8	/*TIMER1 PRESCALER Clear mask (0B11111000)*/
#define TIMER1_WGM1_10_clr_msk				0xFC	/*TIMER1 Waveform Generation Mode WGM11:0 Bits Clear mask*/
#define TIMER1_WGM1_32_clr_msk				0xE7	/*TIMER1 Waveform Generation Mode WGM13:2 Bits Clear mask*/
/*_______________________________________________________________________________________________*/


#endif /* TIMER1_DEF_H_ */

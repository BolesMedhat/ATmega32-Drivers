/******************************************************************************
 * @file    TIMER2_config.h
 * @author  Boles Medhat
 * @brief   TIMER2 Driver Configuration Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the TIMER2 driver for ATmega32
 * microcontroller. It allows for setting up various parameters such as clock source,
 * prescaler, waveform generation mode, interrupt settings, and software time tracking mode.
 *
 * @note
 * - All available choices (e.g., clock sources, modes, output settings) are
 *   defined in `TIMER2_def.h` and explained with comments there.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER2_CONFIG_H_
#define TIMER2_CONFIG_H_

#include "TIMER2_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif

/*Value that set in TCNT2 Register in Initialization function in normal mode*/
#define TIMER2_TCNT2_PRELOAD				0

/*Value that set in OCR2 Register in Initialization function in CTC mode*/
#define TIMER2_OCR2_PRELOAD					0


/*Set TIMER2 Clock Source
 * choose between:
 * 1. TIMER2_NO_CLOCK_SOURCE
 * 2. TIMER2_NO_PRESCALER
 * 3. TIMER2_PRESCALER_8
 * 4. TIMER2_PRESCALER_32
 * 5. TIMER2_PRESCALER_64
 * 6. TIMER2_PRESCALER_128
 * 7. TIMER2_PRESCALER_256
 * 8. TIMER2_PRESCALER_1024
 */
#define TIMER2_CLOCK_SOURCE_msk				TIMER2_PRESCALER_64


/*Set TIMER2 Waveform Generation Mode
 * choose between:
 * 1. TIMER2_NORMAL_MODE
 * 2. TIMER2_PWM_MODE
 * 3. TIMER2_CTC_MODE
 * 4. TIMER2_FAST_PWM_MODE
 */
#define TIMER2_WAVEFORM_GENERATION_MODE		TIMER2_NORMAL_MODE



#if   TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER2_COM_DISCONNECT_OC2			<--the most used
	 * 2. TIMER2_COM_TOGGLE_OC2				//Warning: DIO will not be able to control this pin
	 * 3. TIMER2_COM_CLEAR_OC2				//Warning: DIO will not be able to control this pin
	 * 4. TIMER2_COM_SET_OC2				//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE				TIMER2_COM_DISCONNECT_OC2


	/*Set TIMER2 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER2_OVF_INT_DISABLE
	 * 2. TIMER2_OVF_INT_ENABLE				<--the most used
	 */
	#define  TIMER2_OVF_INT_STATUS			TIMER2_OVF_INT_ENABLE


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER2_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER2_COMP_INT_ENABLE
	 */
	#define  TIMER2_COMP_INT_STATUS			TIMER2_COMP_INT_DISABLE


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_NON_INVERTING_OC2		//Warning: DIO will not be able to control this pin	<--the most used
	 * 3. TIMER2_COM_INVERTING_OC2			//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE				TIMER2_COM_NON_INVERTING_OC2


	/*Set TIMER2 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER2_OVF_INT_DISABLE
	 * 2. TIMER2_OVF_INT_ENABLE				<--if you need function TIMER2_GetTime_ms() (not recommended with this mode)
	 */
	#define  TIMER2_OVF_INT_STATUS			TIMER2_OVF_INT_ENABLE


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER2_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER2_COMP_INT_ENABLE
	 */
	#define  TIMER2_COMP_INT_STATUS			TIMER2_COMP_INT_DISABLE


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER2_COM_DISCONNECT_OC2			<--the most used
	 * 2. TIMER2_COM_TOGGLE_OC2				//Warning: DIO will not be able to control this pin
	 * 3. TIMER2_COM_CLEAR_OC2				//Warning: DIO will not be able to control this pin
	 * 4. TIMER2_COM_SET_OC2				//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE				TIMER2_COM_DISCONNECT_OC2


	/*Set Timer2 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER2_OVF_INT_DISABLE			<--the most used
	 * 2. TIMER2_OVF_INT_ENABLE
	 */
	#define  TIMER2_OVF_INT_STATUS			TIMER2_OVF_INT_DISABLE


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER2_COMP_INT_DISABLE
	 * 2. TIMER2_COMP_INT_ENABLE			<--the most used
	 */
	#define  TIMER2_COMP_INT_STATUS			TIMER2_COMP_INT_ENABLE


#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER2_COM_DISCONNECT_OC2
	 * 2. TIMER2_COM_NON_INVERTING_OC2		//Warning: DIO will not be able to control this pin	<--the most used
	 * 3. TIMER2_COM_INVERTING_OC2			//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER2_OC2_MODE				TIMER2_COM_NON_INVERTING_OC2


	/*Set TIMER2 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER2_OVF_INT_DISABLE
	 * 2. TIMER2_OVF_INT_ENABLE				<--if you need function TIMER2_GetTime_ms()
	 */
	#define  TIMER2_OVF_INT_STATUS			TIMER2_OVF_INT_ENABLE


	/*Set TIMER2 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER2_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER2_COMP_INT_ENABLE
	 */
	#define  TIMER2_COMP_INT_STATUS			TIMER2_COMP_INT_DISABLE


#endif


/*Set the Time Tracking mode (Software mode for TIMER2_GetTime_ms() function)
 * choose between:
 * 1. TIMER2_TIME_TRACKING_DISABLE
 * 2. TIMER2_TIME_TRACKING_ENABLE
 */
#define TIMER2_SW_TIME_TRACKING				TIMER2_TIME_TRACKING_ENABLE





/*Set Automatically*/
/*TIMER2_FREQ_DIVIDER = prescaler * 256(timer cup)*1000(s to ms)*/
#if   TIMER2_CLOCK_SOURCE_msk == TIMER2_NO_PRESCALER
	#define TIMER2_FREQ_DIVIDER				0x3E800UL		/* 1*256*1000    = 256000 */
	#define TIMER2_PRESCALER				1
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_8
	#define TIMER2_FREQ_DIVIDER				0x1F4000UL		/* 8*256*1000    = 2048000 */
	#define TIMER2_PRESCALER				8
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_32
	#define TIMER2_FREQ_DIVIDER				0x7D0000UL		//* 32*256*1000  = 8192000 */
	#define TIMER2_PRESCALER				32
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_64
	#define TIMER2_FREQ_DIVIDER				0xFA0000UL		//* 64*256*1000  = 16384000 */
	#define TIMER2_PRESCALER				64
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_128
	#define TIMER2_FREQ_DIVIDER				0x1F40000UL		//* 128*256*1000 = 32768000 */
	#define TIMER2_PRESCALER				128
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_256
	#define TIMER2_FREQ_DIVIDER				0x3E80000UL		/* 256*256*1000  = 65536000 */
	#define TIMER2_PRESCALER				256
#elif TIMER2_CLOCK_SOURCE_msk == TIMER2_PRESCALER_1024
	#define TIMER2_FREQ_DIVIDER				0xFA00000UL		/* 1024*256*1000 = 262144000 */
	#define TIMER2_PRESCALER				1024
#endif


#endif /* TIMER2_CONFIG_H_ */

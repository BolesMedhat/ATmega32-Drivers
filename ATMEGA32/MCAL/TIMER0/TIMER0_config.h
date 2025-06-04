/******************************************************************************
 * @file    TIMER0_config.h
 * @author  Boles Medhat
 * @brief   TIMER0 Driver Configuration Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-02]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the TIMER0 driver for ATmega32
 * microcontroller. It allows for setting up various parameters such as clock source,
 * prescaler, waveform generation mode, interrupt settings, and software time tracking mode.
 *
 * @note
 * - All available choices (e.g., clock sources, modes, output settings) are
 *   defined in `TIMER0_def.h` and explained with comments there.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#include "TIMER0_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*Value that set in TCNT0 Register in Initialization function in normal mode*/
#define TIMER0_TCNT0_PRELOAD				0

/*Value that set in OCR0 Register in Initialization function in CTC mode*/
#define TIMER0_OCR0_PRELOAD					0


/*Set TIMER0 Clock Source
 * choose between:
 * 1. TIMER0_NO_CLOCK_SOURCE
 * 2. TIMER0_NO_PRESCALER
 * 3. TIMER0_PRESCALER_8
 * 4. TIMER0_PRESCALER_64
 * 5. TIMER0_PRESCALER_256
 * 6. TIMER0_PRESCALER_1024
 * 7. TIMER0_EXT_CLOCK_FALLING
 * 8. TIMER0_EXT_CLOCK_RISING
 */
#define TIMER0_CLOCK_SOURCE_msk				TIMER0_PRESCALER_8


/*Set TIMER0 Waveform Generation Mode
 * choose between:
 * 1. TIMER0_NORMAL_MODE
 * 2. TIMER0_PWM_MODE
 * 3. TIMER0_CTC_MODE
 * 4. TIMER0_FAST_PWM_MODE
 */
#define TIMER0_WAVEFORM_GENERATION_MODE		TIMER0_NORMAL_MODE



#if   TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER0_COM_DISCONNECT_OC0			<--the most used
	 * 2. TIMER0_COM_TOGGLE_OC0				//Warning: DIO will not be able to control this pin
	 * 3. TIMER0_COM_CLEAR_OC0				//Warning: DIO will not be able to control this pin
	 * 4. TIMER0_COM_SET_OC0				//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE				TIMER0_COM_DISCONNECT_OC0


	/*Set Timer0 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER0_OVF_INT_DISABLE
	 * 2. TIMER0_OVF_INT_ENABLE				<--the most used
	 */
	#define  TIMER0_OVF_INT_STATUS			TIMER0_OVF_INT_ENABLE


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER0_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER0_COMP_INT_ENABLE
	 */
	#define  TIMER0_COMP_INT_STATUS			TIMER0_COMP_INT_DISABLE


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_NON_INVERTING_OC0		//Warning: DIO will not be able to control this pin	<--the most used
	 * 3. TIMER0_COM_INVERTING_OC0			//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE				TIMER0_COM_NON_INVERTING_OC0


	/*Set Timer0 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER0_OVF_INT_DISABLE
	 * 2. TIMER0_OVF_INT_ENABLE				<--if you need TIMER0_GetTime_ms() function (not recommended with this mode)
	 */
	#define  TIMER0_OVF_INT_STATUS			TIMER0_OVF_INT_ENABLE


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER0_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER0_COMP_INT_ENABLE
	 */
	#define  TIMER0_COMP_INT_STATUS			TIMER0_COMP_INT_DISABLE


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER0_COM_DISCONNECT_OC0			<--the most used
	 * 2. TIMER0_COM_TOGGLE_OC0				//Warning: DIO will not be able to control this pin
	 * 3. TIMER0_COM_CLEAR_OC0				//Warning: DIO will not be able to control this pin
	 * 4. TIMER0_COM_SET_OC0				//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE				TIMER0_COM_DISCONNECT_OC0


	/*Set Timer0 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER0_OVF_INT_DISABLE			<--the most used
	 * 2. TIMER0_OVF_INT_ENABLE
	 */
	#define  TIMER0_OVF_INT_STATUS			TIMER0_OVF_INT_DISABLE


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER0_COMP_INT_DISABLE
	 * 2. TIMER0_COMP_INT_ENABLE			<--the most used
	 */
	#define  TIMER0_COMP_INT_STATUS			TIMER0_COMP_INT_ENABLE


#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE

	/*Set Compare Output Mode
	 * choose between:
	 * 1. TIMER0_COM_DISCONNECT_OC0
	 * 2. TIMER0_COM_NON_INVERTING_OC0		//Warning: DIO will not be able to control this pin	<--the most used
	 * 3. TIMER0_COM_INVERTING_OC0			//Warning: DIO will not be able to control this pin
	 */
	#define  TIMER0_OC0_MODE				TIMER0_COM_NON_INVERTING_OC0


	/*Set Timer0 Overflow Interrupt Status
	 * choose between:
	 * 1. TIMER0_OVF_INT_DISABLE
	 * 2. TIMER0_OVF_INT_ENABLE				<--if you need TIMER0_GetTime_ms() function
	 */
	#define  TIMER0_OVF_INT_STATUS			TIMER0_OVF_INT_ENABLE


	/*Set Timer0 Compare Match Interrupt Status
	 * choose between:
	 * 1. TIMER0_COMP_INT_DISABLE			<--the most used
	 * 2. TIMER0_COMP_INT_ENABLE
	 */
	#define  TIMER0_COMP_INT_STATUS			TIMER0_COMP_INT_DISABLE


#endif


/*Set the Time Tracking mode (Software mode for TIMER0_GetTime_ms() function)
 * choose between:
 * 1. TIMER0_TIME_TRACKING_DISABLE
 * 2. TIMER0_TIME_TRACKING_ENABLE
 */
#define TIMER0_SW_TIME_TRACKING				TIMER0_TIME_TRACKING_ENABLE





/*Set Automatically*/
/*TIMER0_FREQ_DIVIDER = prescaler * 256(timer cup)*1000(s to ms)*/
#if   TIMER0_CLOCK_SOURCE_msk == TIMER0_NO_PRESCALER
	#define TIMER0_FREQ_DIVIDER				0x3E800UL		/* 1*256*1000    = 256000 */
	#define TIMER0_PRESCALER				1
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_8
	#define TIMER0_FREQ_DIVIDER				0x1F4000UL		/* 8*256*1000    = 2048000 */
	#define TIMER0_PRESCALER				8
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_64
	#define TIMER0_FREQ_DIVIDER				0xFA0000UL		/* 64*256*1000   = 16384000 */
	#define TIMER0_PRESCALER				64
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_256
	#define TIMER0_FREQ_DIVIDER				0x3E80000UL		/* 256*256*1000  = 65536000 */
	#define TIMER0_PRESCALER				256
#elif TIMER0_CLOCK_SOURCE_msk == TIMER0_PRESCALER_1024
	#define TIMER0_FREQ_DIVIDER				0xFA00000UL		/* 1024*256*1000 = 262144000 */
	#define TIMER0_PRESCALER				1024
#endif


#endif /* TIMER0_CONFIG_H_ */

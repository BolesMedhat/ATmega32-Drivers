/****************************************************************************
 * @file    SERVO_config.h
 * @author  Boles Medhat
 * @brief   Servo Motor Driver Configuration Header File
 * @version 1.0
 * @date    [2025-04-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This configuration file checks if the PWM interval exceeds the maximum timer capacity, which
 * could lead to incorrect PWM signal generation. If necessary, you will be
 * prompted to adjust the prescaler value to ensure proper operation.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the TIMER1 module in normal mode **before**
 * 				   calling any SERVO driver function. This driver does not initialize
 *	 	 	 	   TIMER1 module in normal mode internally.
 * - This driver supports up to 9 servo motors.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef SERVO_CONFIG_H_
#define SERVO_CONFIG_H_

#include "SERVO_def.h"
#include "../../MCAL/TIMER1/TIMER1.h"


/* You must initialize Timer1 manually "TIMER1_Init()" before using this driver */
#ifndef TIMER1_IN_HAL
#define TIMER1_IN_HAL
	#warning "⚠️ Initialize Timer1 manually before using this driver."
#endif


/* Configure Timer1 to Normal mode */
#if TIMER1_WAVEFORM_GENERATION_MODE != TIMER1_NORMAL_MODE
	#warning "⚠️ Configure Timer1 in Normal mode."
#endif


/* Enable Timer1 overflow interrupt */
#if TIMER1_OVF_INT_STATUS != TIMER1_OVF_INT_ENABLE
	#warning "⚠️ Enable Timer1 overflow interrupt."
#endif

/*Check if the PWM interval exceeds the maximum timer capacity*/
#if ( SERVO_PWM_INTERVAL_TICKS > TIMER1_MAX_CAPACITY )
	#error "Invalid TIMER1_PRESCALER for Servo!, Increase Prescaler value"
#endif


#endif /* SERVO_CONFIG_H_ */

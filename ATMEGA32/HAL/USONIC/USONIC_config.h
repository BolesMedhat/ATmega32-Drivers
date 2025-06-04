/****************************************************************************
 * @file    USONIC_config.h
 * @author  Boles Medhat
 * @brief   Ultrasonic Sensor Driver Configuration Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file contains the configuration settings for the USONIC driver.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef USONIC_CONFIG_H_
#define USONIC_CONFIG_H_

#include "USONIC_def.h"
#include "../../MCAL/TIMER1/TIMER1.h"


/* You must initialize Timer1 manually "TIMER1_Init()" before using this driver */
#ifndef TIMER1_IN_HAL
#define TIMER1_IN_HAL
	#warning "⚠️ Initialize Timer1 manually before using this driver."
#endif


#endif /* USONIC_CONFIG_H_ */

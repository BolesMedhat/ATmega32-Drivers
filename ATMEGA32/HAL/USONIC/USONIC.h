/****************************************************************************
 * @file    USONIC.h
 * @author  Boles Medhat
 * @brief   Ultrasonic Sensor Driver Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides functionality for interfacing with ultrasonic sensors
 * (such as HC-SR04). It allows the measurement of distances by triggering
 * the sensor and measuring the time taken for the echo to return.
 * The distance is calculated in centimeters.
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
#ifndef USONIC_H_
#define USONIC_H_

#include "USONIC_config.h"
#include <util/delay.h>


/*
 * @brief  Reads the distance from the ultrasonic sensor.
 *
 * This function triggers the ultrasonic sensor to emit a pulse, waits for the echo
 * signal, and calculates the pulse width. The pulse width is then used to compute
 * the distance in centimeters.
 *
 * @param usonic   A structure of type `Usonic` containing:
 *                 - port_id:  Port connected to the ultrasonic sensor trigger and echo pins
 *                 - trig_pin: Pin ID for the trigger signal
 *                 - echo_pin: Pin ID for the echo signal
 *
 * @return: The distance in centimeters.
 */
uint16 USONIC_Read( Usonic usonic );


#endif /* USONIC_H_ */

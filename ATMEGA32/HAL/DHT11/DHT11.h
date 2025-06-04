/****************************************************************************
 * @file    DHT11.h
 * @author  Boles Medhat
 * @brief   DHT11 Driver Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides an interface to communicate with the DHT11 temperature
 * and humidity sensor using a single-wire protocol. It supports reading the
 * sensor values and validating them using the built-in checksum mechanism.
 *
 * @note
 * - Requires `DHT11_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef DHT11_H_
#define DHT11_H_

#include "DHT11_config.h"
#include "../../MCAL/DIO/DIO.h"
#include <util/delay.h>


/*
 * @brief Reads temperature and humidity data from the DHT11 sensor.
 *
 * This function initiates communication with the DHT11 sensor using a start signal,
 * then reads a 40-bit response (5 bytes) containing humidity, temperature, and a checksum.
 * It verifies the checksum and returns the data in a `DHT11_Data` structure.
 *
 * @return (DHT11_Data) structure containing:
 * - `temperature` (uint8): Temperature in Celsius.
 * - `humidity` (uint8): Relative humidity percentage.
 * - `status` (uint8):
 *    - 0: Success.
 *    - 1: Checksum mismatch.
 *    - 2: Timeout or no response from sensor.
 */
DHT11_Data DHT11_Read(void);


#endif /* DHT11_H_ */

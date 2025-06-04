/****************************************************************************
 * @file    LM35.h
 * @author  Boles Medhat
 * @brief   LM35 Temperature Sensor Driver Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver reads the analog voltage from the LM35 temperature sensor using the ADC,
 * converts it to a temperature in the desired unit.
 *
 * The temperature conversion is based on the LM35 characteristics:
 * - 10mV per °C (i.e., 1V = 100°C)
 * - Operating range: -55°C to +150°C
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the ADC module **before** using this driver.
 *   			   The joystick driver assumes the ADC is configured for 10-bit readings.
 * - Requires `LM35_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef LM35_H_
#define LM35_H_

#include "LM35_config.h"


/*
 * @brief Reads the current temperature from the LM35 sensor and returns it in the configured unit.
 *
 * This function reads the ADC value from the LM35 temperature sensor,
 * converts it into a voltage, then calculates the corresponding
 * temperature value in the configured unit in `LM35_config.h` (Celsius, Fahrenheit, or Kelvin).
 *
 * @return: The temperature in the configured unit:
 *         - Celsius    if `LM35_TEMP_UNIT` is `LM35_TEMP_UNIT_CELSIUS`,
 *         - Fahrenheit if `LM35_TEMP_UNIT` is `LM35_TEMP_UNIT_FAHRENHEIT`,
 *         - Kelvin     if `LM35_TEMP_UNIT` is `LM35_TEMP_UNIT_KELVIN`.
 */
uint16 LM35_getTemperature( void );


#endif /* LM35_H_ */

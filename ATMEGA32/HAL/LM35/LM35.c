/****************************************************************************
 * @file    LM35.c
 * @author  Boles Medhat
 * @brief   LM35 Temperature Sensor Driver Source File
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


#include "LM35.h"





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
uint16 LM35_getTemperature( void )
{

	/* Convert ADC Steps to Voltage ( 1023 Steps = LM35_VOLT_REF V )*/
	float32 Volt = ( ADC_Read_10_Bits( LM35_CANNEL ) * LM35_VOLT_REF) / 1023.0;

	/* Convert Voltage to Temperature in Celsius (1 V = 100°C for LM35 Sensor)*/
	uint8 TempInCelsius = Volt * 100;


	/* Check the Return Temperature Unit */
	#if   LM35_TEMP_UNIT == LM35_TEMP_UNIT_CELSIUS

		/* Return in Celsius */
		return TempInCelsius;

	#elif LM35_TEMP_UNIT == LM35_TEMP_UNIT_FAHRENHEIT

		/* Convert Celsius to Fahrenheit */
		return (TempInCelsius * 9 / 5.0 ) + 32;

	#elif LM35_TEMP_UNIT == LM35_TEMP_UNIT_KELVIN

		/* Convert Celsius to Kelvin */
		return TempInCelsius + 273;

	#else
		/* Make an Error */
		#error "Wrong \"LM35_TEMP_UNIT\" configuration option"
	#endif
}



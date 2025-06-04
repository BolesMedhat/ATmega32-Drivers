/****************************************************************************
 * @file    LM35_config.h
 * @author  Boles Medhat
 * @brief   LM35 Configuration Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the LM35 temperature sensor driver.
 * It allows for setting up parameters such as ADC channel, temperature unit.
 * - The ADC channel connected to the LM35 sensor.
 * - The desired temperature unit for return values (Celsius, Fahrenheit, or Kelvin).
 * - The ADC voltage reference used in conversion.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the ADC module **before** using this driver.
 *   			   The joystick driver assumes the ADC is configured for 10-bit readings.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef LM35_CONFIG_H_
#define LM35_CONFIG_H_

#include "LM35_def.h"
#include "../../MCAL/ADC/ADC.h"


/*Set the LM35 Channel
 * choose between:
 * 1. ADC_Channel_0
 * 2. ADC_Channel_1
 * 3. ADC_Channel_2
 * 4. ADC_Channel_3
 * 5. ADC_Channel_4
 * 6. ADC_Channel_5
 * 7. ADC_Channel_6
 * 8. ADC_Channel_7
 */
#define LM35_CANNEL							ADC_Channel_0



/*Set the LM35 Return Unit
 * choose between:
 * 1. LM35_TEMP_UNIT_CELSIUS				<--the most used
 * 2. LM35_TEMP_UNIT_FAHRENHEIT
 * 3. LM35_TEMP_UNIT_KELVIN
 */
#define LM35_TEMP_UNIT						LM35_TEMP_UNIT_CELSIUS



/*The ADC Voltage Reference set Automatically*/
#if   ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AREF

	/*Set the ADC Voltage Reference in AREF Pin*/
	#define LM35_VOLT_REF							//write the reference value here if necessary

#elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_2_56V

	/*the ADC Voltage Reference Set Automatically*/
	#define LM35_VOLT_REF			LM35_2_56V_REF

#elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AVCC

	/*the ADC Voltage Reference Set Automatically*/
	#define LM35_VOLT_REF			LM35_5V_REF

#endif


/* You must initialize ADC manually "ADC_Init()" before using this driver */
#ifndef ADC_IN_HAL
#define ADC_IN_HAL
	#warning "⚠️ Initialize ADC manually before using this driver."
#endif


/* Enable ADC overflow interrupt */
#if ADC_INT_STATUS != ADC_INT_DISABLE
	#warning "⚠️ Disable ADC interrupt."
#endif


#endif /* LM35_CONFIG_H_ */

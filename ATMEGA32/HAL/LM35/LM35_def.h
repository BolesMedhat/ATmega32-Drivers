/****************************************************************************
 * @file    LM35_def.h
 * @author  Boles Medhat
 * @brief   LM35 Temperature Sensor Definitions Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains macro definitions used by the LM35 temperature sensor driver,
 * including voltage reference options for ADC conversion and unit conversion modes
 * (Celsius, Fahrenheit, Kelvin).
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

#ifndef LM35_DEF_H_
#define LM35_DEF_H_


/*------------------------------------------   values    ----------------------------------------*/

/*ADC Voltage Reference Value*/
#define LM35_5V_REF							5		/*Use 5V as ADC reference voltage*/
#define LM35_2_56V_REF						2.56	/*Use 2.56V as ADC reference voltage*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*Set the LM35 Return Unit*/
#define LM35_TEMP_UNIT_CELSIUS				0		/*Return temperature in Celsius    (°C)*/
#define LM35_TEMP_UNIT_FAHRENHEIT			1		/*Return temperature in Fahrenheit (°F)*/
#define LM35_TEMP_UNIT_KELVIN				2		/*Return temperature in Kelvin      (K)*/
/*_______________________________________________________________________________________________*/


#endif /* LM35_DEF_H_ */

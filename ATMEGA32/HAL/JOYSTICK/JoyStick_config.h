/****************************************************************************
 * @file    JOYSTICK_config.h
 * @author  Boles Medhat
 * @brief   Joystick Configuration Header File
 * @version 1.0
 * @date    [2024-09-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This configuration file defines all necessary settings for the joystick driver,
 * including neutral positions, dead zones, maximum range limits, and hardware
 * connections (ADC channels and button pin configuration).
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
 ****************************************************************************/

#ifndef JOYSTICK_CONFIG_H_
#define JOYSTICK_CONFIG_H_

#include "JoyStick_def.h"
#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/DIO/DIO.h"


/*Set the Joystick X-axis Center Value, Indicating the Joystick's Neutral Position (midpoint of the 10-bit ADC range)*/
#define JOYSTICK_X_NEUTRAL					503


/*Set the Joystick Y-axis Center Value, Indicating the Joystick's Neutral Position (midpoint of the 10-bit ADC range)*/
#define JOYSTICK_Y_NEUTRAL					521



/*Set the Range of the Dead Zone around the Joystick's Center, where Movements Within this Range are Ignored*/
#define JOYSTICK_DEAD_ZONE					20



/*Set the Maximum the X-axis value in one Direction (for example, 100 means that the Full Range is -100 to 100)*/
#define JOYSTICK_X_ABS_MAX					100


/*Set the Maximum the Y-axis value in one Direction (for example, 100 means that the Full Range is -100 to 100)*/
#define JOYSTICK_Y_ABS_MAX					100



/*Set the Joystick X Axis Channel
 * choose between:
 * 1. ADC0
 * 2. ADC1
 * 3. ADC2
 * 4. ADC3
 * 5. ADC4
 * 6. ADC5
 * 7. ADC6
 * 8. ADC7
 */
#define JOYSTICK_X_AXIS_CHANNEL				ADC0


/*Set the Joystick Y Axis Channel
 * choose between:
 * 1. ADC0
 * 2. ADC1
 * 3. ADC2
 * 4. ADC3
 * 5. ADC4
 * 6. ADC5
 * 7. ADC6
 * 8. ADC7
 */
#define JOYSTICK_Y_AXIS_CHANNEL				ADC1



/*Set the DIO Port For the Joystick Button
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define JOYSTICK_BUTTON_PORT				DIO_PORTD



/*Set the DIO Pin For the Joystick Button
 * choose between:
 * 1. DIO_PIN0
 * 2. DIO_PIN1
 * 3. DIO_PIN2
 * 4. DIO_PIN3
 * 5. DIO_PIN4
 * 6. DIO_PIN5
 * 7. DIO_PIN6
 * 8. DIO_PIN7
 */
#define JOYSTICK_BUTTON_PIN					DIO_PIN0



/* You must initialize ADC manually "ADC_Init()" before using this driver */
#ifndef ADC_IN_HAL
#define ADC_IN_HAL
	#warning "⚠️ Initialize ADC manually before using this driver."
#endif


/* Enable ADC overflow interrupt */
#if ADC_INT_STATUS != ADC_INT_DISABLE
	#warning "⚠️ Disable ADC interrupt."
#endif


#endif /* JOYSTICK_CONFIG_H_ */

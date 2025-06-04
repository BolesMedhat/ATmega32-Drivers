/****************************************************************************
 * @file    EXTI_config.h
 * @author  Boles Medhat
 * @brief   External Interrupt (EXTI) Configuration Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for External Interrupt (INT0, INT1, INT2)
 * in ATmega32 microcontroller. It allows for setting up various parameters such as
 * enabling/disabling the interrupt, selecting the interrupt sense control,
 * and configuring the interrupt pin mode.
 *
 * @note
 * - All available choices (e.g., enabling/disabling the interrupt, interrupt sense control,
 *   interrupt pin mode) are defined in `EXTI_def.h` and explained with comments there.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

#include "EXTI_def.h"


/*-----------------------------------   External Interrupt 0   ----------------------------------*/
/*Set Interrupt Status
 * choose between:
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define EXTI_0_STATUS					EXTI_ENABLE


/*Set Interrupt Sense Control
 * choose between:
 * 1. EXTI_THE_LOW_LEVEL
 * 2. EXTI_ANY_LOGIC_CHANGE
 * 3. EXTI_THE_FALLING_EDGE
 * 4. EXTI_THE_RISING_EDGE
 */
#define EXTI_0_SENSE_CONTROL			EXTI_THE_FALLING_EDGE


/*Set the External Interrupt PIN Mode
 * choose between:
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define EXTI_0_PIN_MODE					EXTI_INPUT_PULLUP
/*_______________________________________________________________________________________________*/



/*-----------------------------------   External Interrupt 1   ----------------------------------*/
/*Set Interrupt Status
 * choose between:
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define EXTI_1_STATUS					EXTI_ENABLE


/*Set Interrupt Sense Control
 * choose between:
 * 1. EXTI_THE_LOW_LEVEL
 * 2. EXTI_ANY_LOGIC_CHANGE
 * 3. EXTI_THE_FALLING_EDGE
 * 4. EXTI_THE_RISING_EDGE
 */
#define EXTI_1_SENSE_CONTROL			EXTI_THE_FALLING_EDGE


/*Set the External Interrupt PIN Mode
 * choose between:
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define EXTI_1_PIN_MODE					EXTI_INPUT_PULLUP
/*_______________________________________________________________________________________________*/



/*-----------------------------------   External Interrupt 2   ----------------------------------*/
/*Set Interrupt Status
 * choose between:
 * 1. EXTI_DISABLE
 * 2. EXTI_ENABLE
 */
#define EXTI_2_STATUS					EXTI_ENABLE


/*Set Interrupt Sense Control
 * choose between:
 * 1. EXTI_THE_FALLING_EDGE
 * 2. EXTI_THE_RISING_EDGE
 */
#define EXTI_2_SENSE_CONTROL			EXTI_THE_FALLING_EDGE


/*Set the External Interrupt PIN Mode
 * choose between:
 * 1. EXTI_INPUT
 * 2. EXTI_INPUT_PULLUP
 */
#define EXTI_2_PIN_MODE					EXTI_INPUT_PULLUP
/*_______________________________________________________________________________________________*/


#endif /* EXTI_CONFIG_H_ */

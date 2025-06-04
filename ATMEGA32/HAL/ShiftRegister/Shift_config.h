/****************************************************************************
 * @file    Shift_config.h
 * @author  Boles Medhat
 * @brief   Shift Register Driver Configuration Header File
 * @version 1.0
 * @date    [2024-09-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file allows the user to configure port and pin settings for
 * shift-in (74HC165) and shift-out (74HC595) register communication,
 * along with the preferred shift bit order.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/
#ifndef SHIFT_CONFIG_H_
#define SHIFT_CONFIG_H_

#include "Shift_def.h"


/*Set the order of shifting data:
 * choose between:
 * 1. SHIFT_LSB_FIRST
 * 2. SHIFT_MSB_FIRST
*/

#define SHIFT_ORDER				SHIFT_MSB_FIRST



/*--------------------------   SHIFT OUT CONFIGURATION (74HC595)   --------------------------*/

/*Set the DIO Port for the Shift-Out register (74HC595):
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define SHIFT_OUT_PORT			DIO_PORTD


/*Set the DIO Pin for the Shift-Out register (74HC595):
 * - SHCP (pin 11) → SHIFT_OUT_CLOCK_PIN
 * - STCP (pin 12) → SHIFT_OUT_LOAD_PIN
 * - DS   (pin 14) → SHIFT_OUT_DATA_PIN
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
#define SHIFT_OUT_CLOCK_PIN		DIO_PIN0
#define SHIFT_OUT_LOAD_PIN		DIO_PIN1
#define SHIFT_OUT_DATA_PIN		DIO_PIN2

/*___________________________________________________________________________________________*/



/*--------------------------   SHIFT IN CONFIGURATION (74HC165)   --------------------------*/

/*Set the DIO Port for the Shift-In register (74HC165):
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define SHIFT_IN_PORT			DIO_PORTD


/*Set the DIO Pin for the Shift-In register (74HC165):
 * - /PL(SH/LD) (pin 1) → SHIFT_IN_LOAD_PIN
 * - CP(CLK)    (pin 2) → SHIFT_IN_CLOCK_PIN
 * - DS(SI)     (pin 9) → SHIFT_IN_DATA_PIN
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
#define SHIFT_IN_LOAD_PIN		DIO_PIN3
#define SHIFT_IN_CLOCK_PIN		DIO_PIN4
#define SHIFT_IN_DATA_PIN		DIO_PIN5
/*___________________________________________________________________________________________*/


#endif /* SHIFT_CONFIG_H_ */

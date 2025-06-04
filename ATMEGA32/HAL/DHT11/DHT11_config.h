/****************************************************************************
 * @file    DHT11_config.h
 * @author  Boles Medhat
 * @brief   DHT11 Driver Configuration Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This configuration file allows the user to define the port and pin
 * used for interfacing with the DHT11 temperature and humidity sensor.
 * It also sets the timeout threshold to handle communication failures.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef DHT11_CONFIG_H_
#define DHT11_CONFIG_H_

#include "DHT11_def.h"


/*Set the DIO Port For the DHT11 Pin
 * choose between:
 * 1. DIO_PORTA
 * 2. DIO_PORTB
 * 3. DIO_PORTC
 * 4. DIO_PORTD
 */
#define DHT11_PORT							DIO_PORTC


/*Set the DIO Pin For the LCD DHT11 Pin
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
#define DHT11_PIN							DIO_PIN0


/*Maximum number of iterations to wait before timeout*/
#define DHT11_COUNTOUT						10000


#endif /* DHT11_CONFIG_H_ */

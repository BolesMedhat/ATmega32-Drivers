/***********************************************************************************************
 * @file    DHT11_def.h
 * @author  Boles Medhat
 * @brief   DHT11 Driver Definitions Header File
 * @version 1.0
 * @date    [2025-04-26]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This header file contains the necessary type definitions and status macros used
 * for reading data from the DHT11 temperature and humidity sensor.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 ***********************************************************************************************/

#ifndef DHT11_DEF_H_
#define DHT11_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   types    -----------------------------------------*/

/*Structure to hold DHT11 information*/
typedef struct
{
    uint8 humidity;								/*Relative Humidity percentage*/
    uint8 temperature;							/*Temperature in Celsius*/
    uint8 status;								/*Reading result (success, timeout, checksum error)*/
} DHT11_Data;
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*DHT11 Status Codes*/
#define DHT11_SUCCESS							0
#define DHT11_CHECKSUM_ERROR					1
#define DHT11_TIMEOUT_ERROR						2
/*_______________________________________________________________________________________________*/


#endif /* DHT11_DEF_H_ */

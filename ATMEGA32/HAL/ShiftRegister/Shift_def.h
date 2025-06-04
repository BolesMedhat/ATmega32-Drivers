/****************************************************************************
 * @file    SHIFT_def.h
 * @author  Boles Medhat
 * @brief   Shift Register Driver Header File
 * @version 1.0
 * @date    [2024-09-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file defines configuration macros used for controlling the bit
 * shift order of serial data in shift registers (e.g., 74HC165/74HC595).
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef SHIFT_DEF_H_
#define SHIFT_DEF_H_

#include "../../MCAL/DIO/DIO.h"


/*------------------------------------------   modes    -----------------------------------------*/
#define SHIFT_LSB_FIRST							0	/*Shift least significant bit first (LSB → MSB)*/
#define SHIFT_MSB_FIRST							1	/*Shift most  significant bit first (MSB → LSB)*/
/*_______________________________________________________________________________________________*/


#endif /* SHIFT_DEF_H_ */

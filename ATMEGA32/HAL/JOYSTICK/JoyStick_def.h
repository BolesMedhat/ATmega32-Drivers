/****************************************************************************
 * @file    JOYSTICK_def.h
 * @author  Boles Medhat
 * @brief   Joystick Definitions Header File
 * @version 1.0
 * @date    [2024-09-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This header defines direction macros for interpreting joystick movement.
 * These values represent the logical output states when reading joystick input.
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

#ifndef JOYSTICK_DEF_H_
#define JOYSTICK_DEF_H_


/*------------------------------------------   values    ----------------------------------------*/

/*Joystick Directions*/
#define JOYSTICK_DIRECTION_CENTER				0	/*Joystick is in the center position*/
#define JOYSTICK_DIRECTION_UP					1	/*Joystick is pushed upwards*/
#define JOYSTICK_DIRECTION_DOWN					2	/*Joystick is pushed downwards*/
#define JOYSTICK_DIRECTION_LEFT					3	/*Joystick is pushed to the left*/
#define JOYSTICK_DIRECTION_RIGHT				4	/*Joystick is pushed to the right*/
/*_______________________________________________________________________________________________*/


#endif /* JOYSTICK_DEF_H_ */

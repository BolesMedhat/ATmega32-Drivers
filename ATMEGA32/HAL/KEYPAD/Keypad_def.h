/****************************************************************************
 * @file    KEYPAD_def.h
 * @author  Boles Medhat
 * @brief   Keypad Driver Definitions Header File
 * @version 2.0
 * @date    [2024-09-10]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains macro definitions used by the Keypad driver.
 * It allows the user to select whether the return value is a character
 * or a numeric index.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/

#ifndef KEYPAD_DEF_H_
#define KEYPAD_DEF_H_


/*------------------------------------------   modes    -----------------------------------------*/

/*Keypad Return Mode*/
#define KEYPAD_RETURN_CHAR						0	/*Return the character representing the button pressed    (For example: '1', '2', ..., '#')*/
#define KEYPAD_RETURN_INDEX						1	/*Return the button index representing the button pressed (For example: 0, 1, ..., 15)*/
/*_______________________________________________________________________________________________*/


#endif /* KEYPAD_DEF_H_ */

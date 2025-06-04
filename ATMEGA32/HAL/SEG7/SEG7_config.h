/****************************************************************************
 * @file    SEG7_config.h
 * @author  Boles Medhat
 * @brief   7-Segment Display Configuration Header File
 * @version 2.0
 * @date    [2024-09-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the 7-segment display driver.
 * It allows selection of the display type (common anode or common cathode),
 * as well as multiplex delay timing. Logic-level macros, display arrays,
 * and disable masks are automatically derived based on the selected display type.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SEG7_CONFIG_H_
#define SEG7_CONFIG_H_

#include "../SEG7/SEG7_def.h"


/*Set 7 Segment Type
 * choose between:
 * 1. SEG7_COMMON_ANODE
 * 2. SEG7_COMMON_CATHODE
 */
#define SEG7_TYPE							SEG7_COMMON_ANODE



/* Delay in milliseconds between multiplex cycles */
#define SEG7_MULTIPLEX_DELAY				5


/******* Automatically Set *******/
#if   SEG7_TYPE == SEG7_COMMON_ANODE


	/*7-Segment Digits array*/
	#define SEG7_ARRAY						SEG7_ANODE_ARRAY

	/*7-Segment Logic*/
	#define SEG7_PIN_ENABLE					SEG7_ANODE_PIN_ENABLE
	#define SEG7_PIN_DISABLE				SEG7_ANODE_PIN_DISABLE

	/*7-Segment Disable mask*/
	#define SEG7_DISABLE_msk				SEG7_ANODE_DISABLE_msk


#elif SEG7_TYPE == SEG7_COMMON_CATHODE


	/*7-Segment Digits array*/
	#define SEG7_ARRAY						SEG7_CATHODE_ARRAY

	/*7-Segment Logic*/
	#define SEG7_PIN_ENABLE					SEG7_CATHODE_PIN_ENABLE
	#define SEG7_PIN_DISABLE				SEG7_CATHODE_PIN_DISABLE

	/*7-Segment Disable mask*/
	#define SEG7_DISABLE_msk				SEG7_CATHODE_DISABLE_msk


#else
	/* Make an Error */
	#error "Wrong \"SEG7_TYPE\" configuration option"
#endif



#endif /* SEG7_CONFIG_H_ */

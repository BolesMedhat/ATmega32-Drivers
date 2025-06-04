/******************************************************************************
 * @file    WDT_def.h
 * @author  Boles Medhat
 * @brief   Watchdog Timer Driver Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * time-out settings, and masks for configuring and interacting with the
 * Watchdog Timer (WDT) module on the ATmega32 microcontroller.
 *
 * @note
 * - All values correspond to typical Vcc = 5.0V timing from the datasheet.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef WDT_DEF_H_
#define WDT_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*Watchdog Control Register*/
#define WDTCR								*((volatile uint8 *)0x41)	/*Watchdog Timer Control Register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*WDTCR Register*/
#define WDP0								0	/*Watchdog Timer Prescaler bit 0*/
#define WDP1								1	/*Watchdog Timer Prescaler bit 1*/
#define WDP2								2	/*Watchdog Timer Prescaler bit 2*/
#define WDE									3	/*Watchdog Enable*/
#define WDTOE								4	/*Watchdog Turn-off Enable*/

/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*WDT Time-out*/
#define WDT_TIME_OUT_16ms					0	/*WDT Typical Time-out at VCC before Reset = 5.0V = 16.3 ms*/
#define WDT_TIME_OUT_32ms					1	/*WDT Typical Time-out at VCC before Reset = 5.0V = 32.5 ms*/
#define WDT_TIME_OUT_65ms					2	/*WDT Typical Time-out at VCC before Reset = 5.0V = 65 	 ms*/
#define WDT_TIME_OUT_130ms					3	/*WDT Typical Time-out at VCC before Reset = 5.0V = 0.13  s*/
#define WDT_TIME_OUT_260ms					4	/*WDT Typical Time-out at VCC before Reset = 5.0V = 0.26  s*/
#define WDT_TIME_OUT_520ms					5	/*WDT Typical Time-out at VCC before Reset = 5.0V = 0.52  s*/
#define WDT_TIME_OUT_1000ms					6	/*WDT Typical Time-out at VCC before Reset = 5.0V = 1.0   s*/
#define WDT_TIME_OUT_2100ms					7	/*WDT Typical Time-out at VCC before Reset = 5.0V = 2.1   s*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define WDT_TIME_OUT_clr_msk				0xF8	/*WDT PRESCALER Clear mask*/
#define WDT_Disable_msk						0x18	/*WDT Disable bits mask*/
/*_______________________________________________________________________________________________*/


#endif /* WDT_DEF_H_ */

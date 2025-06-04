/******************************************************************************
 * @file    WDT.c
 * @author  Boles Medhat
 * @brief   Watchdog Timer Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides functions to manage the Watchdog Timer (WDT) in
 * ATmega32 microcontroller. It includes the ability to enable, disable,
 * and use the WDT to force a system reset.
 *
 * The WDT is a safety feature that resets the system if software fails to
 * operate correctly (e.g., stuck in an infinite loop).
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "WDT.h"





/*
 * @brief Enables the Watchdog Timer (WDT) with a specified timeout period.
 *
 * This function starts the Watchdog Timer countdown using the selected timeout.
 * If the timer is not reset before it expires, the microcontroller will perform a system reset.
 *
 * @param time_out: Timeout period for the Watchdog Timer. Must be one of the following predefined values:
 *                     - WDT_TIME_OUT_16ms
 *                     - WDT_TIME_OUT_32ms
 *                     - WDT_TIME_OUT_65ms
 *                     - WDT_TIME_OUT_130ms
 *                     - WDT_TIME_OUT_260ms
 *                     - WDT_TIME_OUT_520ms
 *                     - WDT_TIME_OUT_1000ms
 *                     - WDT_TIME_OUT_2100ms
 */
void WDT_Enable( uint8 time_out )
{

	/* Clear Prescaler (Time-out) bits */
	WDTCR &= WDT_TIME_OUT_clr_msk;

	/* Set Prescaler (Time-out) bits */
	WDTCR |= time_out;

	/* Enable the Watchdog Timer (Start count) */
	SET_BIT( WDTCR , WDE );
}





/*
 * @brief Disables the Watchdog Timer (WDT).
 *
 * This function stops the countdown of the Watchdog Timer, preventing a reset from occurring.
 */
void WDT_Disable()
{

	/* Write logical one to WDTOE and WDE */
	WDTCR = WDT_Disable_msk;

	/* Turn off WDT */
	WDTCR = 0;
}






/*
 * @brief Resets the microcontroller using the Watchdog Timer.
 *
 * This function forces a reset by configuring the Watchdog Timer with the shortest timeout (16ms)
 * and enabling it. The MCU will then enter an infinite loop, causing the WDT to reset the MCU.
 */
void WDT_RESET_MCU()
{

	/* Enable the Watchdog Timer (Start count) */
	SET_BIT( WDTCR , WDE );
	WDT_Enable( WDT_TIME_OUT_16ms );

	/* Infinity Loop (Wait until WDT Reset the MCU) */
	while(1);
}






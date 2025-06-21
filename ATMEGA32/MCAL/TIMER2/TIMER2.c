/******************************************************************************
 * @file    TIMER2.c
 * @author  Boles Medhat
 * @brief   TIMER2 Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER2 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, and time tracking.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER2_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "TIMER2.h"

/* Pointer to the callback function for the TIMER2 Overflow ISR */
void (*g_TIMER2_OVF_CallBack)(void) = NULL;

/* Pointer to the callback function for the TIMER2 Compare Match ISR */
void (*g_TIMER2_COMP_CallBack)(void) = NULL;

/* Global Counter Used for Time Tracking */
volatile uint16 g_TIMER2_Overflow = 0;





/*
 * @brief Initialize TIMER2 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC2),
 * preload values for TCNT2 and OCR2, interrupt enables, and the clock source.
 * It configures the TIMER2 registers according to the defined macros in `TIMER2_config.h`.
 *
 * @see `TIMER2_config.h` for configuration options.
 */
void TIMER2_Init( void )
{

	/* Check TIMER2 Waveform Generation Mode (Timer Mode) */
	#if	  TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE

		/* TIMER2 Normal Mode */
		CLR_BIT( TCCR2 , WGM21 ); CLR_BIT( TCCR2 , WGM20 );

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

		/* TIMER2 PWM (Phase Correct) Mode */
		CLR_BIT( TCCR2 , WGM21 ); SET_BIT( TCCR2 , WGM20 );

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE

		/* TIMER2 CTC Mode */
		SET_BIT( TCCR2 , WGM21 ); CLR_BIT( TCCR2 , WGM20 );

	#elif TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE

		/* TIMER2 CTC Mode */
		SET_BIT( TCCR2 , WGM21 ); SET_BIT( TCCR2 , WGM20 );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER2_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif


	/* Check Compare Output Mode (OC2 Pin Mode) */
	#if		TIMER2_OC2_MODE == TIMER2_COM_DISCONNECT_OC2

		/* Normal Port Operation, OC2 Disconnected */
		CLR_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

	#elif	TIMER2_OC2_MODE == TIMER2_COM_TOGGLE_OC2

		/* Toggle OC2 PIN on Compare Match */
		CLR_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

		/* Direction OC2 PIN as Output */
		SET_BIT( DDRD , OC2_PIN );

	#elif	TIMER2_OC2_MODE == TIMER2_COM_CLEAR_OC2	||	\
			TIMER2_OC2_MODE == TIMER2_COM_NON_INVERTING_OC2

		/* Clear OC2 PIN on Compare Match */
		SET_BIT( TCCR2 , COM21 ); CLR_BIT( TCCR2 , COM20 );

		/* Direction OC2 PIN as Output */
		SET_BIT( DDRD , OC2_PIN );

	#elif	TIMER2_OC2_MODE == TIMER2_COM_SET_OC2	||	\
			TIMER2_OC2_MODE == TIMER2_COM_INVERTING_OC2

		/* Set OC2 PIN on Compare Match */
		SET_BIT( TCCR2 , COM21 ); SET_BIT( TCCR2 , COM20 );

		/* Direction OC2 PIN as Output */
		SET_BIT( DDRD , OC2_PIN );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER2_OC2_MODE\" configuration option"
	#endif


	/* Set TCNT2 Preload Value from configuration file */
	TCNT2 = TIMER2_TCNT2_PRELOAD;

	/* Set OCR2 Preload Value from configuration file */
	OCR2 = TIMER2_OCR2_PRELOAD;


	#if		TIMER2_OVF_INT_STATUS == TIMER2_OVF_INT_ENABLE

		/* Clear the TIMER2 Overflow Interrupt Flag */
		SET_BIT( TIFR , TOV2 );

		/* Enable the TIMER2 Overflow Interrupt */
		SET_BIT( TIMSK , TOIE2 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#elif	TIMER2_OVF_INT_STATUS == TIMER2_OVF_INT_DISABLE

		/* Disable the TIMER2 Overflow Interrupt */
		CLR_BIT( TIMSK , TOIE2 );

	#else
			/* Make an Error */
			#error "Wrong \"TIMER2_OVF_INT_STATUS\" configuration option"
	#endif


	#if		TIMER2_COMP_INT_STATUS == TIMER2_COMP_INT_ENABLE

		/* Clear the Compare Match Interrupt Flag */
		SET_BIT( TIFR , OCF2 );

		/* Enable the Compare Match Interrupt */
		SET_BIT( TIMSK , OCIE2 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#elif	TIMER2_COMP_INT_STATUS == TIMER2_COMP_INT_DISABLE

		/* Disable the Compare Match Interrupt */
		CLR_BIT( TIMSK , OCIE2 );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER2_COMP_INT_STATUS\" configuration option"
	#endif


	/* Clear the Clock Source Select Bits */
	TCCR2 &= TIMER2_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR2 |= TIMER2_CLOCK_SOURCE_msk;

}





/*
 * @brief Disable (stop) TIMER2 by clearing the clock source bits.
 *
 * This function stops the TIMER2 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER2_Disable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR2 &= TIMER2_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR2 |= TIMER2_NO_CLOCK_SOURCE;
}





/*
 * @brief Enable (resume) TIMER2 by reapplying the configured clock source.
 *
 * This function re-enables TIMER2 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER2_Init`, so it may not be necessary to call.
 */
void TIMER2_Enable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR2 &= TIMER2_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR2 |= TIMER2_CLOCK_SOURCE_msk;
}





/*
 * @brief Set the Output Compare Register (OCR2) value.
 *
 * This function set OCR2 value that determines when a compare match interrupt
 * is triggered or when the OC2 output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR2.
 */
void TIMER2_SetCompareValue( uint8 CompareValue )
{
	OCR2 = CompareValue;
}





/*
 * @brief Get the OCR2 register value.
 *
 * This function get OCR2 value of TIMER2.
 *
 * @return (uint8) value of OCR2 register.
 */
uint8 TIMER2_GetCompareValue( void )
{
	return OCR2;
}





/*
 * @brief Set the Timer Counter Register (TCNT2) value.
 *
 * This function set TCNT2 value that determines the current count of TIMER2
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT2.
 */
void TIMER2_SetTimerValue( uint8 TimerValue )
{
	TCNT2 = TimerValue;
}





/*
 * @brief Get the current TIMER2 counter value.
 *
 * This function get TCNT2 value that determines the current count of TIMER2.
 *
 * @return (uint8) Current value of TCNT2 register.
 */
uint8 TIMER2_GetTimerValue( void )
{
	return TCNT2;
}





/*
 * @brief Disable a specific TIMER2 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable.
 *        Use `TIMER2_OVF_ID` or `TIMER2_COMP_ID`.
 */
void TIMER2_InterruptDisable( uint8 interrupt_id )
{

	if ( interrupt_id == TIMER2_OVF_ID )
	{
		/* Disable TIMER2 Overflow Interrupt */
		CLR_BIT( TIMSK , TOIE2 );
	}
	else if ( interrupt_id == TIMER2_COMP_ID )
	{
		/* Disable TIMER2 Compare Match Interrupt */
		CLR_BIT( TIMSK , OCIE2 );
	}


}





/*
 * @brief Enable a specific TIMER2 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable.
 *        Use `TIMER2_OVF_ID` or `TIMER2_COMP_ID`.
 */
void TIMER2_InterruptEnable( uint8 interrupt_id )
{

	if ( interrupt_id == TIMER2_OVF_ID )
	{
		/* Enable TIMER2 Overflow Interrupt */
		SET_BIT( TIMSK , TOIE2 );
	}
	else if ( interrupt_id == TIMER2_COMP_ID )
	{
		/* Enable TIMER2 Compare Match Interrupt */
		SET_BIT( TIMSK , OCIE2 );
	}
}





/*
 * @brief Get the total time elapsed since TIMER2 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT2 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return (uint64) Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT2 after initialization.
 * @warning TIMER2_COUNT_MODE and any TIMER2 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER2_GetTime_ms( void )
{

	/* Check the Timer2 Mode */
	#if		TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE ||	\
			TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT2 + ( (uint64)g_TIMER2_Overflow * 256 ) ) * ( TIMER2_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT2 + ( (uint64)g_TIMER2_Overflow * 512 ) ) * ( TIMER2_PRESCALER * 1000.0 / F_CPU );

	#else

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT2 + ( (uint64)g_TIMER2_Overflow * (OCR2 + 1) ) ) * ( TIMER2_PRESCALER * 1000.0 / F_CPU );

	#endif
}





/*
 * @brief Reset TIMER2 counter and overflow counter to zero.
 *
 * This function resets both TCNT2 and `g_TIMER2_Overflow` to start counting from the beginning.
 */
void TIMER2_RESET( void )
{
	TCNT2 = 0;
	g_TIMER2_Overflow = 0;
}





/*
 * @brief Calculate Timer2 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer2 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT2 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT2:      Pointer to store the starting TCNT2 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT2 with initialTCNT2
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER2_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows, uint8 * initialTCNT2 )
{

	/* Check the Timer2 Mode */
	#if		TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_NORMAL_MODE ||	\
			TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_FAST_PWM_MODE

		/* Calculate the total number of Timer2 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / TIMER2_FREQ_DIVIDER;

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT2 preload value to compensate for the fractional part of the overflow */
			*initialTCNT2 = (1 - (totalOverflows - (uint16)totalOverflows)) * 256;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT2 with 0 */
			*initialTCNT2 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_PWM_MODE

		/* Calculate the total number of Timer2 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER2_PRESCALER * 51200.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT2 preload value to compensate for the fractional part of the overflow */
			*initialTCNT2 = (1 - (totalOverflows - (uint16)totalOverflows)) * 512;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT2 with 0 */
			*initialTCNT2 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#else

		/* Calculate the total number of Timer2 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (OCR2 + 1) * TIMER2_PRESCALER * 1000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT2 preload value to compensate for the fractional part of the overflow */
			*initialTCNT2 = (1 - (totalOverflows - (uint16)totalOverflows)) * (OCR2 + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT2 with 0 */
			*initialTCNT2 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#endif
}





/*
 * @brief Sets a callback function for a specified Timer2 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer2 (OVF,or COMP) interrupt occurs.
 *
 * @example TIMER2_SetCallback( TIMER2_OVF_ID , TIMER2_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID (TIMER2_OVF_ID, TIMER2_COMP_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER2_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) )
{

	if ( interrupt_id == TIMER2_OVF_ID )
	{
		/* Copy the Function Pointer */
		g_TIMER2_OVF_CallBack = CopyFuncPtr;
	}
	else if ( interrupt_id == TIMER2_COMP_ID )
	{
		/* Copy the Function Pointer */
		g_TIMER2_COMP_CallBack = CopyFuncPtr;
	}
}





/*
 * @brief ISR for the Timer2 Compare Match (COMP) interrupt.
 *
 * This ISR is triggered when a Timer2 Compare Match (COMP) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER0_SetCallback function.
 *
 * @see TIMER0_SetCallback for setting the callback function.
 */
void __vector_4 (void)		__attribute__ ((signal)) ;
void __vector_4 (void)
{

	/* Check that the Pointer is Valid */
	if( g_TIMER2_COMP_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER2_COMP_CallBack();
	}

	#if	TIMER2_WAVEFORM_GENERATION_MODE == TIMER2_CTC_MODE		&&	\
		TIMER2_SW_TIME_TRACKING == TIMER2_TIME_TRACKING_ENABLE

		g_TIMER2_Overflow++;
	#endif
}




/*
 * @brief ISR for the Timer2 Overflow (OVF) interrupt.
 *
 * This ISR is triggered when a Timer2 Overflow (OVF) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER0_SetCallback function.
 *
 * @see TIMER0_SetCallback for setting the callback function.
 */
void __vector_5 (void)		__attribute__ ((signal)) ;
void __vector_5 (void)
{
	/* ISR for TIMER2 Overflow (OVF) Interrupt */

	/* Check that the Pointer is Valid */
	if( g_TIMER2_OVF_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER2_OVF_CallBack();
	}

	/* Check on Count mode (for TIMER2_GetTime_ms() function) */
	#if	TIMER2_WAVEFORM_GENERATION_MODE != TIMER2_CTC_MODE		&&	\
		TIMER2_SW_TIME_TRACKING == TIMER2_TIME_TRACKING_ENABLE

		g_TIMER2_Overflow++;
	#endif
}




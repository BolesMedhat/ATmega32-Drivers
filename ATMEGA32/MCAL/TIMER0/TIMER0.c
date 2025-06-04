/******************************************************************************
 * @file    TIMER0.c
 * @author  Boles Medhat
 * @brief   TIMER0 Driver Source File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-02]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER0 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, and time tracking.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER0_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "TIMER0.h"

/* Pointer to the callback function for the TIMER0 Overflow ISR */
void (*g_TIMER0_OVF_CallBack)(void) = NULL;

/* Pointer to the callback function for the TIMER0 Compare Match ISR */
void (*g_TIMER0_COMP_CallBack)(void) = NULL;

/* Global Counter Used for Time Tracking */
volatile uint16 g_TIMER0_Overflow = 0;





/*
 * @brief Initialize TIMER0 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC0),
 * preload values for TCNT0 and OCR0, interrupt enables, and the clock source.
 * It configures the TIMER0 registers according to the defined macros in `TIMER0_config.h`.
 *
 * @see `TIMER0_config.h` for configuration options.
 */
void TIMER0_Init( void )
{

	/* Check TIMER0 Waveform Generation Mode (Timer Mode) */
	#if	  TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE

		/* TIMER0 Normal Mode */
		CLR_BIT( TCCR0 , WGM01 ); CLR_BIT( TCCR0 , WGM00 );

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

		/* TIMER0 PWM (Phase Correct) Mode */
		CLR_BIT( TCCR0 , WGM01 ); SET_BIT( TCCR0 , WGM00 );

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE

		/* TIMER0 CTC Mode */
		SET_BIT( TCCR0 , WGM01 ); CLR_BIT( TCCR0 , WGM00 );

	#elif TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE

		/* TIMER0 CTC Mode */
		SET_BIT( TCCR0 , WGM01 ); SET_BIT( TCCR0 , WGM00 );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER0_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif


	/* Check Compare Output Mode (OC0 Pin Mode) */
	#if		TIMER0_OC0_MODE == TIMER0_COM_DISCONNECT_OC0

		/* Normal Port Operation, OC0 Disconnected */
		CLR_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

	#elif	TIMER0_OC0_MODE == TIMER0_COM_TOGGLE_OC0

		/* Toggle OC0 PIN on Compare Match */
		CLR_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

		/* Direction OC0 PIN as Output */
		SET_BIT( DDRB , OC0_PIN );

	#elif	TIMER0_OC0_MODE == TIMER0_COM_CLEAR_OC0	||	\
			TIMER0_OC0_MODE == TIMER0_COM_NON_INVERTING_OC0

		/* Clear OC0 PIN on Compare Match */
		SET_BIT( TCCR0 , COM01 ); CLR_BIT( TCCR0 , COM00 );

		/* Direction OC0 PIN as Output */
		SET_BIT( DDRB , OC0_PIN );

	#elif	TIMER0_OC0_MODE == TIMER0_COM_SET_OC0	||	\
			TIMER0_OC0_MODE == TIMER0_COM_INVERTING_OC0

		/* Set OC0 PIN on Compare Match */
		SET_BIT( TCCR0 , COM01 ); SET_BIT( TCCR0 , COM00 );

		/* Direction OC0 PIN as Output */
		SET_BIT( DDRB , OC0_PIN );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER0_OC0_MODE\" configuration option"
	#endif


	/* Set TCNT0 Preload Value from configuration file */
	TCNT0 = TIMER0_TCNT0_PRELOAD;

	/* Set OCR0 Preload Value from configuration file */
	OCR0 = TIMER0_OCR0_PRELOAD;


	#if		TIMER0_OVF_INT_STATUS == TIMER0_OVF_INT_ENABLE

		/* Clear the Timer0 Overflow Interrupt Flag */
		SET_BIT( TIFR , TOV0 );

		/* Enable the Timer0 Overflow Interrupt */
		SET_BIT( TIMSK , TOIE0 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#elif	TIMER0_OVF_INT_STATUS == TIMER0_OVF_INT_DISABLE

		/* Disable the Timer0 Overflow Interrupt */
		CLR_BIT( TIMSK , TOIE0 );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER0_OVF_INT_STATUS\" configuration option"
	#endif


	#if TIMER0_COMP_INT_STATUS == TIMER0_COMP_INT_ENABLE

		/* Clear the Compare Match Interrupt Flag */
		SET_BIT( TIFR , OCF0 );

		/* Enable the Compare Match Interrupt */
		SET_BIT( TIMSK , OCIE0 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#elif	TIMER0_COMP_INT_STATUS == TIMER0_COMP_INT_DISABLE

		/* Disable the Compare Match Interrupt */
		CLR_BIT( TIMSK , OCIE0 );

	#else
		/* Make an Error */
		#error "Wrong \"TIMER0_COMP_INT_STATUS\" configuration option"
	#endif


	/* Clear the Clock Source Select Bits */
	TCCR0 &= TIMER0_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR0 |= TIMER0_CLOCK_SOURCE_msk;

}





/*
 * @brief Disable (stop) TIMER0 by clearing the clock source bits.
 *
 * This function stops the TIMER0 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER0_Disable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR0 &= TIMER0_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR0 |= TIMER0_NO_CLOCK_SOURCE;
}





/*
 * @brief Enable (resume) TIMER0 by reapplying the configured clock source.
 *
 * This function re-enables TIMER0 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER0_Init`, so it may not be necessary to call.
 */
void TIMER0_Enable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR0 &= TIMER0_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR0 |= TIMER0_CLOCK_SOURCE_msk;
}





/*
 * @brief Set the Output Compare Register (OCR0) value.
 *
 * This function set OCR0 value that determines when a compare match interrupt
 * is triggered or when the OC0 output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR0.
 */
void TIMER0_SetCompareValue( uint8 CompareValue )
{
	OCR0 = CompareValue;
}





/*
 * @brief Get the OCR0 register value.
 *
 * This function get OCR0 value of TIMER0.
 *
 * @return (uint8) value of OCR0 register.
 */
uint8 TIMER0_GetCompareValue( void )
{
	return OCR0;
}





/*
 * @brief Set the Timer Counter Register (TCNT0) value.
 *
 * This function set TCNT0 value that determines the current count of TIMER0
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT0.
 */
void TIMER0_SetTimerValue( uint8 TimerValue )
{
	TCNT0 = TimerValue;
}





/*
 * @brief Get the current TIMER0 counter value.
 *
 * This function get TCNT0 value that determines the current count of TIMER0.
 *
 * @return (uint8) Current value of TCNT0 register.
 */
uint8 TIMER0_GetTimerValue( void )
{
	return TCNT0;
}





/*
 * @brief Disable a specific TIMER0 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable.
 *        Use `TIMER0_OVF_ID` or `TIMER0_COMP_ID`.
 */
void TIMER0_InterruptDisable( uint8 interrupt_id )
{

	if ( interrupt_id == TIMER0_OVF_ID )
	{
		/* Disable TIMER0 Overflow Interrupt */
		CLR_BIT( TIMSK , TOIE0 );
	}
	else if ( interrupt_id == TIMER0_COMP_ID )
	{
		/* Disable TIMER0 Compare Match Interrupt */
		CLR_BIT( TIMSK , OCIE0 );
	}
}





/*
 * @brief Enable a specific TIMER0 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable.
 *        Use `TIMER0_OVF_ID` or `TIMER0_COMP_ID`.
 */
void TIMER0_InterruptEnable( uint8 interrupt_id )
{

	if ( interrupt_id == TIMER0_OVF_ID )
	{
		/* Enable TIMER0 Overflow Interrupt */
		SET_BIT( TIMSK , TOIE0 );
	}
	else if ( interrupt_id == TIMER0_COMP_ID )
	{
		/* Enable TIMER0 Compare Match Interrupt */
		SET_BIT( TIMSK , OCIE0 );
	}
}





/*
 * @brief Get the total time elapsed since TIMER0 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT0 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return (uint64) Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT0 after initialization.
 * @warning TIMER0_COUNT_MODE and any TIMER0 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER0_GetTime_ms( void )
{

	/* Check the Timer0 Mode */
	#if		TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE ||	\
			TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT0 + ( (uint64)g_TIMER0_Overflow * 256 ) ) * ( TIMER0_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT0 + ( (uint64)g_TIMER0_Overflow * 512 ) ) * ( TIMER0_PRESCALER * 1000.0 / F_CPU );

	#else

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT0 + ( (uint64)g_TIMER0_Overflow * (OCR0 + 1) ) ) * ( TIMER0_PRESCALER * 1000.0 / F_CPU );

	#endif
}





/*
 * @brief Reset TIMER0 counter and overflow counter to zero.
 *
 * This function resets both TCNT0 and `g_TIMER0_Overflow` to start counting from the beginning.
 */
void TIMER0_RESET( void )
{
	TCNT0 = 0;
	g_TIMER0_Overflow = 0;
}





/*
 * @brief Calculate Timer0 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer0 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT0 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT0:      Pointer to store the starting TCNT0 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT0 with initialTCNT0
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER0_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows, uint8 * initialTCNT0 )
{

	/* Check the Timer0 Mode */
	#if		TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_NORMAL_MODE ||	\
			TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_FAST_PWM_MODE

		/* Calculate the total number of Timer0 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / TIMER0_FREQ_DIVIDER;

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT0 preload value to compensate for the fractional part of the overflow */
			*initialTCNT0 = (1 - (totalOverflows - (uint16)totalOverflows)) * 256;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT0 with 0 */
			*initialTCNT0 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_PWM_MODE

		/* Calculate the total number of Timer0 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER0_PRESCALER * 512000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT0 preload value to compensate for the fractional part of the overflow */
			*initialTCNT0 = (1 - (totalOverflows - (uint16)totalOverflows)) * 512;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT0 with 0 */
			*initialTCNT0 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#else

		/* Calculate the total number of Timer0 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (OCR0 + 1) * TIMER0_PRESCALER * 1000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT0 preload value to compensate for the fractional part of the overflow */
			*initialTCNT0 = (1 - (totalOverflows - (uint16)totalOverflows)) * (OCR0 + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT0 with 0 */
			*initialTCNT0 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#endif
}





/*
 * @brief Sets a callback function for a specified Timer0 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer0 (OVF,or COMP) interrupt occurs.
 *
 * @example TIMER0_SetCallback( TIMER0_OVF_ID , TIMER0_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID (TIMER0_OVF_ID, TIMER0_COMP_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER0_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) )
{

	if ( interrupt_id == TIMER0_OVF_ID )
	{
		/* Copy the Function Pointer */
		g_TIMER0_OVF_CallBack = CopyFuncPtr;
	}
	else if ( interrupt_id == TIMER0_COMP_ID )
	{
		/* Copy the Function Pointer */
		g_TIMER0_COMP_CallBack = CopyFuncPtr;
	}
}





/*
 * @brief ISR for the Timer0 Compare Match (COMP) interrupt.
 *
 * This ISR is triggered when a Timer0 Compare Match (COMP) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER0_SetCallback function.
 *
 * @see TIMER0_SetCallback for setting the callback function.
 */
void __vector_10 (void)		__attribute__ ((signal)) ;
void __vector_10 (void)
{

	/* Check that the Pointer is Valid */
	if( g_TIMER0_COMP_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER0_COMP_CallBack();
	}

	/* Check on Count Mode (Software mode for TIMER0_GetTime_ms() function) */
	#if	TIMER0_WAVEFORM_GENERATION_MODE == TIMER0_CTC_MODE		&&	\
		TIMER0_SW_TIME_TRACKING == TIMER0_TIME_TRACKING_ENABLE

		/* Count Up */
		g_TIMER0_Overflow++;
	#endif
}





/*
 * @brief ISR for the Timer0 Overflow (OVF) interrupt.
 *
 * This ISR is triggered when a Timer0 Overflow (OVF) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER0_SetCallback function.
 *
 * @see TIMER0_SetCallback for setting the callback function.
 */
void __vector_11 (void)		__attribute__ ((signal)) ;
void __vector_11 (void)
{

	/* Check that the Pointer is Valid */
	if( g_TIMER0_OVF_CallBack != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER0_OVF_CallBack();
	}

	/* Check on Count Mode (Software mode for TIMER0_GetTime_ms() function) */
	#if	TIMER0_WAVEFORM_GENERATION_MODE != TIMER0_CTC_MODE		&&	\
		TIMER0_SW_TIME_TRACKING == TIMER0_TIME_TRACKING_ENABLE

		/* Count Up */
		g_TIMER0_Overflow++;
	#endif
}






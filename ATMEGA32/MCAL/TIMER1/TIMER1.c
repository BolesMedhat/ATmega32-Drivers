/****************************************************************************
 * @file    TIMER1.c
 * @author  Boles Medhat
 * @brief   TIMER1 Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER0 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, input capture functionality,
 * and time tracking.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER1_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/



#include "TIMER1.h"

/* Array of pointer to the callback function for the TIMER1 interrupts ISR */
void (*g_TIMER1_CallBack[4])(void) = { NULL, NULL, NULL, NULL };

/* Global Counter Used for Time Tracking */
volatile uint16 g_TIMER1_Overflow = 0;





/*
 * @brief Initialize TIMER1 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC1A and OC1B),
 * preload values for TCNT1, OCR1A, and OCR1B, interrupt enables, and the clock source.
 * It configures the TIMER1 registers according to the defined macros in `TIMER1_config.h`.
 *
 * @see `TIMER1_config.h` for configuration options.
 */
void TIMER1_Init( void )
{

	/* Clear the Waveform Generation Mode Bits */
	TCCR1A &= TIMER1_WGM1_10_clr_msk;
	TCCR1B &= TIMER1_WGM1_32_clr_msk;

	/* Set the Waveform Generation Mode Bits */
	TCCR1A |= ( TIMER1_WAVEFORM_GENERATION_MODE & 0x03 );
	TCCR1B |= ( TIMER1_WAVEFORM_GENERATION_MODE & 0x0C ) << 1;

	// '\'  means that the macro will be completed on another line
	#if 	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE	 || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE


			/* Check Compare Output Mode (OC1A Pin Mode) */
			#if   TIMER1_OC1A_MODE == TIMER1_COM_DISCONNECT_OC1A

				/* Normal Port Operation, OC1A Disconnected */
				CLR_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

			#elif TIMER1_OC1A_MODE == TIMER1_COM_TOGGLE_OC1A

				/* Toggle OC1A PIN on Compare Match */
				CLR_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_OC1A_MODE == TIMER1_COM_CLEAR_OC1A

				/* Clear OC1A PIN on Compare Match */
				SET_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_OC1A_MODE == TIMER1_COM_SET0_OC1A

				/* Set OC1A PIN on Compare Match */
				SET_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_OC1A_MODE\" configuration option"
			#endif


			/* Check Compare Output Mode (OC1B Pin Mode) */
			#if   TIMER1_OC1B_MODE == TIMER1_COM_DISCONNECT_OC1B

				/* Normal Port Operation, OC1B Disconnected */
				CLR_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

			#elif TIMER1_OC1B_MODE == TIMER1_COM_TOGGLE_OC1B

				/* Toggle OC1B PIN on Compare Match */
				CLR_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_OC1B_MODE == TIMER1_COM_CLEAR_OC1B

				/* Clear OC1B PIN on Compare Match */
				SET_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_OC1B_MODE == TIMER1_COM_SET0_OC1B

				/* Set OC1B PIN on Compare Match */
				SET_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_OC1B_MODE\" configuration option"
			#endif


	#elif	TIMER1_WAVEFORM_GENERATION_MODE != 13 && TIMER1_WAVEFORM_GENERATION_MODE <16


			/* Check Compare Output Mode (OC1A Pin Mode) */
			#if   TIMER1_OC1A_MODE == TIMER1_COM_DISCONNECT_OC1A

				/* Normal Port Operation, OC1A Disconnected */
				CLR_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

			#elif TIMER1_OC1A_MODE == TIMER1_COM_NON_INVERTING_OC1A

				/* OC1A in Non Inverting Mode */
				SET_BIT( TCCR1A , COM1A1 ); CLR_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#elif TIMER1_OC1A_MODE == TIMER1_COM_INVERTING_OC1A

				/* OC1A in Inverting Mode */
				SET_BIT( TCCR1A , COM1A1 ); SET_BIT( TCCR1A , COM1A0 );

				/* Direction OC1A PIN as Output */
				SET_BIT( DDRD , OC1A_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_OC1A_MODE\" configuration option"
			#endif

			/* Check Compare Output Mode (OC1B Pin Mode) */
			#if   TIMER1_OC1B_MODE == TIMER1_COM_DISCONNECT_OC1B

				/* Normal Port Operation, OC1B Disconnected */
				CLR_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

			#elif TIMER1_OC1B_MODE == TIMER1_COM_NON_INVERTING_OC1B

				/* OC1B in Non Inverting Mode */
				SET_BIT( TCCR1A , COM1B1 ); CLR_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#elif TIMER1_OC1B_MODE == TIMER1_COM_INVERTING_OC1B

				/* OC1B in Inverting Mode */
				SET_BIT( TCCR1A , COM1B1 ); SET_BIT( TCCR1A , COM1B0 );

				/* Direction OC1B PIN as Output */
				SET_BIT( DDRD , OC1B_PIN );

			#else
				/* Make an Error */
				#error "Wrong \"TIMER1_OC1B_MODE\" configuration option"
			#endif


	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_WAVEFORM_GENERATION_MODE\" configuration option"
	#endif


	/* Set TCNT1 PREload Value From Configuration File */
	TCNT1 = TIMER1_TCNT1_PRELOAD;

	/* Set OCR1A PREload Value From Configuration File */
	OCR1A = TIMER1_OCR1A_PRELOAD;

	/* Set OCR1B PREload Value From Configuration File */
	OCR1B = TIMER1_OCR1B_PRELOAD;

	// '\'  means that the macro will be completed on another line
	#if TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE ||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE		||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE		||	\
		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		/* Set ICR1 PREload Value From Configuration File */
		ICR1 = TIMER1_ICR1_PRELOAD;

	#endif


	#if   TIMER1_OVF_INT_STATUS == TIMER1_OVF_INT_ENABLE

			/* Clear the Overflow Interrupt Flag */
			SET_BIT( TIFR , TOV1 );

			/* Enable the Overflow Interrupt */
			SET_BIT( TIMSK , TOIE1 );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_OVF_INT_STATUS == TIMER1_OVF_INT_DISABLE

			/* Disable the Overflow Interrupt */
			CLR_BIT( TIMSK , TOIE1 );

	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_OVF_INT_STATUS\" configuration option"
	#endif


	#if TIMER1_COMPA_INT_STATUS == TIMER1_COMPA_INT_ENABLE

			/* Clear the Compare Match A Interrupt Flag */
			SET_BIT( TIFR , OCF1A );

			/* Enable the Compare Match A Interrupt */
			SET_BIT( TIMSK , OCIE1A );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_COMPA_INT_STATUS == TIMER1_COMPA_INT_DISABLE

			/* Disable the Compare Match A Interrupt */
			CLR_BIT( TIMSK , OCIE1A );

	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_COMPA_INT_STATUS\" configuration option"
	#endif


	#if TIMER1_COMPB_INT_STATUS == TIMER1_COMPB_INT_ENABLE

			/* Clear the Compare Match B Interrupt Flag */
			SET_BIT( TIFR , OCF1B );

			/* Enable the Compare Match B Interrupt */
			SET_BIT( TIMSK , OCIE1B );

			/* Enable Global Interrupt */
			SET_BIT( SREG , I );

	#elif TIMER1_COMPB_INT_STATUS == TIMER1_COMPB_INT_DISABLE

			/* Disable the Compare Match B Interrupt */
			CLR_BIT( TIMSK , OCIE1B );
	#else
			/* Make an Error */
			#error "Wrong \"TIMER1_COMPB_INT_STATUS\" configuration option"
	#endif


	/* Clear the Clock Source Select Bits */
	TCCR1B &= TIMER1_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR1B |= TIMER1_CLOCK_SOURCE_msk;

}





/*
 * @brief Disable (stop) TIMER1 by clearing the clock source bits.
 *
 * This function stops the TIMER1 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER1_Disable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR1B &= TIMER1_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR1B |= TIMER1_NO_CLOCK_SOURCE;
}





/*
 * @brief Enable (resume) TIMER1 by reapplying the configured clock source.
 *
 * This function re-enables TIMER1 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER1_Init`, so it may not be necessary to call.
 */
void TIMER1_Enable( void )
{

	/* Clear the Clock Source Select Bits */
	TCCR1B &= TIMER1_PRESCALER_clr_msk;

	/* Set the Clock Source Select Bits */
	TCCR1B |= TIMER1_CLOCK_SOURCE_msk;
}





/*
 * @brief Set the Output Compare Register (OCR1A) value.
 *
 * This function set OCR1A value that determines when a compare match interrupt
 * is triggered or when the OC1A output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR1A.
 */
void TIMER1_SetCompare_A_Value( uint16 CompareAValue )
{
	OCR1A = CompareAValue;
}





/*
 * @brief Get the OCR1A register value.
 *
 * This function get OCR1A value of TIMER1.
 *
 * @return (uint16) value of OCR1A register.
 */
uint16 TIMER1_GetCompare_A_Value( void )
{
	return OCR1A;
}





/*
 * @brief Set the Output Compare Register (OCR1B) value.
 *
 * This function set OCR1B value that determines when a compare match interrupt
 * is triggered or when the OC1B output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR1B.
 */
void TIMER1_SetCompare_B_Value( uint16 CompareBValue )
{
	OCR1B = CompareBValue;
}





/*
 * @brief Get the OCR1B register value.
 *
 * This function get OCR1B value of TIMER1.
 *
 * @return (uint16) value of OCR1B register.
 */
uint16 TIMER1_GetCompare_B_Value( void )
{
	return OCR1B;
}





/*
 * @brief Set the Timer Counter Register (TCNT1) value.
 *
 * This function set TCNT1 value that determines the current count of TIMER1
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT1.
 */
void TIMER1_SetTimerValue( uint16 TimerValue )
{
	TCNT1 = TimerValue;
}





/*
 * @brief Get the current TIMER0 counter value.
 *
 * This function get TCNT0 value that determines the current count of TIMER0.
 *
 * @return (uint16) Current value of TCNT0 register.
 */
uint16 TIMER1_GetTimerValue( void )
{
	return TCNT1;
}





/*
 * @brief Disable a specific TIMER1 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable. This can be one of the following:
 *                     - TIMER1_OVF_ID   : Overflow Interrupt
 *                     - TIMER1_COMPA_ID : Compare Match A Interrupt
 *                     - TIMER1_COMPB_ID : Compare Match B Interrupt
 *                     - TIMER1_CAPT_ID  : Input Capture Event Interrupt
 */
void TIMER1_InterruptDisable( uint8 interrupt_id )
{

	switch (interrupt_id)
	{
		/* Disable Overflow Interrupt */
		case TIMER1_OVF_ID:   CLR_BIT( TIMSK , TOIE1 );  break;

		/* Disable Compare Match A Interrupt */
		case TIMER1_COMPA_ID: CLR_BIT( TIMSK , OCIE1A ); break;

		/* Disable Compare Match B Interrupt */
		case TIMER1_COMPB_ID: CLR_BIT( TIMSK , OCIE1B ); break;

		/* Disable Capture Event Interrupt */
		case TIMER1_CAPT_ID:  CLR_BIT( TIMSK , TICIE1 ); break;
	}
}





/*
 * @brief Enable a specific TIMER1 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable. This can be one of the following:
 *                     - TIMER1_OVF_ID   : Overflow Interrupt
 *                     - TIMER1_COMPA_ID : Compare Match A Interrupt
 *                     - TIMER1_COMPB_ID : Compare Match B Interrupt
 *                     - TIMER1_CAPT_ID  : Input Capture Event Interrupt
 */
void TIMER1_InterruptEnable( uint8 interrupt_id )
{

	switch (interrupt_id)
	{
		/* Enable Overflow Interrupt */
		case TIMER1_OVF_ID:   SET_BIT( TIMSK , TOIE1 );  break;

		/* Enable Compare Match A Interrupt */
		case TIMER1_COMPA_ID: SET_BIT( TIMSK , OCIE1A ); break;

		/* Enable Compare Match B Interrupt */
		case TIMER1_COMPB_ID: SET_BIT( TIMSK , OCIE1B ); break;

		/* Enable Capture Event Interrupt */
		case TIMER1_CAPT_ID:  SET_BIT( TIMSK , TICIE1 ); break;
	}
}





/*
 * @brief Get the total time elapsed since TIMER1 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT1 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return (uint64) Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT1 after initialization.
 * @warning TIMER1_COUNT_MODE and any TIMER1 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER1_GetTime_ms( void )
{

	/* Check the Timer1 Mode */
	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 65536 ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8BIT_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9BIT_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 512 ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9BIT_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10BIT_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 1024 ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10BIT_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 2048 ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_OCR1A_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 2 * (OCR1A + 1) ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * (OCR1A + 1) ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8BIT_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 256 ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * 2 * (ICR1 + 1) ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		/* Calculate Time (Total Ticks)*(Time per Tick in ms) */
		return ( TCNT1 + ( (uint64)g_TIMER1_Overflow * (ICR1 + 1) ) ) * ( TIMER1_PRESCALER * 1000.0 / F_CPU );

	#endif

}





/*
 * @brief Reset TIMER0 counter and overflow counter to zero.
 *
 * This function resets both TCNT0 and `TIMER0_Overflow` to start counting from the beginning.
 */
void TIMER1_RESET( void )
{
	TCNT1 = 0;
	g_TIMER1_Overflow = 0;
}





/*
 * @brief Calculate Timer1 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer1 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT1 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT1:      Pointer to store the starting TCNT1 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT1 with initialTCNT1
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER1_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows, uint16 * initialTCNT1 )
{

	/* Check the Timer1 Mode */
	#if   TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / TIMER1_FREQ_DIVIDER;

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 65536;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_8BIT_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_9BIT_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER1_PRESCALER * 512000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 512;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_9BIT_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_10BIT_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER1_PRESCALER * 1024000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 1024;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_10BIT_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER1_PRESCALER * 2048000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 2048;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_OCR1A_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (OCR1A + 1) * TIMER1_PRESCALER * 2000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 2 * (OCR1A + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_OCR1A_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (OCR1A + 1) * TIMER1_PRESCALER * 1000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * (OCR1A + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_8BIT_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( TIMER1_PRESCALER * 256000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 256;

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PFC_PWM_ICR1_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_PWM_ICR1_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (ICR1 + 1) * TIMER1_PRESCALER * 2000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * 2 * (ICR1 + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#elif	TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE || \
			TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_FAST_PWM_ICR1_MODE

		/* Calculate the total number of Timer1 overflows needed for the desired time (can be fractional) */
		float32 totalOverflows = ( (float32)milliseconds * F_CPU ) / ( (ICR1 + 1) * TIMER1_PRESCALER * 1000.0 );

		/* Check if the total overflow count has a fractional part */
		if (totalOverflows > (uint16)totalOverflows)
		{
			/* Compute TCNT1 preload value to compensate for the fractional part of the overflow */
			*initialTCNT1 = (1 - (totalOverflows - (uint16)totalOverflows)) * (ICR1 + 1);

			/* Round up the total overflows to ensure complete time coverage */
			*requiredOverflows = (uint16)totalOverflows + 1;
		}
		else
		{
			/* No fractional part, preload TCNT1 with 0 */
			*initialTCNT1 = 0;

			/* Use the exact number of overflows */
			*requiredOverflows = totalOverflows;
		}

	#endif

}





/*
 * @brief Sets a callback function for a specified Timer1 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer1 (OVF, COMPA, COMPB, or CAPT) interrupt occurs.
 *
 * @example TIMER1_SetCallback( TIMER1_OVF_ID , TIMER1_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID can be one of the following:
 *                     - TIMER1_OVF_ID   : Overflow Interrupt
 *                     - TIMER1_COMPA_ID : Compare Match A Interrupt
 *                     - TIMER1_COMPB_ID : Compare Match B Interrupt
 *                     - TIMER1_CAPT_ID  : Input Capture Event Interrupt
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER1_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) )
{

	/* Check that the Pointer is Valid */
	if( interrupt_id < 4 )
	{
		/* Copy the Function Pointer */
		g_TIMER1_CallBack[ interrupt_id ] = CopyFuncPtr;
	}

}





/*
 * @brief Initializes the Input Capture Unit (ICU).
 *
 * This function configures the Input Capture Unit.
 * It sets up the noise canceler, the signal edge detection (rising or falling),
 * and enables the ICU interrupt if configured.
 * It configures the ICU registers according to the defined macros in TIMER1_config.h.
 *
 * @see TIMER1_config.h for configuration options.
 * @warning TIMER1 must be initialized before calling this function.
 */
void ICU_Init( void )
{

	/* Check on Input Capture Noise Canceler Status */
	#if   ICU_NOISE_CANCELER_STATUS == ICU_NOISE_CANCELER_DISABLE

		/* Disable Input Capture Noise Canceler */
		CLR_BIT( TCCR1B , ICNC1 );

	#elif ICU_NOISE_CANCELER_STATUS == ICU_NOISE_CANCELER_ENABLE

		/* Enable Input Capture Noise Canceler */
		SET_BIT( TCCR1B , ICNC1 );

	#else
		/* Make an Error */
		#error "Wrong \"ICU_NOISE_CANCELER_STATUS\" configuration option"
	#endif


	/* Check on Input Capture Signal Start Edge Status */
	#if   ICU_START_EDGE_STATUS == ICU_FALLING_EDGE

		/* the Input Capture Signal Start Edge is Falling Edge */
		CLR_BIT( TCCR1B , ICES1 );

	#elif ICU_START_EDGE_STATUS == ICU_RISING_EDGE

		/* the Input Capture Signal Start Edge is Rising Edge */
		SET_BIT( TCCR1B , ICES1 );

	#else
		/* Make an Error */
		#error "Wrong \"ICU_START_EDGE_STATUS\" configuration option"
	#endif

	/* Direction ICP1 PIN as Input */
	CLR_BIT( DDRD  , ICP1_PIN );

	#if   TIMER1_CAPT_INT_STATUS == TIMER1_CAPT_INT_ENABLE

		/* Clear Input Capture Unit Interrupt Flag */
		SET_BIT( TIFR , ICF1 );

		/* Enable Input Capture Unit Interrupt */
		SET_BIT( TIMSK , TICIE1 );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#endif
}





/*
 * @brief Sets the ICU to trigger on a falling edge.
 *
 * This function configures the Input Capture Unit to detect a falling edge as the trigger
 * for capturing the timer value.
 */
void ICU_FallingTriggerEdge( void )
{
	CLR_BIT( TCCR1B , ICES1 );
}





/*
 * @brief Sets the ICU to trigger on a rising edge.
 *
 * This function configures the Input Capture Unit to detect a rising edge as the trigger
 * for capturing the timer value.
 */
void ICU_RisingTriggerEdge( void )
{
	SET_BIT( TCCR1B , ICES1 );
}





/*
 * @brief Clears the Input Capture Flag.
 *
 * This function clears the ICF1 flag in the TIFR register, which indicates that an
 * input capture event has occurred.
 */
void ICU_ClearFlag( void )
{
	SET_BIT( TIFR , ICF1 );
}





/*
 * @brief Reads the Input Capture Flag.
 *
 * This function checks whether the Input Capture Flag (ICF1) is set, indicating that
 * a capture event has occurred.
 *
 * @return 1 if the flag is set, 0 otherwise.
 */
uint8 ICU_GetFlag( void )
{
	return GET_BIT( TIFR , ICF1 );
}





/*
 * @brief Retrieves the captured timer value.
 *
 * This function returns the current value stored in the ICR1 register, which holds the
 * timer value at the time of the input capture event.
 *
 * @return (uint16) Captured value from the ICR1 register.
 */
uint16 ICU_GetICUvalue( void )
{
	return ICR1;
}





/*
 * @brief ISR for the Timer1 Compare Match A (COMPA) interrupt.
 *
 * This ISR is triggered when a Timer1 Compare Match A (COMPA) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER1_SetCallback function.
 *
 * @see TIMER01SetCallback for setting the callback function.
 */
void __vector_7 (void)		__attribute__((signal)) ;
void __vector_7 (void)
{

	/* Check that the Pointer is Valid */
	if(g_TIMER1_CallBack[ TIMER1_COMPA_ID ] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER1_CallBack[ TIMER1_COMPA_ID ]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_OCR1A_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		g_TIMER1_Overflow++;
	#endif
}





/*
 * @brief ISR for the Timer1 Compare Match B (COMPB) interrupt.
 *
 * This ISR is triggered when a Timer1 Compare Match B (COMPB) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER1_SetCallback function.
 *
 * @see TIMER01SetCallback for setting the callback function.
 */
void __vector_8 (void)		__attribute__((signal)) ;
void __vector_8 (void)
{
	/* ISR for Timer1 Compare Match B (COMPB) Interrupt */

	/* Check that the Pointer is Valid */
	if(g_TIMER1_CallBack[ TIMER1_COMPB_ID ] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER1_CallBack[ TIMER1_COMPB_ID ]();
	}
}





/*
 * @brief ISR for the Timer1 Overflow (OVF) interrupt.
 *
 * This ISR is triggered when a Timer1 Overflow (OVF) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER0_SetCallback function.
 *
 * @see TIMER0_SetCallback for setting the callback function.
 */
void __vector_9 (void)		__attribute__((signal)) ;
void __vector_9 (void)
{

	/* Check that the Pointer is Valid */
	if(g_TIMER1_CallBack[ TIMER1_OVF_ID ] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER1_CallBack[ TIMER1_OVF_ID ]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_NORMAL_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		g_TIMER1_Overflow++;
	#endif
}





/*
 * @brief ISR for the Timer1 Capture Event (CAPT) interrupt.
 *
 * This ISR is triggered when a Timer0 Capture Event (CAPT) interrupt occurs.
 * It calls the user-defined callback function set by the TIMER1_SetCallback function.
 *
 * @see TIMER1_SetCallback for setting the callback function.
 */
void __vector_6 (void)		__attribute__ ((signal)) ;
void __vector_6 (void)
{

	/* ISR for Timer1 Capture Event (CAPT) Interrupt */

	/* Check that the Pointer is Valid */
	if(g_TIMER1_CallBack[ TIMER1_CAPT_ID ] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_TIMER1_CallBack[ TIMER1_CAPT_ID ]();
	}

	#if		TIMER1_WAVEFORM_GENERATION_MODE == TIMER1_CTC_ICR1_MODE	&&	\
			TIMER1_COUNT_MODE == TIMER1_COUNT_ENABLE

		g_TIMER1_Overflow++;
	#endif
}





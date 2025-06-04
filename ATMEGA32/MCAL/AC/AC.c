/****************************************************************************
 * @file    AC.c
 * @author  Boles Medhat
 * @brief   Analog Comparator (AC) Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-09-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file implements the functions for controlling the Analog Comparator
 * (AC) module in the ATmega32 microcontroller. It provides functions for
 * initialization, input source selection, interrupt control, and setting
 * callback functions for interrupt handling.
 *
 * @note
 * - Requires `AC_config.h` for macro-based configuration.
 * - Disabling the ADC module is required when using ADCx inputs as negative input.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "AC.h"

/* Pointer to the callback function for the Analog Comparator ISR */
void (*g_AC_CallBack)(void) = NULL;





/*
 * @brief Initialize the Analog Comparator based on configuration options.
 *
 * This function configures the interrupt mode, trigger source for ICU, input source, and enables
 * the Analog Comparator.
 * It configures the Analog Comparator registers according to the defined macros in `AC_config.h`.
 *
 * @see `AC_config.h` for configuration options.
 */
void AC_Init(void)
{

	/* Disable the Analog Comparator interrupt */
	CLR_BIT(ACSR, ACIE);

	/* Configure the Analog Comparator interrupt trigger event */
	#if   AC_INT_MODE == AC_INT_ON_TOGGLE

		/* Interrupt on output toggle */
		CLR_BIT(ACSR, ACIS1); CLR_BIT(ACSR, ACIS0);

	#elif AC_INT_MODE == AC_INT_ON_FALLING

		/* Interrupt on falling output edge */
		SET_BIT(ACSR, ACIS1); CLR_BIT(ACSR, ACIS0);

	#elif AC_INT_MODE == AC_INT_ON_RISING

		/* Interrupt on rising output edge */
		SET_BIT(ACSR, ACIS1); SET_BIT(ACSR, ACIS0);

	#else
		/* Invalid configuration option */
		#error "Wrong \"AC_INT_MODE\" configuration option"
	#endif

	/* Configure the Input Capture trigger from the Analog Comparator */
	#if   AC_TRIGGER_ICU_STATUS == AC_TRIGGER_ICU_DISABLE

		/* Disable input capture triggering by the Analog Comparator */
		CLR_BIT(ACSR, ACIC);

	#elif AC_TRIGGER_ICU_STATUS == AC_TRIGGER_ICU_ENABLE

		/* Enable input capture triggering by the Analog Comparator */
		SET_BIT(ACSR, ACIC);

	#else
		/* Invalid configuration option */
		#error "Wrong \"AC_TRIGGER_ICU_STATUS\" configuration option"
	#endif

	/* Configure the Analog Comparator interrupt status */
	#if   AC_INT_STATUS == AC_INT_ENABLE

		/* Clear the interrupt flag */
		SET_BIT(ACSR, ACI);

		/* Enable the Analog Comparator interrupt */
		SET_BIT(ACSR, ACIE);

		/* Enable global interrupts */
		SET_BIT(SREG, I);

	#elif AC_INT_STATUS != AC_INT_DISABLE
		/* Invalid configuration option */
		#error "Wrong \"AC_INT_STATUS\" configuration option"
	#endif

	/* Enable the Analog Comparator by clearing the disable bit */
	CLR_BIT(ACSR, ACD);
}






/*
 * @brief Get the output state of the Analog Comparator.
 *
 * This function checks the output of the Analog Comparator (ACO flag), which indicates whether
 * the positive input is greater than the negative input.
 *
 * @return (uint8) The output of the Analog Comparator.
 *               - Returns 1 if positive input > negative input.
 *               - Returns 0 if negative input >= positive input.
 */
uint8 AC_GetOutput( void )
{
	/* Return the output of the Analog Comparator */
	return GET_BIT( ACSR , ACO );
}





/*
 * @brief Change the negative input source of the Analog Comparator.
 *
 * This function select the negative input from various sources, including AIN1 or any of the ADC channels.
 *
 * @param Negative_Input: One of [AC_AIN1, AC_ADC0 ... AC_ADC7].
 *
 * @warning Choosing any ADC channel (AC_ADC0 ... AC_ADC7) will disable the ADC module.
 * @note If AC_AIN1 is selected, the ADC module will not be disabled.
 */
void AC_ChangeNegativeInput(uint8 Negative_Input)
{

	/* Check the Analog Comparator negative input source */
	if (Negative_Input == AC_AIN1)
	{
		/* AIN1 is applied to the negative input of the Analog Comparator */

		/* Disable Analog Comparator multiplexer */
		CLR_BIT(ACSR, ACME);
	}
	else if (Negative_Input >= AC_ADC0 && Negative_Input <= AC_ADC7)
	{
		/* ADC channel is applied to the negative input of the Analog Comparator */

		/* Enable Analog Comparator multiplexer */
		SET_BIT(ACSR, ACME);

		/* Disable ADC */
		CLR_BIT(ADCSRA, ADEN);

		/* Clear the channel bits */
		ADMUX &= ADC_CHANNEL_clr_msk;

		/* Set the selected channel bits */
		ADMUX |= Negative_Input;
	}
}




/*
 * @brief Change the positive input source of the Analog Comparator.
 *
 * This function select the positive input for the Analog Comparator from
 * AIN0 or the internal bandgap voltage (AC_BG).
 *
 * @param Positive_Input: One of [AC_AIN0, AC_BG].
 */
void AC_ChangePositiveInput( uint8 Positive_Input )
{

	/* Check the Analog Comparator positive input source */
	switch (Positive_Input)
	{
		/* The fixed bandgap reference voltage replaces the positive input */
		case AC_BG:		SET_BIT( ACSR , ACBG );	break;

		/* The AIN0 is applied to the positive input */
		case AC_AIN0:	CLR_BIT( ACSR , ACBG );	break;
	}
}





/*
 * @brief Change the interrupt trigger condition for the Analog Comparator.
 *
 * This function configures the event that triggers the Analog Comparator interrupt. The interrupt can
 * be triggered by a toggle of the output, a rising edge, or a falling edge.
 *
 * @param mode The desired trigger mode. It can be one of the following:
 *        - AC_INT_ON_TOGGLE: Trigger interrupt on output toggle.
 *        - AC_INT_ON_FALLING: Trigger interrupt on falling output edge.
 *        - AC_INT_ON_RISING: Trigger interrupt on rising output edge.
 */
void AC_ChangeTriggerEvent(uint8 mode)
{

	/* Disable the Analog Comparator interrupt */
	CLR_BIT(ACSR, ACIE);

	/* Set the Analog Comparator interrupt trigger event */
	switch (mode)
	{
		/* Interrupt on output toggle */
		case AC_INT_ON_TOGGLE:  CLR_BIT(ACSR, ACIS1); CLR_BIT(ACSR, ACIS0); break;

		/* Interrupt on falling output edge */
		case AC_INT_ON_FALLING: SET_BIT(ACSR, ACIS1); CLR_BIT(ACSR, ACIS0); break;

		/* Interrupt on rising output edge */
		case AC_INT_ON_RISING:  SET_BIT(ACSR, ACIS1); SET_BIT(ACSR, ACIS0); break;
	}

	/* Enable the Analog Comparator interrupt */
	SET_BIT(ACSR, ACIE);
}






/*
 * @brief Enable Analog Comparator interrupt.
 *
 * This function enables the interrupt for the Analog Comparator. The interrupt will be triggered based
 * on the configured trigger mode (toggle, rising, or falling edge).
 */
void AC_InterruptEnable( void )
{
	/* Enable the Analog Comparator interrupt */
	SET_BIT( ACSR , ACIE );
}





/*
 * @brief Disable Analog Comparator interrupt.
 *
 * This function disables the interrupt for the Analog Comparator.
 */
void AC_InterruptDisable( void )
{
	/* Disable the Analog Comparator interrupt */
	CLR_BIT( ACSR , ACIE );
}





/*
 * @brief Sets the callback function for the Analog Comparator interrupt.
 *
 * This function sets a user-defined callback function to be called when the
 * Analog Comparator interrupt occurs.
 *
 * @example
 * void AC_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * AC_SetCallback( AC_InterruptHandler );
 *
 * @param CopyFuncPtr: Pointer to the callback function. The function should have a
 * 					   void return type and no parameters.
 */
void AC_SetCallback( void (*CopyFuncPtr)(void) )
{
	/* Copy the pointer */
	g_AC_CallBack	= CopyFuncPtr;
}





/*
 * @brief ISR for the Analog Comparator interrupt.
 *
 * This interrupt service routine (ISR) is called when the Analog Comparator interrupt is triggered.
 * It will invoke the registered callback function, if set.

 * @see AC_SetCallback for setting the callback function.
 */
void __vector_18(void)		__attribute__((signal));
void __vector_18(void)
{

		/* Check that the pointer is valid */
		if(g_AC_CallBack != NULL)
		{
			/* Call The pointer to function */
			g_AC_CallBack();
		}
}








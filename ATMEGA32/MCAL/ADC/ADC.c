/****************************************************************************
 * @file    ADC.c
 * @author  Boles Medhat
 * @brief   ADC Driver Source File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-16]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides an abstraction layer for the Analog-to-Digital Converter (ADC)
 * in the ATmega32 microcontroller. It supports both 8-bit and 10-bit resolutions,
 * single and auto trigger conversion modes, interrupt handling, and callback registration.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `ADC_config.h` for macro-based configuration.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "ADC.h"

/* Pointer to the callback function for the ADC ISR */
void (*g_ADC_CallBack)(uint16) = NULL;





/*
 * @brief Initializes the ADC based on configuration options.
 *
 * This function sets up the ADC voltage reference, adjustment mode,
 * prescaler, ADC mode (auto trigger or single conversion), and interrupt status.
 * It configures the ADC registers according to the defined macros in `ADC_config.h`.
 *
 * @see `ADC_config.h` for configuration options.
 */
void ADC_Init(void)
{
    /* Check the ADC voltage reference */
    #if   ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AREF

        /* ADC voltage reference is AREF pin */
        CLR_BIT(ADMUX, REFS1); CLR_BIT(ADMUX, REFS0);

    #elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_AVCC

        /* ADC voltage reference is AVCC pin */
        CLR_BIT(ADMUX, REFS1); SET_BIT(ADMUX, REFS0);

    #elif ADC_VOLTAGE_REF == ADC_VOLTAGE_REF_2_56V

        /* ADC voltage reference is internal 2.56V */
        SET_BIT(ADMUX, REFS1); SET_BIT(ADMUX, REFS0);

    #else
        /* Make an error */
        #error "Wrong \"ADC_VOLTAGE_REF\" configuration option"
    #endif


    /* Check the adjust mode */
    #if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

        /* ADC in right adjust mode */
        CLR_BIT(ADMUX, ADLAR);

    #elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

        /* ADC in left adjust mode */
        SET_BIT(ADMUX, ADLAR);

    #else
        /* Make an error */
        #error "Wrong \"ADC_ADJUSTMENT\" configuration option"
    #endif


    /* Clear the prescaler bits */
    ADCSRA &= ADC_PRESCALER_clr_msk;

    /* Set the prescaler value */
    ADCSRA |= ADC_PRESCALER;


    /* Check the ADC mode */
    #if  ADC_MODE == ADC_MODE_AUTO_TRIGGER

        /* Disable ADC auto trigger before setting the auto trigger source */
        CLR_BIT(ADCSRA, ADATE);

        /* Clear the ADC auto trigger source bits */
        SFIOR &= ADC_AUTO_TRIG_clr_msk;

        /* Set the ADC auto trigger source bits */
        SFIOR |= ADC_AUTO_TRIG_SRC;

        /* Enable ADC auto trigger */
        SET_BIT(ADCSRA, ADATE);

    #elif ADC_MODE == ADC_MODE_SINGLE_CONVERSION

        /* Disable ADC auto trigger */
        CLR_BIT(ADCSRA, ADATE);

    #else
        /* Make an error */
        #error "Wrong \"ADC_MODE\" configuration option"
    #endif


    /* Enable the ADC */
    SET_BIT(ADCSRA, ADEN);


    /* Check if the ADC interrupt is enabled */
    #if   ADC_INT_STATUS == ADC_INT_ENABLE

        /* Clear the ADC interrupt flag */
        SET_BIT(ADCSRA, ADIF);

        /* Enable the ADC interrupt */
        SET_BIT(ADCSRA, ADIE);

        /* Enable global interrupt */
        SET_BIT(SREG, I);

    #elif ADC_INT_STATUS == ADC_INT_DISABLE

        /* Disable the ADC interrupt */
        CLR_BIT(ADCSRA, ADIE);

    #else
        /* Make an error */
        #error "Wrong \"ADC_INT_STATUS\" configuration option"
    #endif
}





/*
 * @brief Starts the ADC conversion for the specified channel without reading the result.
 *
 * This function initiates the conversion process for the given ADC channel.
 * It does not wait for the conversion to complete.
 * The result can be read later using the appropriate read function ( uint16 ADC_OnlyRead( void ) ).
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 */
void ADC_OnlyStartConversion( uint8 ADC_channel )
{

	/* Clear the channel bits */
	ADMUX &= ADC_CHANNEL_clr_msk;

	/* Set the channel bits */
	ADMUX |= ADC_channel;

	/* Start conversion */
	SET_BIT( ADCSRA , ADSC );
}





/*
 * @brief Reads the ADC result without starting a new conversion.
 *
 * This function returns the ADC result without starting a new conversion.
 * The ADC conversion must be completed before calling this function.
 * It checks for a timeout condition if specified and returns 0 in case of a timeout.
 *
 * @return: The ADC result. The return value depends on the adjustment mode (10-bit or 8-bit).
 */
uint16 ADC_OnlyRead( void )
{

	/* Check if there is a limit for waiting */
	#if ADC_COUNTOUT != ADC_WAIT_FOREVER

		/* Counter that count until it equals ADC_COUNTOUT */
		/* to end the waiting if conversion does not end */
		volatile uint16 ADC_counter = 0;

		/* Waiting until the conversion is complete or until waiting time is end */
		while (GET_BIT( ADCSRA , ADSC ) && ADC_counter < ADC_COUNTOUT)
		{
			/* Counter up */
			ADC_counter++;
		}


		/* Check that the conversion is end correctly */
		if(ADC_counter < ADC_COUNTOUT)
		{
			/* the conversion is end correctly */

			/* Return the 10 bits in any adjust mode */
			#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

				/* Return the 10 bits */
				return ADC;

			#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

				/* Return the 8 bits */
				return ADCH;

			#endif
		}
		else
		{
			/* the conversion has not end correctly */

			/* Return 0 */
			return 0;
		}

	#else

		/* Waiting until the conversion is complete */
		while (GET_BIT( ADCSRA , ADSC ));

		/* Return the 10 bits in any adjust mode */
		#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

			/* Return the 10 bits */
			return ADC;

		#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

			/* Return the 8 bits */
			return ADCH;

		#endif

	#endif
}





/*
 * @brief Starts an ADC conversion and returns the 10-bit result.
 *
 * This function starts a conversion for the specified ADC channel and waits for the result to be ready.
 * It returns the result as a 10-bit value.
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 *
 * @return: The 10-bit ADC result.
 */
uint16 ADC_Read_10_Bits( uint8 ADC_channel )
{

	/* Start Conversion */
	ADC_OnlyStartConversion( ADC_channel );

	/* Return the 10 BITS in any Adjust mode */
	#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

		/* Return the 10 BITS */
		return ADC_OnlyRead();

	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* Return the 10 BITS */
		return (ADC_OnlyRead() << 2);

	#endif


}





/*
 * @brief Starts an ADC conversion and returns the 8-bit result.
 *
 * This function starts a conversion for the specified ADC channel and waits for the result to be ready.
 * It returns the result as an 8-bit value.
 *
 * @param ADC_channel: The ADC channel to convert. This should be one of the available channels (e.g., ADC0, ADC1, etc.).
 *
 * @return: The 8-bit ADC result.
 */
uint8 ADC_Read_8_Bits( uint8 ADC_channel )
{

	/* Start Conversion */
	ADC_OnlyStartConversion( ADC_channel );

	/* Return the 8 BITS in any Adjust mode */
	#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

	/* Return the 8 MSB */
	return (ADC_OnlyRead() >> 2);

	#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

		/* Return the 8 MSB */
		return ADC_OnlyRead();

	#endif


}





/*
 * @brief Enables the ADC.
 *
 * This function enables the ADC by setting the ADEN bit in the ADCSRA register.
 */
void ADC_Enable ( void )
{
	/* Enable the ADC */
	SET_BIT( ADCSRA , ADEN );
}





/*
 * @brief Disables the ADC.
 *
 * This function disables the ADC by clearing the ADEN bit in the ADCSRA register.
 */
void ADC_Disable ( void )
{
	/* Disable the ADC */
	CLR_BIT( ADCSRA , ADEN );
}





/*
 * @brief Enables ADC Auto Triggering.
 *
 * This function enables ADC auto triggering by setting the appropriate bits in the ADCSRA and SFIOR registers.
 */
void ADC_AutoTriggerEnable ( void )
{
	/* Enable ADC Auto Trigger */

	/* Clear the ADC AUTO TRIGGER Source Bits */
	SFIOR &= ADC_AUTO_TRIG_clr_msk;

	/* Set the ADC AUTO TRIGGER Source Bits */
	SFIOR |= ADC_AUTO_TRIG_SRC;

	/* Enable ADC Auto Trigger */
	SET_BIT( ADCSRA , ADATE );
}





/*
 * @brief Disables ADC Auto Triggering.
 *
 * This function disables ADC auto triggering by clearing the ADATE bit in the ADCSRA register.
 */
void ADC_AutoTriggerDisable ( void )
{
	/* Disable ADC Auto Trigger */
	CLR_BIT( ADCSRA , ADATE );
}





/*
 * @brief Enables ADC Interrupt.
 *
 * This function enables the ADC interrupt by setting the ADIE bit in the ADCSRA register.
 */
void ADC_InterruptEnable ( void )
{
	/* Enable the ADC Interrupt */
	SET_BIT( ADCSRA , ADIE );
}





/*
 * @brief Disables ADC Interrupt.
 *
 * This function disables the ADC interrupt by clearing the ADIE bit in the ADCSRA register.
 */
void ADC_InterruptDisable ( void )
{
	/* Disable the ADC Interrupt */
	CLR_BIT( ADCSRA , ADIE );
}





/*
 * @brief Sets the callback function for the ADC interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the ADC conversion completes (interrupt-based).
 * The ADC result (10-bit) is passed as a parameter to the callback function.
 *
 * @example
 * void ADC_InterruptHandler(uint16 result)
 * {
 *     // Process ADC result
 * }
 * ...
 * ADC_SetCallback( ADC_InterruptHandler );
 *
 * @param CopyFuncPtr Pointer to the callback function.
 *        The function must have a uint16 parameter and void return type.
 */
void ADC_SetCallback( void (*CopyFuncPtr)(uint16) )
{

	/* Copy the function pointer */
	g_ADC_CallBack = CopyFuncPtr;
}





/*
 * @brief ISR for the ADC interrupt.
 *
 * This ISR is triggered when an ADC interrupt occurs.
 * It reads the ADC result and passes it to the user-defined callback function,
 * previously registered with ADC_SetCallback().
 *
 * @see ADC_SetCallback for setting the callback function.
 */
void __vector_16(void)		__attribute__((signal));
void __vector_16(void)
{

	/* Check that the pointer is valid */
	if(g_ADC_CallBack != NULL)
	{

		/* Call the callback function and return 10 bit ADC value */
		#if   ADC_ADJUSTMENT == ADC_RIGHT_ADJUSTED

			g_ADC_CallBack( ADC );

		#elif ADC_ADJUSTMENT == ADC_LEFT_ADJUSTED

			g_ADC_CallBack( ADC >> 6 );

		#endif
	}
}







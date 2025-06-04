/****************************************************************************
 * @file    EXTI.c
 * @author  Boles Medhat
 * @brief   External Interrupt (EXTI) Driver Source File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for External Interrupt in ATmega32
 * microcontroller, It supports INT0, INT1, and INT2 with customizable pin modes,
 * sense control, and user-defined callback functions.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `EXTI_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "EXTI.h"

/* Array of pointer to the callback function for the external interrupts ISR */
void (*g_EXTI_CallBack[3])(void) = { NULL, NULL, NULL };





/*
 * @brief Initializes the external interrupts based on configuration options.
 *
 * This function initializes the external interrupts (INT0, INT1, INT2) by configuring the pin modes,
 * sense control, and enabling/disabling interrupts.
 * It configures the external interrupts registers according to the defined macros in `EXTI_config.h`.
 * It also sets up global interrupt enable.
 *
 * @see `EXTI_config.h` for configuration options.
 */
void EXTI_Init( void )
{

	/* Disable Global Interrupt */
	CLR_BIT( SREG , I );

	/********  External Interrupt 0   ********/

	/* Check if the External Interrupt 0 is Enable */
	#if	  EXTI_0_STATUS == EXTI_ENABLE

		/* Disable the External Interrupts 0 */
		CLR_BIT( GICR , INT0 );

		/* Check the External Interrupt 0 PIN mode */
		#if	  EXTI_0_PIN_MODE == EXTI_INPUT

			/* Set External Interrupt 0 PIN as Floating Input */
			CLR_BIT( DDRD,INT0_PIN );

		#elif EXTI_0_PIN_MODE == EXTI_INPUT_PULLUP

			/* Set External Interrupt 0 PIN as Pull-up Input */
			CLR_BIT( DDRD,INT0_PIN );
			SET_BIT( PORTD,INT0_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_0_PIN_MODE\" configuration option"
		#endif


		/* Check the External Interrupt 0 Sense Control */
		#if	  EXTI_0_SENSE_CONTROL == EXTI_THE_LOW_LEVEL

			/* The Low Level Generates an Interrupt Request */
			CLR_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 );

		#elif EXTI_0_SENSE_CONTROL == EXTI_ANY_LOGIC_CHANGE

			/* Any Logical Change Generates an Interrupt Request */
			CLR_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );

		#elif EXTI_0_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

			/* The Falling Edge Generates an Interrupt Request */
			SET_BIT( MCUCR , ISC01 ); CLR_BIT( MCUCR , ISC00 );

		#elif EXTI_0_SENSE_CONTROL == EXTI_THE_RISING_EDGE

			/* The Rising Edge generates an Interrupt Request */
			SET_BIT( MCUCR , ISC01 ); SET_BIT( MCUCR , ISC00 );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_0_SENSE_CONTROL\" configuration option"
		#endif

		/* Clear the External Interrupt 0 Flag */
		SET_BIT( GIFR , INTF0 );

		/* Enable the External Interrupts 0 */
		SET_BIT( GICR , INT0 );

	#elif EXTI_0_STATUS == EXTI_DISABLE

		/* Disable the External Interrupts 0 */
		CLR_BIT( GICR , INT0 );

	#else
		/* Make an Error */
		#error	"Wrong in \"EXTI_0_STATUS\" configuration"
	#endif


	/********   External Interrupt 1   ********/

	/* Check if the External Interrupt 1 is Enable */
	#if	  EXTI_1_STATUS == EXTI_ENABLE

		/* Disable the External Interrupts 1 */
		CLR_BIT( GICR , INT1 );

		/* Check the External Interrupt 1 PIN mode */
		#if	  EXTI_1_PIN_MODE == EXTI_INPUT

			/* Set External Interrupt 1 PIN as Floating Input */
			CLR_BIT( DDRD,INT1_PIN );

		#elif EXTI_1_PIN_MODE == EXTI_INPUT_PULLUP

			/* Set External Interrupt 1 PIN as Pull-up Input */
			CLR_BIT( DDRD,INT1_PIN );
			SET_BIT( PORTD,INT1_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_1_PIN_MODE\" configuration option"
		#endif


		/* Check the External Interrupt 1 Sense Control */
		#if	  EXTI_1_SENSE_CONTROL == EXTI_THE_LOW_LEVEL

			/* The Low Level Generates an Interrupt Request */
			CLR_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 );

		#elif EXTI_1_SENSE_CONTROL == EXTI_ANY_LOGIC_CHANGE

			/* Any Logical Change Generates an Interrupt Request */
			CLR_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );

		#elif EXTI_1_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

			/* The Falling Edge Generates an Interrupt Request */
			SET_BIT( MCUCR , ISC11 ); CLR_BIT( MCUCR , ISC10 );

		#elif EXTI_1_SENSE_CONTROL == EXTI_THE_RISING_EDGE

			/* The Rising Edge generates an Interrupt Request */
			SET_BIT( MCUCR , ISC11 ); SET_BIT( MCUCR , ISC10 );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_1_SENSE_CONTROL\" configuration option"
		#endif

		/* Clear the External Interrupt 1 Flag */
		SET_BIT( GIFR , INTF1 );

		/* Enable the External Interrupts 1 */
		SET_BIT( GICR , INT1 );


	#elif EXTI_1_STATUS == EXTI_DISABLE

		/* Disable the External Interrupts 1 */
		CLR_BIT( GICR , INT1 );

	#else
		/* Make an Error */
		#error	"Wrong in \"EXTI_1_STATUS\" configuration"
	#endif


	/********   External Interrupt 2   ********/

	/* Check if the External Interrupt 2 is Enable */
	#if	  EXTI_2_STATUS == EXTI_ENABLE

		/* Disable the External Interrupts 2 */
		CLR_BIT( GICR , INT2 );

		/* Check the External Interrupt 2 PIN mode */
		#if	  EXTI_2_PIN_MODE == EXTI_INPUT

			/* Set External Interrupt 2 PIN as Floating Input */
			CLR_BIT( DDRB,INT2_PIN );

		#elif EXTI_2_PIN_MODE == EXTI_INPUT_PULLUP

			/* Set External Interrupt 2 PIN as Pull-up Input */
			CLR_BIT( DDRB,INT2_PIN );
			SET_BIT( PORTB,INT2_PIN );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_2_PIN_MODE\" configuration option"
		#endif


		/* Check the External Interrupt 2 Sense Control */
		#if EXTI_2_SENSE_CONTROL == EXTI_THE_FALLING_EDGE

			/* The Falling Edge Generates an Interrupt Request */
			CLR_BIT( MCUCSR , ISC2 );

		#elif EXTI_2_SENSE_CONTROL == EXTI_THE_RISING_EDGE

			/* The Rising Edge generates an Interrupt Request */
			SET_BIT( MCUCSR , ISC2 );

		#else
			/* Make an Error */
			#error "Wrong \"EXTI_2_SENSE_CONTROL\" configuration option"
		#endif

		/* Clear the External Interrupt 2 Flag */
		SET_BIT( GIFR , INTF2 );

		/* Enable the External Interrupts 2 */
		SET_BIT( GICR , INT2 );


	#elif EXTI_2_STATUS == EXTI_DISABLE

		/* Disable the External Interrupts 2 */
		CLR_BIT( GICR , INT2 );

	#else
		/* Make an Error */
		#error	"Wrong in \"EXTI_2_STATUS\" configuration"
	#endif


	/* Enable Global Interrupt */
	SET_BIT( SREG , I );
}





/*
 * @brief Disables a specified external interrupt.
 *
 * This function disables the external interrupt corresponding to the specified ID (INT0, INT1, or INT2).
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 */
void EXTI_DisableInterrupt( uint8 interrupt_id )
{
	/* Check on the External Interrupt Number */

	/* Disable External Interrupt 0 */
	if (interrupt_id == EXTI_INT0_ID)
	{
		CLR_BIT( GICR , INT0 );
	}
	/* Disable External Interrupt 1 */
	else if (interrupt_id == EXTI_INT1_ID)
	{
		CLR_BIT( GICR , INT1 );
	}
	/* Disable External Interrupt 2 */
	else if (interrupt_id == EXTI_INT2_ID)
	{
		CLR_BIT( GICR , INT2 );
	}
}





/*
 * @brief Enables a specified external interrupt.
 *
 * This function enables the external interrupt corresponding to the specified ID (INT0, INT1, or INT2).
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 */
void EXTI_EnableInterrupt( uint8 interrupt_id )
{
	/* Check on the External Interrupt Number */

	/* Enable External Interrupt 0 */
	if (interrupt_id == EXTI_INT0_ID)
	{
		SET_BIT( GICR , INT0 );
	}
	/* Enable External Interrupt 1 */
	else if (interrupt_id == EXTI_INT1_ID)
	{
		SET_BIT( GICR , INT1 );
	}
	/* Enable External Interrupt 2 */
	else if (interrupt_id == EXTI_INT2_ID)
	{
		SET_BIT( GICR , INT2 );
	}
}





/*
 * @brief Changes the sense control of a specified external interrupt.
 *
 * This function allows the runtime configuration of the sense control for an external interrupt
 * (INT0, INT1, or INT2) to one of the following modes: low level, any logic change, falling edge,
 * or rising edge.
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 * @param sense_mode:   The sense control mode:
 * 						 - EXTI_THE_LOW_LEVEL
 * 						 - EXTI_ANY_LOGIC_CHANGE
 * 						 - EXTI_THE_FALLING_EDGE
 * 						 - EXTI_THE_RISING_EDGE
 *
 * @note INT2 supports only EXTI_THE_FALLING_EDGE and EXTI_THE_RISING_EDGE.
 *
 */
void EXTI_ChangeSenseControl( uint8 interrupt_id , uint8 sense_mode )
{
	/* Check on the External Interrupt Number */

	/* External Interrupt 0 */
	if (interrupt_id == EXTI_INT0_ID)
	{
		/* Check on the External Interrupt 0 Sense Control */

		/* The Low Level Generates an Interrupt Request */
		if (sense_mode == EXTI_THE_LOW_LEVEL)
		{
			CLR_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
		}
		/* Any Logical Change Generates an Interrupt Request */
		else if (sense_mode == EXTI_ANY_LOGIC_CHANGE)
		{
			CLR_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
		}
		/* The Falling Edge Generates an Interrupt Request */
		else if (sense_mode == EXTI_THE_FALLING_EDGE)
		{
			SET_BIT(MCUCR, ISC01);
			CLR_BIT(MCUCR, ISC00);
		}
		/* The Rising Edge generates an Interrupt Request */
		else if (sense_mode == EXTI_THE_RISING_EDGE)
		{
			SET_BIT(MCUCR, ISC01);
			SET_BIT(MCUCR, ISC00);
		}
	}

	/* External Interrupt 1 */
	else if (interrupt_id == EXTI_INT1_ID)
	{
		/* Check on the External Interrupt 1 Sense Control */

		/* The Low Level Generates an Interrupt Request */
		if (sense_mode == EXTI_THE_LOW_LEVEL)
		{
			CLR_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
		}
		/* Any Logical Change Generates an Interrupt Request */
		else if (sense_mode == EXTI_ANY_LOGIC_CHANGE)
		{
			CLR_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
		}
		/* The Falling Edge Generates an Interrupt Request */
		else if (sense_mode == EXTI_THE_FALLING_EDGE)
		{
			SET_BIT(MCUCR, ISC11);
			CLR_BIT(MCUCR, ISC10);
		}
		/* The Rising Edge generates an Interrupt Request */
		else if (sense_mode == EXTI_THE_RISING_EDGE)
		{
			SET_BIT(MCUCR, ISC11);
			SET_BIT(MCUCR, ISC10);
		}
	}

	/* External Interrupt 2 */
	else if (interrupt_id == EXTI_INT2_ID)
	{
		/* Check on the External Interrupt 2 Sense Control */

		/* The Falling Edge Generates an Interrupt Request */
		if (sense_mode == EXTI_THE_FALLING_EDGE)
		{
			CLR_BIT(MCUCSR, ISC2);
		}
		/* The Rising Edge generates an Interrupt Request */
		else if (sense_mode == EXTI_THE_RISING_EDGE)
		{
			SET_BIT(MCUCSR, ISC2);
		}
	}
}





/*
 * @brief Sets a callback function for a specified external interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified external interrupt (INT0, INT1, or INT2) interrupt occurs.
 *
 * @example
 * void EXTI_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * EXTI_SetCallback( EXTI_INT0_ID , EXTI_InterruptHandler );
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void EXTI_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) )
{

	/* Check that the Pointer is Valid */
	if( interrupt_id < EXTI_MAX_INTERRUPTS )
	{
		/* Copy the Function Pointer */
		g_EXTI_CallBack[ interrupt_id ] = CopyFuncPtr;
	}
}





/*
 * @brief ISR for External Interrupt 0.
 *
 * This ISR is triggered when External Interrupt 0 (INT0) occurs.
 * It calls the user-defined callback function set by the EXTI_SetCallback function.
 *
 * @see EXTI_SetCallback for setting the callback function.
 */
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{

	/* Check that the Pointer is Valid */
	if( g_EXTI_CallBack[0] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_EXTI_CallBack[0]();
	}
}





/*
 * @brief ISR for External Interrupt 1.
 *
 * This ISR is triggered when External Interrupt 1 (INT1) occurs.
 * It calls the user-defined callback function set by the EXTI_SetCallback function.
 *
 * @see EXTI_SetCallback for setting the callback function.
 */
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{

	/* Check that the Pointer is Valid */
	if( g_EXTI_CallBack[1] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_EXTI_CallBack[1]();
	}
}





/*
 * @brief ISR for External Interrupt 2.
 *
 * This ISR is triggered when External Interrupt 2 (INT2) occurs.
 * It calls the user-defined callback function set by the EXTI_SetCallback function.
 *
 * @see EXTI_SetCallback for setting the callback function.
 */
void __vector_3(void)		__attribute__((signal));
void __vector_3(void)
{
	/* ISR for External Interrupt 2 */

	/* Check that the Pointer is Valid */
	if( g_EXTI_CallBack[2] != NULL )
	{
		/* Call The Global Pointer to Function */
		g_EXTI_CallBack[2]();
	}
}





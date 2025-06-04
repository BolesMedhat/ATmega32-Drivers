/****************************************************************************
 * @file    DIO.c
 * @author  Boles Medhat
 * @brief   DIO Driver Source File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides an abstraction for managing the Digital Input/Output
 * (DIO) functionality on ATmega32 microcontroller ports and pins. It includes
 * functions for configuring pin directions, setting pin values, and reading pin
 * states. Additionally, it supports controlling the entire port at once and toggling
 * pin or port values.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "DIO.h"





/*
 * @brief Sets the direction of a specific pin in a specific port.
 *
 * @param dio_port: 		 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin: 		 Pin number [ DIO_PIN0 to DIO_PIN7 ].
 * @param pin_direction: Direction [ INPUT , OUTPUT , INPUT_PULLUP ].
 */
void DIO_SetPinDirection( uint8 dio_port , uint8 dio_pin , uint8 pin_direction )
{

	/* Check on the direction */
	switch( pin_direction )
	{

	/* Output direction */
		case OUTPUT:

			/* Check which DIO Port is specified */
			switch( dio_port )
			{
				/* Direction Port A as output */
				case DIO_PORTA:	SET_BIT( DDRA , dio_pin );	break;

				/* Direction Port B as output */
				case DIO_PORTB:	SET_BIT( DDRB , dio_pin );	break;

				/* Direction Port C as output */
				case DIO_PORTC:	SET_BIT( DDRC , dio_pin );	break;

				/* Direction Port D as output */
				case DIO_PORTD:	SET_BIT( DDRD , dio_pin );	break;
			}
			break;

		/* Input direction */
		case INPUT:

			/* Check which DIO Port is specified */
			switch( dio_port )
			{
				/* Direction Port A as input */
				case DIO_PORTA:	CLR_BIT( DDRA , dio_pin );	break;

				/* Direction Port B as input */
				case DIO_PORTB:	CLR_BIT( DDRB , dio_pin );	break;

				/* Direction Port C as input */
				case DIO_PORTC:	CLR_BIT( DDRC , dio_pin );	break;

				/* Direction Port D as input */
				case DIO_PORTD:	CLR_BIT( DDRD , dio_pin );	break;
			}
			break;

		/* Input Pull-up direction */
		case INPUT_PULLUP:

			/* Check which DIO Port is specified */
			switch( dio_port )
			{
				/* Direction Port A as input pull-up */
				case DIO_PORTA:	CLR_BIT( DDRA , dio_pin );	SET_BIT( PORTA , dio_pin );	break;

				/* Direction Port B as input pull-up */
				case DIO_PORTB:	CLR_BIT( DDRB , dio_pin );	SET_BIT( PORTB , dio_pin );	break;

				/* Direction Port C as input pull-up */
				case DIO_PORTC:	CLR_BIT( DDRC , dio_pin );	SET_BIT( PORTC , dio_pin );	break;

				/* Direction Port D as input pull-up */
				case DIO_PORTD:	CLR_BIT( DDRD , dio_pin );	SET_BIT( PORTD , dio_pin );	break;
			}
			break;
	}

}





/*
 * @brief Sets the direction of all pins in a port.
 *
 * @param dio_port: 		 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param pin_direction: Direction [ INPUT , OUTPUT , INPUT_PULLUP ].
 */
void DIO_SetPortDirection( uint8 dio_port , uint8 port_direction )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Direction Port A */
		case DIO_PORTA:	DDRA = port_direction;	break;

		/* Direction Port B */
		case DIO_PORTB:	DDRB = port_direction;	break;

		/* Direction Port C */
		case DIO_PORTC:	DDRC = port_direction;	break;

		/* Direction Port D */
		case DIO_PORTD:	DDRD = port_direction;	break;
	}
}






/*
 * @brief Sets the value (HIGH or LOW) of a specific pin.
 *
 * @param dio_port: 	 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin: 	 Pin number [ DIO_PIN0 to DIO_PIN7 ].
 * @param pin_value: Pin value [ LOW , HIGH ].
 */
void DIO_SetPinValue( uint8 dio_port , uint8 dio_pin , uint8 pin_value )
{

	/* Check on the pin value */
	switch( pin_value )
	{
		/* High value */
		case HIGH:

			/* Check which DIO Port is specified */
			switch( dio_port )
			{
				/* Set Port A value as High */
				case DIO_PORTA:	SET_BIT( PORTA , dio_pin );	break;

				/* Set Port B value as High */
				case DIO_PORTB:	SET_BIT( PORTB , dio_pin );	break;

				/* Set Port C value as High */
				case DIO_PORTC:	SET_BIT( PORTC , dio_pin );	break;

				/* Set Port D value as High */
				case DIO_PORTD:	SET_BIT( PORTD , dio_pin );	break;
			}
			break;

		/* low value */
		case LOW:

			/* Check which DIO Port is specified */
			switch( dio_port )
			{
				/* Set Port A value as Low */
				case DIO_PORTA:	CLR_BIT( PORTA , dio_pin );	break;

				/* Set Port B value as Low */
				case DIO_PORTB:	CLR_BIT( PORTB , dio_pin );	break;

				/* Set Port B value as Low */
				case DIO_PORTC:	CLR_BIT( PORTC , dio_pin );	break;

				/* Set Port D value as Low */
				case DIO_PORTD:	CLR_BIT( PORTD , dio_pin );	break;
			}
			break;
	}
}





/*
 * @brief Sets the value of all pins in a port.
 *
 * @param dio_port: 	 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param pin_value: Pin value [ LOW , HIGH ].
 */
void DIO_SetPortValue( uint8 dio_port , uint8 port_value )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Set Port A value */
		case DIO_PORTA:	PORTA = port_value;	break;

		/* Set Port B value */
		case DIO_PORTB:	PORTB = port_value;	break;

		/* Set Port C value */
		case DIO_PORTC:	PORTC = port_value;	break;

		/* Set Port D value */
		case DIO_PORTD:	PORTD = port_value;	break;

	}
}





/*
 * @brief Gets the current value (HIGH or LOW) of a specific pin.
 *
 * @param dio_port: DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin:  Pin number [ DIO_PIN0 to DIO_PIN7 ].
 *
 * @return (uint8) Logic level of the specified pin [0 or 1].
 */
uint8 DIO_GetPinValue( uint8 dio_port , uint8 dio_pin )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Return the Pin value from Port A */
		case DIO_PORTA:	return GET_BIT( PINA , dio_pin );

		/* Return the Pin value from Port B */
		case DIO_PORTB:	return GET_BIT( PINB , dio_pin );

		/* Return the Pin value from Port C */
		case DIO_PORTC:	return GET_BIT( PINC , dio_pin );

		/* Return the Pin value from Port D */
		case DIO_PORTD:	return GET_BIT( PIND , dio_pin );

		/* Return 0 with wrong DIO Port */
		default:		return 0;
	}
}





/*
 * @brief Returns the current value of the specified port.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 *
 * @return (uint8) value representing port logic levels.
 */
uint8 DIO_GetPortValue( uint8 dio_port )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Return Port A value */
		case DIO_PORTA:	return PINA;

		/* Return Port B value */
		case DIO_PORTB:	return PINB;

		/* Return Port C value */
		case DIO_PORTC:	return PINC;

		/* Return Port D value */
		case DIO_PORTD:	return PIND;

		/* Return 0 with wrong DIO Port */
		default:		return 0x00;
	}
}





/*
 * @brief Toggles the current state of a specific pin.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin:  Pin number [ DIO_PIN0 to DIO_PIN7 ].
 */
void DIO_TogglePinValue( uint8 dio_port , uint8 dio_pin )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Toggle the Pin value from Port A */
		case DIO_PORTA:	TOG_BIT( PORTA , dio_pin );	break;

		/* Toggle the Pin value from Port B */
		case DIO_PORTB:	TOG_BIT( PORTB , dio_pin );	break;

		/* Toggle the Pin value from Port C */
		case DIO_PORTC:	TOG_BIT( PORTC , dio_pin );	break;

		/* Toggle the Pin value from Port D */
		case DIO_PORTD:	TOG_BIT( PORTD , dio_pin );	break;
	}
}





/*
 * @brief Toggles all bits of the specified port.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 */
void DIO_TogglePortValue( uint8 dio_port )
{

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Toggle Port A value */
		case DIO_PORTA:	PORTA ^= 0xFF;	break;

		/* Toggle Port B value */
		case DIO_PORTB:	PORTB ^= 0xFF;	break;

		/* Toggle Port C value */
		case DIO_PORTC:	PORTC ^= 0xFF;	break;

		/* Toggle Port D value */
		case DIO_PORTD:	PORTD ^= 0xFF;	break;
	}
}





/*
 * @brief Sets the upper 4 bits of a port with a given nibble value.
 *
 * @param dio_port:     Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param nibble_value: 4-bit value to be placed in the upper nibble (bits 4-7).
 */
void DIO_SetUpperNibble( uint8 dio_port , uint8 nibble_value )
{

	/* Shift the nibble value to the upper 4 bits */
	nibble_value <<= 4;

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Handle Port A case */
		case DIO_PORTA:

			/* Clear the upper 4 bits in Port A */
			PORTA &= 0x0F;

			/* Set the upper 4 bits in Port A with the new nibble value */
			PORTA |= nibble_value;
			break;

		/* Handle Port B case */
		case DIO_PORTB:

			/* Clear the upper 4 bits in Port B */
			PORTB &= 0x0F;

			/* Set the upper 4 bits in Port B with the new nibble value */
			PORTB |= nibble_value;
			break;

		/* Handle Port C case */
		case DIO_PORTC:

			/* Clear the upper 4 bits in Port C */
			PORTC &= 0x0F;

			/* Set the upper 4 bits in Port C with the new nibble value */
			PORTC |= nibble_value;
			break;

		/* Handle Port D case */
		case DIO_PORTD:

			/* Clear the upper 4 bits in Port D */
			PORTD &= 0x0F;

			/* Set the upper 4 bits in Port D with the new nibble value */
			PORTD |= nibble_value;
			break;
	}
}





/*
 * @brief Sets the lower 4 bits of a port with a given nibble value.
 *
 * @param dio_port:      Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param nibble_value: 4-bit value to be placed in the lower nibble (bits 0-3).
 */
void DIO_SetLowerNibble( uint8 dio_port , uint8 nibble_value )
{

	/* Mask nibble_value to ensure it only affects the lower 4 bits */
	nibble_value &= 0x0F;

	/* Check which DIO Port is specified */
	switch( dio_port )
	{
		/* Handle Port A case */
		case DIO_PORTA:

			/* Clear the lower 4 bits in Port A */
			PORTA &= 0xF0;

			/* Set the lower 4 bits in Port A with the new nibble value */
			PORTA |= nibble_value;
			break;

		/* Handle Port B case */
		case DIO_PORTB:

			/* Clear the lower 4 bits in Port B */
			PORTB &= 0xF0;

			/* Set the lower 4 bits in Port B with the new nibble value */
			PORTB |= nibble_value;
			break;

		/* Handle Port C case */
		case DIO_PORTC:

			/* Clear the lower 4 bits in Port C */
			PORTC &= 0xF0;

			/* Set the lower 4 bits in Port C with the new nibble value */
			PORTC |= nibble_value;
			break;

		/* Handle Port D case */
		case DIO_PORTD:

			/* Clear the lower 4 bits in Port D */
			PORTD &= 0xF0;

			/* Set the lower 4 bits in Port D with the new nibble value */
			PORTD |= nibble_value;
			break;
	}
}






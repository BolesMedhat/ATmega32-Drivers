/****************************************************************************
 * @file    DIO.h
 * @author  Boles Medhat
 * @brief   DIO Driver Header - AVR ATmega32
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
 * The driver supports operations such as:
 * - Setting the direction of specific pins or entire ports.
 * - Setting, reading, and toggling individual pin values.
 * - Setting, reading, and toggling values for all pins in a port.
 * - Handling upper and lower nibbles for ports.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include "../../LIB/BIT_MATH.h"
#include "DIO_def.h"


/*
 * @brief Sets the direction of a specific pin in a specific port.
 *
 * @param dio_port: 		 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin: 		 Pin number [ DIO_PIN0 to DIO_PIN7 ].
 * @param pin_direction: Direction [ INPUT , OUTPUT , INPUT_PULLUP ].
 */
void DIO_SetPinDirection( uint8 dio_port , uint8 dio_pin , uint8 pin_direction );



/*
 * @brief Sets the direction of all pins in a port.
 *
 * @param dio_port: 		 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param pin_direction: Direction [ INPUT , OUTPUT , INPUT_PULLUP ].
 */
void DIO_SetPortDirection( uint8 dio_port , uint8 port_direction );


/*
 * @brief Sets the value (HIGH or LOW) of a specific pin.
 *
 * @param dio_port: 	 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin: 	 Pin number [ DIO_PIN0 to DIO_PIN7 ].
 * @param pin_value: Pin value [ LOW , HIGH ].
 */
void DIO_SetPinValue( uint8 dio_port , uint8 dio_pin , uint8 pin_value );


/*
 * @brief Sets the value of all pins in a port.
 *
 * @param dio_port: 	 DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param pin_value: Pin value [ LOW , HIGH ].
 */
void DIO_SetPortValue( uint8 dio_port , uint8 port_value );


/*
 * @brief Gets the current value (HIGH or LOW) of a specific pin.
 *
 * @param dio_port: DIO Port [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin:  Pin number [ DIO_PIN0 to DIO_PIN7 ].
 *
 * @return (uint8) Logic level of the specified pin [0 or 1].
 */
uint8 DIO_GetPinValue( uint8 dio_port , uint8 dio_pin );


/*
 * @brief Returns the current value of the specified port.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 *
 * @return (uint8) value representing port logic levels.
 */
uint8 DIO_GetPortValue( uint8 dio_port );


/*
 * @brief Toggles the current state of a specific pin.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param dio_pin:  Pin number [ DIO_PIN0 to DIO_PIN7 ].
 */
void DIO_TogglePinValue( uint8 dio_port , uint8 dio_pin );


/*
 * @brief Toggles all bits of the specified port.
 *
 * @param dio_port: Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 */
void DIO_TogglePortValue( uint8 dio_port );


/*
 * @brief Sets the upper 4 bits of a port with a given nibble value.
 *
 * @param dio_port:     Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param nibble_value: 4-bit value to be placed in the upper nibble (bits 4-7).
 */
void DIO_SetUpperNibble( uint8 dio_port , uint8 nibble_value );


/*
 * @brief Sets the lower 4 bits of a port with a given nibble value.
 *
 * @param dio_port:     Port identifier [ DIO_PORTA , DIO_PORTB , DIO_PORTC , DIO_PORTD ].
 * @param nibble_value: 4-bit value to be placed in the lower nibble (bits 0-3).
 */
void DIO_SetLowerNibble( uint8 dio_port , uint8 nibble_value );


#endif

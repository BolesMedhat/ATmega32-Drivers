/****************************************************************************
 * @file    DIO_DIF.h
 * @author  Boles Medhat
 * @brief   DIO Driver Definitions Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit-level
 * control values for the Digital Input/Output (DIO) functionality of the
 * ATmega32 microcontroller. It includes register mappings for the data direction,
 * data output, and input registers of each port (PORTA to PORTD), as well as
 * symbolic definitions for common pin configurations and operations.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef DIO_DIF_H_
#define DIO_DIF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*Direction Registers*/
#define DDRA								*((volatile uint8 *)0x3A)	/*Port A Data Direction Register*/
#define DDRB								*((volatile uint8 *)0x37)	/*Port B Data Direction Register*/
#define DDRC								*((volatile uint8 *)0x34)	/*Port C Data Direction Register*/
#define DDRD								*((volatile uint8 *)0x31)	/*Port D Data Direction Register*/

/*Data Registers*/
#define PORTA								*((volatile uint8 *)0x3B)	/*Port A Data Direction Register*/
#define PORTB								*((volatile uint8 *)0x38)	/*Port B Data Direction Register*/
#define PORTC								*((volatile uint8 *)0x35)	/*Port C Data Direction Register*/
#define PORTD								*((volatile uint8 *)0x32)	/*Port D Data Direction Register*/

/*Input Registers*/
#define PINA								*((volatile uint8 *)0x39)	/*Port A Input Pins Address Register*/
#define PINB								*((volatile uint8 *)0x36)	/*Port B Input Pins Address Register*/
#define PINC								*((volatile uint8 *)0x33)	/*Port C Input Pins Address Register*/
#define PIND								*((volatile uint8 *)0x30)	/*Port D Input Pins Address Register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*DIO PORTs*/
#define DIO_PORTA							0		/*PORTA for functions parameters*/
#define DIO_PORTB							1		/*PORTB for functions parameters*/
#define DIO_PORTC							2		/*PORTC for functions parameters*/
#define DIO_PORTD							3		/*PORTD for functions parameters*/


/*DIO PINs*/
#define DIO_PIN0							0		/*PIN0 for functions parameters*/
#define DIO_PIN1							1		/*PIN1 for functions parameters*/
#define DIO_PIN2							2		/*PIN2 for functions parameters*/
#define DIO_PIN3							3		/*PIN3 for functions parameters*/
#define DIO_PIN4							4		/*PIN4 for functions parameters*/
#define DIO_PIN5							5		/*PIN5 for functions parameters*/
#define DIO_PIN6							6		/*PIN6 for functions parameters*/
#define DIO_PIN7							7		/*PIN7 for functions parameters*/


/*PIN values*/
#define LOW									0		/*Low  value (set Pin by 0)*/
#define HIGH								1		/*High value (set Pin by 1)*/


/*PORT values*/
#define LOW_PORT							0		/*Low  value (set Port by 0x00)*/
#define HIGH_PORT							0xFF	/*Port value (set Port by 0xFF)*/


/*PINs Direction*/
#define INPUT								0		/*Set Pin Direction as Input*/
#define OUTPUT								1		/*Set Pin Direction as Output*/
#define INPUT_PULLUP						2		/*Set Pin Direction as Input Pull-Up*/


/*PORTs Direction*/
#define INPUT_PORT							0		/*Set PORT Direction as Input*/
#define OUTPUT_PORT							0xFF	/*Set PORT Direction as Output*/


/*PORTA PINs*/
#define PINA0								0		/*PIN0 in port A for functions parameters*/
#define PINA1								1		/*PIN1 in port A for functions parameters*/
#define PINA2								2		/*PIN2 in port A for functions parameters*/
#define PINA3								3		/*PIN3 in port A for functions parameters*/
#define PINA4								4		/*PIN4 in port A for functions parameters*/
#define PINA5								5		/*PIN5 in port A for functions parameters*/
#define PINA6								6		/*PIN6 in port A for functions parameters*/
#define PINA7								7		/*PIN7 in port A for functions parameters*/

#define PA0									0		/*PIN0 in port A for functions parameters*/
#define PA1									1		/*PIN1 in port A for functions parameters*/
#define PA2									2		/*PIN2 in port A for functions parameters*/
#define PA3									3		/*PIN3 in port A for functions parameters*/
#define PA4									4		/*PIN4 in port A for functions parameters*/
#define PA5									5		/*PIN5 in port A for functions parameters*/
#define PA6									6		/*PIN6 in port A for functions parameters*/
#define PA7									7		/*PIN7 in port A for functions parameters*/


/*PORTB PINs*/
#define PINB0								0		/*PIN0 in port B for functions parameters*/
#define PINB1								1		/*PIN1 in port B for functions parameters*/
#define PINB2								2		/*PIN2 in port B for functions parameters*/
#define PINB3								3		/*PIN3 in port B for functions parameters*/
#define PINB4								4		/*PIN4 in port B for functions parameters*/
#define PINB5								5		/*PIN5 in port B for functions parameters*/
#define PINB6								6		/*PIN6 in port B for functions parameters*/
#define PINB7								7		/*PIN7 in port B for functions parameters*/

#define PB0									0		/*PIN0 in port B for functions parameters*/
#define PB1									1		/*PIN1 in port B for functions parameters*/
#define PB2									2		/*PIN2 in port B for functions parameters*/
#define PB3									3		/*PIN3 in port B for functions parameters*/
#define PB4									4		/*PIN4 in port B for functions parameters*/
#define PB5									5		/*PIN5 in port B for functions parameters*/
#define PB6									6		/*PIN6 in port B for functions parameters*/
#define PB7									7		/*PIN7 in port B for functions parameters*/


/*PORTC PINs*/
#define PINC0								0		/*PIN0 in port C for functions parameters*/
#define PINC1								1		/*PIN1 in port C for functions parameters*/
#define PINC2								2		/*PIN2 in port C for functions parameters*/
#define PINC3								3		/*PIN3 in port C for functions parameters*/
#define PINC4								4		/*PIN4 in port C for functions parameters*/
#define PINC5								5		/*PIN5 in port C for functions parameters*/
#define PINC6								6		/*PIN6 in port C for functions parameters*/
#define PINC7								7		/*PIN7 in port C for functions parameters*/

#define PC0									0		/*PIN0 in port C for functions parameters*/
#define PC1									1		/*PIN1 in port C for functions parameters*/
#define PC2									2		/*PIN2 in port C for functions parameters*/
#define PC3									3		/*PIN3 in port C for functions parameters*/
#define PC4									4		/*PIN4 in port C for functions parameters*/
#define PC5									5		/*PIN5 in port C for functions parameters*/
#define PC6									6		/*PIN6 in port C for functions parameters*/
#define PC7									7		/*PIN7 in port C for functions parameters*/


/*PORTD PINs*/
#define PIND0								0		/*PIN0 in port D for functions parameters*/
#define PIND1								1		/*PIN1 in port D for functions parameters*/
#define PIND2								2		/*PIN2 in port D for functions parameters*/
#define PIND3								3		/*PIN3 in port D for functions parameters*/
#define PIND4								4		/*PIN4 in port D for functions parameters*/
#define PIND5								5		/*PIN5 in port D for functions parameters*/
#define PIND6								6		/*PIN6 in port D for functions parameters*/
#define PIND7								7		/*PIN7 in port D for functions parameters*/

#define PD0									0		/*PIN0 in port D for functions parameters*/
#define PD1									1		/*PIN1 in port D for functions parameters*/
#define PD2									2		/*PIN2 in port D for functions parameters*/
#define PD3									3		/*PIN3 in port D for functions parameters*/
#define PD4									4		/*PIN4 in port D for functions parameters*/
#define PD5									5		/*PIN5 in port D for functions parameters*/
#define PD6									6		/*PIN6 in port D for functions parameters*/
#define PD7									7		/*PIN7 in port D for functions parameters*/
/*_______________________________________________________________________________________________*/


#endif /* DIO_DIF_H_ */

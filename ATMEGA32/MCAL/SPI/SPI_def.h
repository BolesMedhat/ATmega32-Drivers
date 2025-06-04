/******************************************************************************
 * @file    SPI_def.h
 * @author  Boles Medhat
 * @brief   SPI Driver Definitions Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * and mode macros required for configuring and interacting with the SPI
 * module on the ATmega32 microcontroller.
 *
 * These definitions are intended to be used by the `SPI` driver and other components
 * that require interaction with the SPI module.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SPI_DEF_H_
#define SPI_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*---------------------------------------    Registers    ---------------------------------------*/

/*SPI data Register*/
#define SPDR								*((volatile uint8 *)0x2F)	/*SPI Data Register*/

/*SPI Control Registers*/
#define SPCR								*((volatile uint8 *)0x2D)	/*SPI Control Register*/
#define SPSR								*((volatile uint8 *)0x2E)	/*SPI Status Register*/

/*Global Interrupt Register*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/

/*SPI Pins Direction Register*/
#define DDRB								*((volatile uint8 *)0x37)	/*Port B Direction Register (MOSI, MISO, SCK, SS Pins's Port Register)*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*SPCR Register*/
#define SPR0								0	/*SPI Clock Rate Select Bit 0*/
#define SPR1								1	/*SPI Clock Rate Select Bit 1*/
#define CPHA								2	/*Clock Phase*/
#define CPOL								3	/*Clock Polarity*/
#define MSTR								4	/*Master/Slave Select*/
#define DORD								5	/*Data Order*/
#define SPE									6	/*SPI Enable*/
#define SPIE								7	/*SPI Interrupt Enable*/

/*SPSR Register*/
#define SPI2X								0	/*Double SPI Speed Bit*/
#define WCOL								6	/*Write COLlision Flag*/
#define SPIF								7	/*SPI Interrupt Flag*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/

/*DDRB and PORTB Register*/
#define SS_PIN								4	/*SPI Slave Select Input			pin from pinout*/
#define MOSI_PIN							5	/*SPI Bus Master Output/Slave Input pin from pinout*/
#define MISO_PIN							6	/*SPI Bus Master Input/Slave Output pin from pinout*/
#define SCK_PIN								7	/*SPI Bus Serial Clock				pin from pinout*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define SPI_WAIT_FOREVER					0	/*finishing the transfer is the only thing that ends the waiting*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*SPI Interrupt Status*/
#define SPI_INT_DISABLE						0	/*SPI Interrupt Disable*/
#define SPI_INT_ENABLE						1	/*SPI Interrupt Enable*/

/*SPI Data Order*/
#define SPI_MSB_FIRST						0	/*the MSB of the data word is transmitted first*/
#define SPI_LSB_FIRST						1	/*the LSB of the data word is transmitted first*/

/*SPI Mode*/
#define SPI_SLAVE							0	/*configured as a Slave*/
#define SPI_MASTER							1	/*configured as a Master*/

/*SPI Clock Polarity*/
#define SPI_LEADING_RISING					0	/*SCK is low when idle*/
#define SPI_LEADING_FALLING					1	/*SCK is high  when idle*/

/*SPI Clock Phase*/
#define SPI_LEADING_SAMPLE					0	/*data is sample on the leading(first) and Setup  on the trailing (last) edge of SCK*/
#define SPI_LEADING_SETUP					1	/*data is Setup  on the leading(first) and sample on the trailing (last) edge of SCK*/

/*SPI Clock Rate*/
#define SPI_FREQ_DIVIDED_BY_2				4	/*SPI Frequency = F_CPU / 2	  (CLK/2)*/
#define SPI_FREQ_DIVIDED_BY_4				0	/*SPI Frequency = F_CPU / 4	  (CLK/4)*/
#define SPI_FREQ_DIVIDED_BY_8				5	/*SPI Frequency = F_CPU / 8	  (CLK/8)*/
#define SPI_FREQ_DIVIDED_BY_16				1	/*SPI Frequency = F_CPU / 16  (CLK/16)*/
#define SPI_FREQ_DIVIDED_BY_32				6	/*SPI Frequency = F_CPU / 32  (CLK/32)*/
#define SPI_FREQ_DIVIDED_BY_64				2	/*SPI Frequency = F_CPU / 64  (CLK/64)*/
#define SPI_FREQ_DIVIDED_BY_128				3	/*SPI Frequency = F_CPU / 128 (CLK/128)*/
/*_______________________________________________________________________________________________*/


#endif /* SPI_DEF_H_ */

/******************************************************************************
 * @file    UART_def.h
 * @author  Boles Medhat
 * @brief   UART Driver Definitions Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-1]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains all the necessary register definitions, bit positions,
 * and mode macros required for configuring and interacting with the UART
 * module on the ATmega32 microcontroller.
 *
 * These definitions are intended to be used by the `UART` driver and other components
 * that require interaction with the UART module.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef UART_DEF_H_
#define UART_DEF_H_

#include "../../LIB/STD_TYPES.h"

/*---------------------------------------    Registers    ---------------------------------------*/

/*UART Register*/
#define UDR									*((volatile uint8 *)0x2C)	/*USART I/O Data Register*/

/*UART Control Register*/
#define UCSRA								*((volatile uint8 *)0x2B)	/*USART Control and Status Register A*/
#define UCSRB								*((volatile uint8 *)0x2A)	/*USART Control and Status Register B*/
#define UCSRC								*((volatile uint8 *)0x40)	/*USART Control and Status Register C*/
#define UBRRL								*((volatile uint8 *)0x29)	/*USART Baud Rate LOW Register*/
#define UBRRH								*((volatile uint8 *)0x40)	/*USART Baud Rate HIGH Register*/

/*Interrupt Registers*/
#define SREG								*((volatile uint8 *)0x5F)	/*status register*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   BITS    ------------------------------------------*/

/*UCSRA Register*/
#define MPCM								0	/*Multi-processor Communication Mode*/
#define U2X									1	/*Double the USART Transmission Speed*/
#define PE									2	/*Parity Error*/
#define DOR									3	/*Data OverRun*/
#define FE									4	/*Frame Error*/
#define UDRE								5	/*USART Data Register Empty*/
#define TXC									6	/*USART Transmit Complete*/
#define RXC									7	/*USART Receive Complete*/

/*UCSRB Register*/
#define TXB8								0	/*Transmit Data Bit 8*/
#define RXB8								1	/*Receive Data Bit 8*/
#define UCSZ2								2	/*Character Size*/
#define TXEN								3	/*Transmitter Enable*/
#define RXEN								4	/*Receiver Enable*/
#define UDRIE								5	/*USART Data Register Empty Interrupt Enable*/
#define TXCIE								6	/*TX Complete Interrupt Enable*/
#define RXCIE								7	/*RX Complete Interrupt Enable*/

/*UCSRC Register*/
#define UCPOL								0	/*Clock Polarity*/
#define UCSZ0								1	/*Character Size Bit 0*/
#define UCSZ1								2	/*Character Size Bit 1*/
#define USBS								3	/*Stop Bit Select*/
#define UPM0								4	/*Parity Mode Bit 0*/
#define UPM1								5	/*Parity Mode Bit 1*/
#define UMSEL								6	/*USART Mode Select*/
#define URSEL								7	/*Register Select*/

/*SREG Register*/
#define	I									7	/*Global Interrupt Enable*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

#define UART_WAIT_FOREVER					0	/*Max time to waiting for the Send to finish*/ /*Set it by any number (e.g. 100) to wait until counter equal it to end waiting OR Set it by ( UART_WAIT_FOREVER ) to wait until MCU end*/

/*Bit values*/
#define LOW									0	/*Low  value (set Bit by 0)*/
#define HIGH								1	/*High value (set Bit by 1)*/

/*UART Interrupt IDs*/
#define UART_INT_TX_ID						0	/*TX  interrupt ID for functions parameters*/
#define UART_INT_RX_ID						1	/*RX  interrupt ID for functions parameters*/
#define UART_INT_UDR_ID						2	/*UDR interrupt ID for functions parameters*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   modes    -----------------------------------------*/

/*Baud Rate Speed*/
#define UART_BAUD_RATE_2400				2400UL		/*BaudRate = 2400   bps*/
#define UART_BAUD_RATE_4800				4800UL		/*BaudRate = 4800   bps*/
#define UART_BAUD_RATE_9600				9600UL		/*BaudRate = 9600   bps*/
#define UART_BAUD_RATE_14400			14400UL		/*BaudRate = 14400  bps*/
#define UART_BAUD_RATE_19200			19200UL		/*BaudRate = 19200  bps*/
#define UART_BAUD_RATE_28800			28800UL		/*BaudRate = 28800  bps*/
#define UART_BAUD_RATE_38400			38400UL		/*BaudRate = 38400  bps*/
#define UART_BAUD_RATE_57600			57600UL		/*BaudRate = 57600  bps*/
#define UART_BAUD_RATE_76800			76800UL		/*BaudRate = 76800  bps*/
#define UART_BAUD_RATE_115200			115200UL	/*BaudRate = 115200 bps*/
#define UART_BAUD_RATE_230400			230400UL	/*BaudRate = 230400 bps*/

/*UART Double the UART Transmission Speed for ASYNCHRONOUS mode only*/
#define UART_U2X_DISABLE					0	/*U2X mode Disable*/
#define UART_U2X_ENABLE						1	/*U2X mode Enable*/

/*UART Parity Mode*/
#define UART_PARITY_DISABLE					0	/*Parity mode Disabled*/
#define UART_PARITY_EVEN					2	/*Parity mode Enabled, Even Parity*/
#define UART_PARITY_ODD						3	/*Parity mode Enabled, Odd Parity*/

/*UART Stop Bit Mode*/
#define UART_1_STOP_BIT						0	/*1-bit Stop in the frame*/
#define UART_2_STOP_BIT						1	/*2-bit Stop in the frame*/

/*UART Character Size*/
#define UART_DATA_5_BIT_SIZE				0	/*5-bit Data in the frame*/
#define UART_DATA_6_BIT_SIZE				1	/*6-bit Data in the frame*/
#define UART_DATA_7_BIT_SIZE				2	/*7-bit Data in the frame*/
#define UART_DATA_8_BIT_SIZE				3	/*8-bit Data in the frame*/
#define UART_DATA_9_BIT_SIZE				7	/*9-bit Data in the frame*/

/*UART Interrupt Mode*/
#define UART_INT_DISABLE					0	/*UART interrupt disable*/
#define UART_INT_ENABLE						1	/*UART interrupt enable*/

/*UART Mode*/
#define UART_DISABLE						0	/*UART (TX or RX) disable*/
#define UART_ENABLE							1	/*UART (TX or RX) enable*/
/*_______________________________________________________________________________________________*/


#endif /* UART_DEF_H_ */

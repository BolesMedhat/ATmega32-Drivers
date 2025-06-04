/******************************************************************************
 * @file    SPI.c
 * @author  Boles Medhat
 * @brief   SPI Driver Source File - AVR ATmega32
 * @version 1.0
 * @date    [2024-08-04]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file implements the SPI (Serial Peripheral Interface) driver for the
 * ATmega32 microcontroller. The driver supports both master and slave modes,
 * and it allows full-duplex, interrupt-driven communication.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `SPI_config.h` for macro-based configuration.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "SPI.h"

/* Pointer to hold the address of the transmit array */
uint8 * g_SPI_TX_Array = NULL;

/* Pointer to hold the address of the receive array */
uint8 * g_SPI_RX_ArrayPointer = NULL;

/* Variable to hold the size of the transmit and receive array */
uint16 g_SPI_ArraySize;

/* Variable to track the current byte index of the transmit and receive array */
uint16 g_SPI_ArrayIndex = 0;

/* Pointer to the callback function for the SPI ISR */
void (* g_SPI_CallBack)(void)= NULL;





/*
 * @brief Initialize the SPI peripheral based on configuration options.
 *
 * This function configures the SPI as Master or Slave, data order,
 * clock polarity, clock phase, interrupt settings, and clock rate,
 * and sets the appropriate pin directions (MISO, MOSI, SCK, SS) on PORTB.
 * It configures the SPI registers according to the defined macros in `SPI_config.h`.
 *
 * @see `SPI_config.h` for configuration options.
 */
void SPI_Init( void )
{

	/* check the spi mode */
	#if   SPI_MODE == SPI_MASTER

		/* master mode */
		SET_BIT( SPCR , MSTR );


		/* set mosi as an output */
		SET_BIT( DDRB , MOSI_PIN );

		/* set sck as an output */
		SET_BIT( DDRB , SCK_PIN );

		/* set miso as an input */
		CLR_BIT( DDRB , MISO_PIN );

		/* set ss as an output */
		SET_BIT( DDRB , SS_PIN );

	#elif SPI_MODE == SPI_SLAVE

		/* slave mode */
		CLR_BIT( SPCR , MSTR );


		/* set miso as an output */
		SET_BIT( DDRB , MISO_PIN );

		/* set sck as an input */
		CLR_BIT( DDRB , SCK_PIN );

		/* set mosi as an input */
		CLR_BIT( DDRB , MOSI_PIN );

		/* set ss as an input */
		CLR_BIT( DDRB , SS_PIN );

	#else
		/* make an error */
		#error "Wrong \"SPI_MODE\" configuration option"
	#endif


	/* check the data order */
	#if   SPI_DATA_ORDER == SPI_MSB_FIRST

		/* the msb is transmitted first */
		CLR_BIT( SPCR , DORD );

	#elif SPI_DATA_ORDER == SPI_LSB_FIRST

		/* the lsb is transmitted first */
		SET_BIT( SPCR , DORD );

	#else
		/* make an error */
		#error "Wrong \"SPI_DATA_ORDER\" configuration option"
	#endif


	/* check the clock polarity */
	#if   SPI_CLOCK_POLARITY == SPI_LEADING_RISING

		/* sck is low when idle */
		CLR_BIT( SPCR , CPOL );

	#elif SPI_CLOCK_POLARITY == SPI_LEADING_FALLING

		/* sck is high when idle */
		SET_BIT( SPCR , CPOL );

	#else
		/* make an error */
		#error "Wrong \"SPI_CLOCK_POLARITY\" configuration option"
	#endif


	/* check the clock phase */
	#if   SPI_CLOCK_PHASE == SPI_LEADING_SAMPLE

		/* cpha leading edge: sample, trailing edge: setup */
		CLR_BIT( SPCR , CPHA );

	#elif SPI_CLOCK_PHASE == SPI_LEADING_SETUP

		/* cpha leading edge: setup, trailing edge: sample */
		SET_BIT( SPCR , CPHA );

	#else
		/* make an error */
		#error "Wrong \"SPI_CLOCK_PHASE\" configuration option"
	#endif


	/* check the spi interrupt status */
	#if   SPI_INT_STATUS == SPI_INT_DISABLE

		/* disable spi interrupt */
		CLR_BIT( SPCR , SPIE );

	#elif SPI_INT_STATUS == SPI_INT_ENABLE

		/* enable spi interrupt */
		SET_BIT( SPCR , SPIE );

		/* enable global interrupt */
		SET_BIT( SREG , I );

	#else
		/* make an error */
		#error "Wrong \"SPI_INT_STATUS\" configuration option"
	#endif


	/* check the clock rate */
	#if   SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_2

		/* spi frequency = f_cpu / 2 (clk/2) */
		CLR_BIT( SPCR , SPR0 );
		CLR_BIT( SPCR , SPR1 );
		SET_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_4

		/* spi frequency = f_cpu / 4 (clk/4) */
		CLR_BIT( SPCR , SPR0 );
		CLR_BIT( SPCR , SPR1 );
		CLR_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_8

		/* spi frequency = f_cpu / 8 (clk/8) */
		SET_BIT( SPCR , SPR0 );
		CLR_BIT( SPCR , SPR1 );
		SET_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_16

		/* spi frequency = f_cpu / 16 (clk/16) */
		SET_BIT( SPCR , SPR0 );
		CLR_BIT( SPCR , SPR1 );
		CLR_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_32

		/* spi frequency = f_cpu / 32 (clk/32) */
		CLR_BIT( SPCR , SPR0 );
		SET_BIT( SPCR , SPR1 );
		SET_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_64

		/* spi frequency = f_cpu / 64 (clk/64) */
		CLR_BIT( SPCR , SPR0 );
		SET_BIT( SPCR , SPR1 );
		CLR_BIT( SPSR , SPI2X );

	#elif SPI_CLOCK_RATE == SPI_FREQ_DIVIDED_BY_128

		/* spi frequency = f_cpu / 128 (clk/128) */
		SET_BIT( SPCR , SPR0 );
		SET_BIT( SPCR , SPR1 );
		CLR_BIT( SPSR , SPI2X );

	#else
		/* make an error */
		#error "Wrong \"SPI_CLOCK_RATE\" configuration option"
	#endif


	/* enable spi */
	SET_BIT( SPCR , SPE );
}





/*
 * @brief Disable SPI interrupt.
 *
 * This function disables the SPI interrupt by clearing the SPIE bit in the SPCR register.
 */
void SPI_InterruptDisable( void )
{
	CLR_BIT( SPCR , SPIE );
}





/*
 * @brief Enable SPI interrupt.
 *
 * This function enables the SPI interrupt by setting the SPIE bit in the SPCR register.
 */
void SPI_InterruptEnable( void )
{
	SET_BIT( SPCR , SPIE );
}





/*
 * @brief Transmit a single byte over SPI and receive a byte simultaneously.
 *
 * This function sends the specified byte and waits until transmission is complete.
 * If a timeout counter is enabled (SPI_COUNTOUT != SPI_WAIT_FOREVER),
 * the function will return 0xFF if the transfer fails.
 *
 * @param TX_Byte: Byte to send.
 * @return (uint8) Received byte. Returns 0xFF if the transfer times out.
 */
uint8 SPI_transferByte( uint8 TX_Byte )
{

	/* transmit one byte data */
	SPDR = TX_Byte;

	#if SPI_COUNTOUT != SPI_WAIT_FOREVER

		/* counter that count until it equals spi_countout */
		/* to end the waiting if transferring does not end */
		uint16 SPI_counter = 0 ;

		/* waiting until the sending is complete or until waiting time is end */
		while ((IS_BIT_CLR( SPSR , SPIF )) && (SPI_counter < SPI_COUNTOUT))
		{
			/* counter up */
			SPI_counter++ ;
		}

		/* check that the transferring is complete correctly */
		if (SPI_counter < SPI_COUNTOUT)
		{
			/* receive the data */
			return SPDR;
		}
		else
		{
			/* receive 0 */
			return 0xFF;
		}

	#else
		/* waiting until the transferring is complete */
		while (IS_BIT_CLR( SPSR , SPIF ));

		/* receive the data */
		return SPDR;
	#endif

}





/*
 * @brief Transmit a single byte over SPI.
 *
 * This function only sends the specified byte and waits until transmission is complete (no return value).
 *
 * @param TX_Byte: Byte to transmit.
 */
void SPI_transmitByte( uint8 TX_Byte )
{
	SPI_transferByte( TX_Byte );
}





/*
 * @brief Receive a single byte over SPI.
 *
 * This function receiving data and sends a default transmit value.
 * If a timeout counter is enabled (SPI_COUNTOUT != SPI_WAIT_FOREVER),
 * the function will return 0xFF if the transfer fails.
 *
 * @return (uint8) Received byte. Returns 0xFF if the transfer times out.
 */
uint8 SPI_ReceiveByte( void )
{
	return SPI_transferByte( SPI_DEFAULT_TRANSMIT_DATA );
}





/*
 * @brief Transmit and receive arrays of bytes simultaneously over SPI.
 *
 * This function transmits each byte from the `TX_Array`
 * and stores the received bytes in the `RX_Array` (Full-duplex communication).
 *
 * @param TX_Array:	Pointer to the array of data to transmit.
 * @param RX_Array:	Pointer to the array to store received data.
 * @param ArraySize:			Number of bytes to transmit/receive.
 */
void SPI_transferArray( const uint8 * TX_Array , uint8 * RX_Array , uint16 ArraySize )
{
	/* Loop on the array until it end */
	for(uint16 index = 0 ; index < ArraySize ; index++)
	{
		/* Transmit and receive one byte data */
		RX_Array[index] = SPI_transferByte( TX_Array[index] );
	}
}





/*
 * @brief Transmit arrays of bytes over SPI.
 *
 * This function transmits each byte from the `TX_Array`.
 *
 * @param TX_Array:	Pointer to the array of data to transmit.
 * @param ArraySize:			Number of bytes to transmit.
 */
void SPI_transmitArray( const uint8 * TX_Array , uint16 ArraySize )
{
	/* Loop on the array until it end */
	for(uint16 index = 0 ; index < ArraySize ; index++)
	{
		/* Transmit one byte data */
		SPI_transferByte( TX_Array[index] );
	}
}





/*
 * @brief Receive arrays of bytes over SPI.
 *
 * This function Stores the received bytes in the `RX_Array`
 * and sends default values.
 *
 * @param RX_Array:	Pointer to the array to store received data.
 * @param ArraySize:			Number of bytes to receive.
 */
void SPI_ReceiveArray( uint8 * RX_Array , uint16 ArraySize )
{
	/* Loop on the array until it end */
	for(uint16 index = 0 ; index < ArraySize ; index++)
	{
		/* Receive one byte data */
		RX_Array[index] = SPI_transferByte( SPI_DEFAULT_TRANSMIT_DATA );
	}
}





/*
 * @brief Set the SPI callback function and start interrupt-driven transfer.
 *
 * Initializes internal pointers and index counters to support interrupt-driven
 * SPI data transfer. The user-provided callback function will be called upon completion.
 *
 *@example SPI_SetCallback( SPI_Interrupt_Function , TransmitArray , ReceiveArray , ArraySize );
 *
 * @param CopyFuncPtr:			Pointer to the callback function. The function should have a
 * 								void return type and no parameters.
 * @param TX_Array: Pointer to data array to transmit (NULL if not used).
 * @param RX_Array:	Pointer to data array to store received data (NULL if not used).
 * @param ArraySize:			Size of the data arrays.
 */
void SPI_SetCallback( void (*CopyFuncPtr)(void) , uint8 * TX_Array , uint8 * RX_Array , uint16 ArraySize )
{

	/* Copy the data */
	g_SPI_CallBack		= CopyFuncPtr;
	g_SPI_TX_Array		= TX_Array;
	g_SPI_RX_ArrayPointer = RX_Array;
	g_SPI_ArraySize		= ArraySize;

	/* Set index to first element */
	g_SPI_ArrayIndex = 0;

	/* Check if the array is valid */
	if(g_SPI_TX_Array != NULL)
	{
		/*Transmit first data */
		SPDR = g_SPI_TX_Array[ g_SPI_ArrayIndex ] ;
	}

}





/*
 * @brief ISR for the SPI interrupt.
 *
 * This ISR is triggered when a SPI interrupt occurs.
 * It calls the user-defined callback function set by the SPI_SetCallback function.
 *
 * @see SPI_SetCallback for setting the callback function.
 */
void __vector_12 (void)		__attribute__ ((signal)) ;
void __vector_12 (void)
{

	/* Check if the array is valid */
	if( g_SPI_RX_ArrayPointer != NULL )
	{
		/* Receive data */
		g_SPI_RX_ArrayPointer[ g_SPI_ArrayIndex ] = SPDR ;
	}


	/* Increment data index of the array */
	g_SPI_ArrayIndex++ ;


	/* Check if the array complete */
	if (g_SPI_ArrayIndex >= g_SPI_ArraySize)
	{
		/* the array is complete */

		/* Ready for new array */
		g_SPI_ArrayIndex = 0;

		/* Check that the pointer is Vvlid */
		if( g_SPI_CallBack != NULL )
		{
			/* Call The pointer to function */
			g_SPI_CallBack() ;
		}

	}
	else
	{
		/* the array is not complete */

		/* Check if the array is valid */
		if(g_SPI_TX_Array != NULL)
		{
			/* Transmit next data */
			SPDR = g_SPI_TX_Array[ g_SPI_ArrayIndex ];
		}
	}

}


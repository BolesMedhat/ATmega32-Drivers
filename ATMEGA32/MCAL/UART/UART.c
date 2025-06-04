/******************************************************************************
 * @file    UART.c
 * @author  Boles Medhat
 * @brief   UART Driver Source File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-1]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for the Universal Asynchronous
 * Receiver Transmitter (UART) module in ATmega32 microcontroller. It supports
 * configurable baud rate, frame format (data bits, stop bits, parity), polling
 * and interrupt-based communication, and includes timeout mechanisms and
 * callback function registration.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `UART_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/



#include "UART.h"

/* Pointer to hold the address of the transmit array */
uint8 * g_UART_TX_Array = NULL;

/* Pointer to hold the address of the receive array */
uint8 * g_UART_RX_Array = NULL;

/* Variable to hold the size of the transmit array */
uint16 g_UART_TX_ArraySize;

/* Variable to hold the size of the receive array */
uint16 g_UART_RX_ArraySize;

/* Variable to track the current byte index of the transmit array */
uint16 g_UART_TX_Index = 0;

/* Variable to track the current byte index of the receive array */
uint16 g_UART_RX_Index = 0;

/* variable to Stop Byte of the RX interrupt */
uint8 g_UART_Stop_Byte;

/* Pointer to the callback function for the UART TX ISR */
void (*g_UART_TXCallBack)(void)= NULL;

/* Pointer to the callback function for the UART RX ISR */
void (*g_UART_RXCallBack)(void)= NULL;





/*
 * @brief Initialize the UART peripheral based on configuration options.
 *
 * This function configures the UART module based on the defined macros
 * in the configuration file. It sets the baud rate, parity, stop bits,
 * data size, transmission speed mode, and enables/disables receiver,
 * transmitter, and interrupts as required.
 * It configures the UART registers according to the defined macros in `UART_config.h`.
 *
 * @see `UART_config.h` for configuration options.
 */
void UART_Init( void )
{

	/*Calculate The UBRR Registers */
	#if UART_U2X_MODE == UART_U2X_DISABLE

		uint16 UBRR = (uint16)((uint16)(F_CPU/(UART_BAUD_RATE*16.0) + 0.5) - 1);

	#elif UART_U2X_MODE == UART_U2X_ENABLE

		uint16 UBRR = (uint16)((uint16)(F_CPU/(UART_BAUD_RATE*8.0) + 0.5) - 1);

	#endif

	/* Set The UBRR Register */
	UBRRH = (uint8)(UBRR >> 8);
	UBRRL = (uint8)(UBRR);


	/* Clear Error Flag Bits */
	UCSRA &= 0XE3;


	/* Check Double the UART Transmission Speed mode */
	#if UART_U2X_MODE == UART_U2X_DISABLE

		/* Disable Double Speed mode */
		CLR_BIT( UCSRA , U2X );

	#elif UART_U2X_MODE == UART_U2X_ENABLE

		/* Enable Double Speed mode */
		SET_BIT( UCSRA , U2X );

	#else
		/* Make an Error */
		#error "Wrong \"UART_U2X_MODE\" configuration option"
	#endif


	/* Declaration Temporarily Variable UCSRC_REG */
	uint8 UCSRC_REG = 0X80;


	/* Set Asynchronous mode (UART) */
	CLR_BIT( UCSRC_REG , UMSEL ) ;


	/* Check Parity mode */
	#if UART_PARITY_MODE == UART_Parity_Disable

		/* Disabled Parity */
		CLR_BIT( UCSRC_REG , UPM1 ); CLR_BIT( UCSRC_REG , UPM0 );

	#elif UART_PARITY_MODE == UART_PARITY_EVEN

		/* Enabled, Even Parity */
		SET_BIT( UCSRC_REG , UPM1 ); CLR_BIT( UCSRC_REG , UPM0 );

	#elif UART_PARITY_MODE == UART_PARITY_ODD

		/* Enabled, Odd Parity */
		SET_BIT( UCSRC_REG , UPM1 ); SET_BIT( UCSRC_REG , UPM0 );

	#else
		/* Make an Error */
		#error "Wrong \"UART_PARITY_MODE\" configuration option"
	#endif

	/* Check Stop Bit Mode */
	#if UART_STOP_BIT == UART_1_STOP_BIT

		/* 1 Stop BIT */
		CLR_BIT( UCSRC_REG , USBS );

	#elif UART_STOP_BIT == UART_2_STOP_BIT

		/* 2 Stop BITs */
		SET_BIT( UCSRC_REG , USBS );

	#else
		/* Make an Error */
		#error "Wrong \"UART_STOP_BIT_Mode\" configuration option"
	#endif

	/* Check Data Size */
	#if UART_DATA_SIZE == UART_DATA_5_BIT_SIZE

		/* 5 BITs Data Size */
		CLR_BIT( UCSRC_REG , UCSZ0 );
		CLR_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_DATA_SIZE == UART_DATA_6_BIT_SIZE

		/* 6 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		CLR_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_DATA_SIZE == UART_DATA_7_BIT_SIZE

		/* 7 BITs Data Size */
		CLR_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_DATA_SIZE == UART_DATA_8_BIT_SIZE

		/* 8 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		CLR_BIT( UCSRB , UCSZ2 );

	#elif UART_DATA_SIZE == UART_DATA_9_BIT_SIZE

		/* 9 BITs Data Size */
		SET_BIT( UCSRC_REG , UCSZ0 );
		SET_BIT( UCSRC_REG , UCSZ1 );
		SET_BIT( UCSRB , UCSZ2 );

	#else
		/* Make an Error */
		#error "Wrong \"UART_DATA_SIZE\" configuration option"
	#endif


	/* Set UCSRC */
	UCSRC = UCSRC_REG;


	/* Check if the Receive is Enable */
	#if UART_RECEIVER_ENABLE == UART_DISABLE

		/* Disable the Receive */
		CLR_BIT( UCSRB , RXEN );

	#elif UART_RECEIVER_ENABLE == UART_ENABLE

		/* Enable the Receive */
		SET_BIT( UCSRB , RXEN );

	#else
		/* Make an Error */
		#error "Wrong \"UART_RECEIVER_ENABLE\" configuration option"
	#endif

	/*Check if the Transmitter is Enable*/
	#if UART_TRANSMITTER_ENABLE == UART_DISABLE

		/* Disable the Transmitter */
		CLR_BIT( UCSRB , TXEN );

	#elif UART_TRANSMITTER_ENABLE == UART_ENABLE

		/* Enable the Transmitter */
		SET_BIT( UCSRB , TXEN );

	#else
		/* Make an Error */
		#error "Wrong \"UART_TRANSMITTER_ENABLE\" configuration option"
	#endif


	/* Check if RX Complete Interrupt is Enable */
	#if UART_RX_INTERRUPT == UART_INT_DISABLE

		/* Disable RX Complete Interrupt */
		CLR_BIT( UCSRB , RXCIE );

	#elif UART_RX_INTERRUPT == UART_INT_ENABLE

		/* Enable RX Complete Interrupt */
		SET_BIT( UCSRB , RXCIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_RX_INTERRUPT\" configuration option"
	#endif


	/* Check if TX Complete Interrupt is Enable */
	#if UART_TX_INTERRUPT == UART_INT_DISABLE

		/* Disable TX Complete Interrupt */
		CLR_BIT( UCSRB , TXCIE );

	#elif UART_TX_INTERRUPT == UART_INT_ENABLE

		/* Enable TX Complete Interrupt */
		SET_BIT( UCSRB , TXCIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_TX_INTERRUPT\" configuration option"
	#endif


	/* Check if UDR Empty Interrupt is Enable */
	#if UART_UDR_INTERRUPT == UART_INT_DISABLE

		/* Disable UDR Empty Interrupt */
		CLR_BIT( UCSRB , UDRIE );

	#elif UART_UDR_INTERRUPT == UART_INT_ENABLE



		/* Enable UDR Empty Interrupt */
		SET_BIT( UCSRB , UDRIE );

		/* Enable Global Interrupt */
		SET_BIT( SREG , I );

	#else
		/* Make an Error */
		#error "Wrong \"UART_UDR_INTERRUPT\" configuration option"
	#endif


}





/*
 * @brief Disable the specified UART interrupt.
 *
 * This function disables a specific UART interrupt based on the provided ID.
 *
 * @param interrupt_id: Interrupt ID to disable. Options:
 *        - UART_INT_TX_ID: TX Complete Interrupt
 *        - UART_INT_RX_ID: RX Complete Interrupt
 *        - UART_INT_UDR_ID: UDR Empty Interrupt
 */
void UART_InterruptDisable( uint8 interrupt_id )
{

	switch ( interrupt_id )
	{
		/* Disable TX Complete Interrupt */
		case UART_INT_TX_ID:  CLR_BIT( UCSRB , TXCIE ); break;

		/* Disable RX Complete Interrupt */
		case UART_INT_RX_ID:  CLR_BIT( UCSRB , RXCIE ); break;

		/* Disable UDR Empty Interrupt */
		case UART_INT_UDR_ID: CLR_BIT( UCSRB , UDRIE ); break;
	}

}





/**
 * @brief Enable the specified UART interrupt.
 *
 * This function enables a specific UART interrupt based on the provided ID.
 *
 * @param interrupt_id: Interrupt ID to enable. Options:
 *        - UART_INT_TX_ID: TX Complete Interrupt
 *        - UART_INT_RX_ID: RX Complete Interrupt
 *        - UART_INT_UDR_ID: UDR Empty Interrupt
 */
void UART_InterruptEnable( uint8 interrupt_id )
{

	switch ( interrupt_id )
	{
		/* Enable TX Complete Interrupt */
		case UART_INT_TX_ID:  SET_BIT( UCSRB , TXCIE ); break;

		/* Enable RX Complete Interrupt */
		case UART_INT_RX_ID:  SET_BIT( UCSRB , RXCIE ); break;

		/* Enable UDR Empty Interrupt */
		case UART_INT_UDR_ID: SET_BIT( UCSRB , UDRIE ); break;
	}
}





/*
 * @brief Transmit a single byte over UART.
 *
 * This function waits for the UART data register to be ready and then sends
 * the given byte. If timeout is configured, it waits up
 * to the timeout duration before aborting the transmission.
 *
 * @param byte: The byte to be transmitted.
 */
void UART_WriteByte( uint8 byte )
{

	#if UART_COUNTOUT != UART_WAIT_FOREVER

		/* Counter that Count until it Equals UART_COUNTOUT */
		/* to end the Waiting if Sending does not End */
		uint16 UART_counter = 0 ;

		/* Waiting until the Sending is Complete or until Waiting Time is End */
		while ((IS_BIT_CLR( UCSRA , UDRE )) && (UART_counter < UART_COUNTOUT))
		{
			/* Counter UP */
			UART_counter++ ;
		}

		/* Check that the Sending is Complete Correctly */
		if (UART_counter < UART_COUNTOUT)
		{
			/* Send the Byte */
			UDR = byte ;
		}

	#else
		/* Waiting until the Sending is Complete */
		while (IS_BIT_CLR( UCSRA , UDRE ));

		/* Send the Byte */
		UDR = byte ;
	#endif

}





/*
 * @brief Transmit arrays of bytes over UART.
 *
 * This function transmits each byte from the `TX_Array`.
 *
 * @param TX_Array:	 Pointer to the array of data to transmit.
 * @param ArraySize: Number of bytes to write.
 */
void UART_WriteArray( const uint8 * TX_Array , uint16 ArraySize )
{

	/* Loop on the Array Until it End */
	for( uint16 index = 0 ; index < ArraySize ; index++ )
	{
		/* Send One Byte */
		UART_WriteByte( TX_Array[ index ] ) ;
	}
}





/*
 * @brief Transmit a null-terminated string over UART.
 *
 * Sends each character in the provided string one by one
 * until the null terminator '\0' is encountered. Also sends the
 * null terminator to indicate the end of the string.
 *
 * @param TX_String: Pointer to the string to be sent.
 */
void UART_WriteString( const char * TX_String )
{

	/* Loop on the String Until it End */
	for(uint8 index = 0 ; TX_String[ index ] != '\0' ; index++)
	{
		/* Send One Byte */
		UART_WriteByte( TX_String[ index ] ) ;
	}
	/* Send '\0' Byte as End of the String */
	UART_WriteByte( '\0' );

}





/*
 * @brief Send an integer number over UART.
 *
 * This function converts the given integer into a string and sends it
 * using the UART_SendString function.
 *
 * @param number: The integer number to send.
 */
void UART_WriteNumber( sint32 number )
{

	/* Store the integer number to arr & 10 is for decimal numbering system*/
	char arr[12];
	DC_itoa(number,arr,10);

   /* Write the String over UART */
   UART_WriteString( arr );
}





/*
 * @brief receives one byte from the UART.
 *
 * This function waits for a byte to be received through UART. If the wait time exceeds
 * the `UART_COUNTOUT` value (when defined), it returns a timeout character `UART_TIMEOUT_BYTE`.
 * If `UART_COUNTOUT` is set to `UART_WAIT_FOREVER`, it waits indefinitely.
 *
 * @return (uint8) Received byte, or `UART_TIMEOUT_BYTE` if no data received within timeout period.
 */
uint8 UART_ReadByte( void )
{

	/* Check if there is a limit for Waiting */
	#if UART_COUNTOUT != UART_WAIT_FOREVER

		/* Counter that Count until it Equals UART_COUNTOUT */
		/* to end the Waiting if Nothing Send */
		uint16 UART_counter = 0;

		/* Waiting until the Reading is Complete or until Waiting Time is End */
		while ((IS_BIT_CLR( UCSRA , RXC )) && (UART_counter < UART_COUNTOUT))
		{
			/* Counter UP */
			UART_counter++;
		}

		/* Check that the Reading is Complete Correctly */
		if (UART_counter < UART_COUNTOUT)
		{
			/* Read the Byte */
			return UDR;
		}
		else
		{
			/* Read Timeout value */
			return UART_TIMEOUT_BYTE;
		}

	#else

		/* Waiting until the Reading is Complete */
		while (IS_BIT_CLR( UCSRA , RXC ));

		/* Send the Byte */
		return UDR;

	#endif

}





/*
 * @brief receive arrays of bytes from the UART.
 *
 * This function receives each byte and stores them in the `RX_String`.
 *
 * @param RX_Array:  Pointer to the buffer where the received string is stored.
 * @param ArraySize: Number of bytes to read.
 */
void UART_ReadArray( uint8 * RX_Array , uint16 ArraySize )
{

	/* Loop on the Array Until it End */
	for( uint16 index = 0 ; index < ArraySize ; index++ )
	{
		/* Read One Character */
		RX_Array[ index ] = UART_ReadByte();
	}
}





/*
 * @brief receive string from the UART until a null terminator is received.
 *
 * This function receives characters and stores them in the provided buffer
 * until the received byte is a null terminator `\0`.
 *
 * @param String_pointer: Pointer to the buffer where the received string is stored.
 */
void UART_ReadString( char * RX_String )
{

	/* declaration variable for Byte Index */
	uint16 index = 0;

	/* Loop on the String Until Get the Stop Byte or the NULL Character '\0' */
	do
	{
		/* Receive and Save the Byte in the String */
		RX_String[index] = UART_ReadByte();

		/* Check if this Byte is the NULL Character '\0' */
		if( RX_String[index] == '\0' )
		{
			/* End the Loop */
			break;
		}
		/* Go to the Next Index in the String */
		index++;

	}while(1);
}





/*
 * @brief receive string from the UART until a specific stop byte or null terminator is received.
 *
 * This function keeps receiving characters from UART and storing them in the provided buffer
 * until it encounters the specified `stop_Byte` or a null terminator `\0`.
 *
 * @param RX_String: Pointer to the buffer where the received string is stored.
 * @param Stop_Byte: character to stop reading when encountered.
 */
void UART_ReadStringUntil( char * RX_String , uint8 Stop_Byte )
{

	/* declaration variable for Byte Index */
	uint16 index = 0;

	/* Loop on the String Until Get the Stop Byte or the NULL Character '\0' */
	do
	{
		/* Receive and Save the Byte in the String */
		RX_String[index] = UART_ReadByte();

		/* Check if this Byte is the Stop Byte */
		if( RX_String[index] == Stop_Byte )
		{
			/* Read '\0' Character as End of the String */
			RX_String[ index + 1 ] = '\0';

			/* End the Loop */
			break;
		}
		/* Check if this Byte is the NULL Character '\0' */
		else if( RX_String[index] == '\0' )
		{
			/* End the Loop */
			break;
		}
		/* Go to the Next Index in the String */
		index++;

	}while(1);
}





/*
 * @brief Checks if data is available to read from UART.
 *
 * This function checks if there data received and ready to read.
 *
 * @return (uint8) 1 if data is available, 0 otherwise.
 */
uint8 UART_IsAvailableToRead( void )
{
	return GET_BIT( UCSRA,RXC );
}





/*
 * @brief Checks UART status flags for errors.
 *
 * This function returns the bits related to errors (Frame Error, Data Overrun, Parity Error)
 * from the UCSRA register.
 *
 * @return (uint8) Bitmask of error flags from UCSRA (bits 4, 3, 2).
 */
uint8 UART_CheckErrors( void )
{
	return UCSRA & 0x1C ;
}





/*
 * @brief Writes the 9th bit in UART 9-bit mode.
 *
 * This function sets or clears the TXB8 bit in UCSRB register to transmit the 9th data bit.
 * It must be called **before** writing the lower 8 bits to the UDR register.
 *
 * @param NinthBit: The value of the 9th bit to send (use HIGH or LOW).
 */
void UART_WritetheNinthBit( uint8 NinthBit )
{

	/* Check the Direction */
	switch (NinthBit) {

		/* Set Bit by 1 */
		case HIGH:	SET_BIT( UCSRB , TXB8 );	break;

		/* Set Bit by 0 */
		case LOW:	CLR_BIT( UCSRB , TXB8 );	break;
	}
}





/*
 * @brief Reads the 9th bit received in UART 9-bit mode.
 *
 * This function reads the RXB8 bit from the UCSRB register, which represents
 * the 9th bit of received data. It must be called **before** reading the lower 8 bits from UDR.
 *
 * @return (uint8) Value of the received 9th bit (0 or 1).
 */
uint8 UART_ReadtheNinthBit( void )
{
	return GET_BIT( UCSRB , RXB8);
}





/*
 * @brief Sets a callback function for a UART TX (Transmit) interrupt and start sending a data.
 *
 * This function sets a user-defined callback function to be called
 * when the UART transmission is complete.
 * It also loads the first byte to start transmission and initializes internal buffers.
 *
 * @example UART_Set_TX_Callback( & TX_Interrupt_Function , TX_String , TX_StringLength );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 							void return type and no parameters.
 * @param TX_Array:		Pointer to the array to transmit.
 * @param TX_ArraySize: Size of the data array.
 */
void UART_Set_TX_Callback ( void (*CopyFuncPtr)(void) , uint8 * TX_Array , uint16 TX_ArraySize )
{

	/* Copy the Data */
	g_UART_TXCallBack	  = CopyFuncPtr;
	g_UART_TX_Array	  = TX_Array;
	g_UART_TX_ArraySize = TX_ArraySize;


	/*Set Index to First Element*/
	g_UART_TX_Index = 0 ;

	/* Check that the Array Pointer is Valid */
	if ( TX_Array != NULL )
	{
		/*Send First Byte */
		UART_WriteByte(g_UART_TX_Array[ g_UART_TX_Index ]);

	}
}





/*
 * @brief Sets a callback function for a UART RX (Receive) interrupt and start sending a data.
 *
 * This function sets a user-defined callback function to be called
 * when the UART reception is complete (by size) or a stop byte is received.
 * It also stores a buffer to hold received data and store the stop byte that terminates reception.
 *
 * @example UART_Set_RX_Callback( & RX_Interrupt_Function , RX_String , 99999 , '\0' );
 *
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 							void return type and no parameters.
 * @param RX_Array    : Pointer to the buffer where received data will be stored.
 * @param RX_ArraySize: Maximum size of the receive buffer.
 * @param Stop_Byte   : Byte that indicates the end of reception.
 */
void UART_Set_RX_Callback ( void (*CopyFuncPtr)(void) , uint8 * RX_Array , uint16 RX_ArraySize , uint8 Stop_Byte )
{

	/* Check that the Array Pointer is Valid */
	if (RX_Array != NULL)
	{
		/* Copy the Data */
		g_UART_RXCallBack	  = CopyFuncPtr;
		g_UART_RX_Array	  = RX_Array;
		g_UART_RX_ArraySize = RX_ArraySize;
		g_UART_Stop_Byte	  = Stop_Byte;

		/* Set Index to First Element */
		g_UART_RX_Index = 0;
	}
}





/*
 * @brief ISR for the UART TX Interrupt.
 *
 * This ISR is triggered when a UART TX interrupt occurs.
 * It calls the user-defined callback function set by the UART_Set_TX_Callback function.
 *
 * @see UART_Set_TX_Callback for setting the callback function.
 */
void __vector_15 (void)		__attribute__ ((signal)) ;
void __vector_15 (void)
{

	/* Check that the Array Pointer is Valid */
	if ( g_UART_TX_Array != NULL )
	{

		/* Increment index of the TX String */
		g_UART_TX_Index++;

		if ( ( g_UART_TX_Array[g_UART_TX_Index] == '\0' ) || ( g_UART_TX_Index >= g_UART_TX_ArraySize ) )
		{
			/* Send the Last Byte */
			UDR = g_UART_TX_Array[ g_UART_TX_Index ] ;

			/* Ready for New String */
			g_UART_TX_Index = 0;

			/* Check that the Pointer is Valid */
			if( g_UART_TXCallBack != NULL )
			{
				/* Call The Pointer to Function */
				g_UART_TXCallBack();
			}

		}
		else
		{
			/* Send next Byte */
			UDR = g_UART_TX_Array[ g_UART_TX_Index ];
		}
	}
}





/*
 * @brief ISR for the UART RX Interrupt.
 *
 * This ISR is triggered when a UART RX interrupt occurs.
 * It calls the user-defined callback function set by the UART_Set_RX_Callback function.
 *
 * @see UART_Set_RX_Callback for setting the callback function.
 */
void __vector_13 (void)		__attribute__ ((signal)) ;
void __vector_13 (void)
{

	/* Check that the Array Pointer is Valid */
	if ( g_UART_RX_Array != NULL )
	{

		uint8 byte;

		/* Receive next Byte */
		byte = UDR ;
		g_UART_RX_Array[ g_UART_RX_Index ] = byte;

		/* Increment index of the RX String */
		g_UART_RX_Index++ ;


		if ( ( g_UART_RX_Index >= g_UART_RX_ArraySize ) || ( byte == g_UART_Stop_Byte ) )
		{

			if( byte == g_UART_Stop_Byte )
			{
				/* Store the Stop Character as End of the String */
				g_UART_RX_Array[ g_UART_RX_Index ] = g_UART_Stop_Byte;
			}


			/* Ready for New String */
			g_UART_RX_Index = 0;

			/* Check that the Pointer is Valid */
			if( g_UART_RXCallBack != NULL )
			{
				/* Call The Pointer to Function */
				g_UART_RXCallBack() ;
			}

		}
	}
}





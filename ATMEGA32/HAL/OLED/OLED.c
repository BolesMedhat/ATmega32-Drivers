/****************************************************************************
 * @file    OLED.c
 * @author  Boles Medhat
 * @brief   OLED Driver Source File
 * @version 1.0
 * @date    [2025-03-06]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This driver provides an abstraction layer for controlling OLED displays
 * based on the SSD1306 controller using I2C communication protocol.
 * It includes initialization, command/data transmission, screen control,
 * and basic character printing functionalities.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 * - Requires `EEPROM_I2C_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "OLED.h"


/* Stores the Current Cursor Position on the OLED Display */
uint8 OLED_CurrentPage = 0 , OLED_CurrentCol = 0;





/*
 * @brief Initializes the OLED display module.
 *
 * This function configures the OLED display by sending initialization commands over I2C.
 */
void OLED_Init( void )
{

	/* Start I2C Communication */
    I2C_Start();

    /* Send OLED Slave Address with Write Instruction */
    I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );


    /* Disable Display (sleep mode) */
    I2C_WriteOLEDCommand( OLED_DISPLAY_OFF );


    /* Set Display Clock Divide Ratio */
    I2C_WriteOLEDCommand( OLED_SET_DISPLAY_CLK_DIV );

    /* Defined Clock Divide Ratio and Clock Frequency Value */
    I2C_WriteOLEDCommand( OLED_CLK_DIV_OSCI_FREQ );


    /* Configure Multiplex Ratio */
    I2C_WriteOLEDCommand( OLED_SET_MULTIPLEX_RATIO );

    /* Defined Multiplex Ratio Value */
    I2C_WriteOLEDCommand( OLED_MUX_VALUE );


    /* Set Display Offset */
    I2C_WriteOLEDCommand( OLED_SET_DISPLAY_OFFSET );

    /* Defined Display Row Offset */
    I2C_WriteOLEDCommand( OLED_ROWS_OFFSET );


    /* Set Defined Display Start Line */
    I2C_WriteOLEDCommand( OLED_DISPLAY_START_LINE | ( OLED_START_ROW_OFFSET & OLED_START_ROW_OFFSET_msk ) );


    /* Configure Charge Pump Mode */
    I2C_WriteOLEDCommand( OLED_CHARGE_PUMP );

    /* Enable Charge Pump */
    I2C_WriteOLEDCommand( OLED_CHARGE_PUMP_ENABLE );


    /* Configure Memory Addressing Mode */
    I2C_WriteOLEDCommand( OLED_MEMORY_ADDRESSIND_MODE );

    /* Set Addressing Mode */
    I2C_WriteOLEDCommand( OLED_MEMORY_MODE );


    /* Set Segment and COM Output Remapping */
    I2C_WriteOLEDCommand( OLED_SEG_REMAP );
    I2C_WriteOLEDCommand( OLED_COM_REMAP );


    /* Configure COM pin Hardware */
    I2C_WriteOLEDCommand( OLED_SET_COM_PINS );

    /* Alternative COM pin Configuration */
    I2C_WriteOLEDCommand( OLED_COM_PINS_ALT );


    /* Set Contrast level */
    I2C_WriteOLEDCommand( OLED_SET_CONTRAST );

    /* Defined Contrast Value */
    I2C_WriteOLEDCommand( OLED_CONTRAST_VALUE );


    /* Set pre-charge Period */
    I2C_WriteOLEDCommand( OLED_SET_PRECHARGE_PERIOD );

    /* Phase 1: 15 DCLK, Phase 2: 1 DCLK */
    I2C_WriteOLEDCommand( 0xF1 );


    /* Configure VCOMH Deselect level */
    I2C_WriteOLEDCommand( OLED_SET_VCOMH_LEVEL );

    /* Set VCOMH to 0.77 × Vcc */
    I2C_WriteOLEDCommand( OLED_VCOMH_077_VCC );


    /* Resume Display from RAM Content */
    I2C_WriteOLEDCommand( OLED_DISPLAY_RAM );


    /* Set Normal Display Mode */
    I2C_WriteOLEDCommand( OLED_DISPALY_MODE );


    /* Enable Display */
    I2C_WriteOLEDCommand( OLED_DISPLAY_ON );


    /* Stop I2C Communication */
    I2C_Stop();
}





/*
 * @brief Turns on the OLED display.
 *
 * This function sends a command to power on the OLED display, making it active
 * and ready to show content.
 */
void OLED_DisplayON( void )
{
	/* Sends a Command to Power On the Display */
	OLED_WriteCommand( OLED_DISPLAY_ON );
}





/*
 * @brief Turns off the OLED display.
 *
 * This function sends a command to power off the OLED display, putting it into
 * sleep mode to reduce power consumption.
 */
void OLED_DisplayOFF( void )
{
	/* Sends a Command to Power Off the Display */
	OLED_WriteCommand( OLED_DISPLAY_OFF );
}





/*
 * @brief Inverts or restores the display colors.
 *
 * This function sets the display mode to either normal or inverse. In inverse mode,
 * pixels that are normally lit will be turned off, and pixels that are normally off
 * will be lit.
 *
 * @param invert: If `true`, the display is set to inverse mode. If `false`, it is set to normal mode.
 */
void OLED_LogicInvertDisplay( uint8 invert )
{

	/* Check if Inverse Mode is Requested */
	if ( invert == true )
	{
		/* Set the Display to Inverse Mode */
		OLED_WriteCommand( OLED_INVERSE_DISPALY );
	}
	else
	{
		/* Set the Display to Normal Mode */
		OLED_WriteCommand( OLED_NORMAL_DISPALY );
	}
}





/*
 * @brief Sets the cursor position on the OLED display.
 *
 * This function updates the current page and column positions based on the selected
 * memory addressing mode.
 *
 * @param page:   The target page (row) for the cursor position (valid range: 0 to OLED_TOTAL_PAGES - 1).
 * @param colunm: The target column for the cursor position (valid range: 0 to OLED_TOTAL_COLS - 1).
 */
void OLED_SetCursor( uint8 page , uint8 colunm )
{

	/* Ensure the Specified Position is within Valid Bounds */
	if( ( page < OLED_TOTAL_PAGES ) && ( colunm < OLED_TOTAL_COLS ) )
	{

		/* Update Current Cursor Position */
		OLED_CurrentPage = page;
		OLED_CurrentCol = colunm;

		/* Check the Configured Memory Addressing Mode */
		#if		OLED_MEMORY_MODE == OLED_MEMORY_MODE_HORIZONTAL || OLED_MEMORY_MODE == OLED_MEMORY_MODE_VERTICAL

			/* Horizontal and Vertical Addressing Modes: Set Page and Column Range */


			/* Start I2C Communication */
			I2C_Start();

			/* Send OLED Slave Address with Write Instruction */
			I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

			/* Send Command Mode Byte */
			I2C_WriteData( OLED_COMMAND_MODE );


			/* Set Column Address Range */
			I2C_WriteData( OLED_COLUMN_ADDRESS );

			/* From the Target Start Column */
			I2C_WriteData( colunm );

			/* To the Last Column in the Display */
			I2C_WriteData( OLED_LAST_COL );


			/* Set Page Address Range */
			I2C_WriteData( OLED_PAGE_ADDRESS );

			/* From the Target Start Page */
			I2C_WriteData( page );

			/* To the Last Page in the Display */
			I2C_WriteData( OLED_LAST_PAGE );


			/* Stop I2C Communication */
			I2C_Stop();

		#elif	OLED_MEMORY_MODE == OLED_MEMORY_MODE_PAGE

			/* Page Addressing Mode: Set Individual Page and Column Addresses */


			/* Extract Lower and Higher Column Address Nibbles */
			uint8 lowCol = colunm & 0x0F;
			uint8 highCol = ( colunm >> 4 ) & 0x0F;

			/* Start I2C Communication */
			I2C_Start();

			/* Send OLED Slave Address with Write Instruction */
			I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

			/* Send Command Mode Byte */
			I2C_WriteData( OLED_COMMAND_MODE );


			/* Set Page and Column Addresses */
			I2C_WriteData( OLED_SET_PAGE_START | page );
			I2C_WriteData( OLED_SET_LOW_COLUMN_START | lowCol );
			I2C_WriteData( OLED_SET_HIGH_COLUMN_START |  highCol );


			/* Stop I2C Communication */
			I2C_Stop();

		#else
			/* Make an Error */
			#error "Wrong \"OLED_MEMORY_MODE\" configuration option"
		#endif
	}
}





/*
 * @brief Moves the cursor to the next line (page) on the OLED display.
 *
 * This function increments the current page and resets the column to the first position.
 * If the cursor is on the last page, it wraps around to the first page.
 */
void OLED_GoToNextLine( void )
{
	/* Move to the next page (row), wrapping around if at the last page */
	OLED_SetCursor( ( OLED_CurrentPage + 1 ) % OLED_TOTAL_PAGES , OLED_FIRST_COL );
}





/*
 * @brief Clears the OLED display by writing zeros to all pixels.
 *
 * This function turns off the display, writing zeros to all pixels,
 * and Finally, it turns the display back on.
 */
void OLED_ClearScreen( void )
{

	/* Turn Off the Display to Prevent Visual Artifacts while Clearing */
	OLED_DisplayOFF();


	/* Set Cursor to the First Page and First Column */
	OLED_SetCursor( OLED_FIRST_PAGE , OLED_FIRST_COL );


	/* Start I2C Communication */
	I2C_Start();

	/* Send OLED Slave Address with Write Instruction */
	I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

	/* Set OLED to Data Mode for Writing Pixel Data */
	I2C_WriteData( OLED_DATA_MODE );


	/* Write Zeros to All Display Memory (Clear All Pixels) */
	for( uint16 byte = 0 ; byte < OLED_TOTAL_BYTES ; byte++ )
	{
		I2C_WriteData( 0x00 );
	}


	/* Stop I2C Communication */
	I2C_Stop();


	/* Turn the Display Back On After Clearing */
	OLED_DisplayON();
}





/*
 * @brief Deactivates any active scrolling on the OLED display.
 *
 * This function stops the scrolling effect if it is enabled,
 * ensuring the display remains static.
 */
void OLED_DeactiveScrolling( void )
{
	/* Send Command to Stop any Ongoing Scrolling Effect */
	OLED_WriteCommand( OLED_DEACTIVATE_SCROLL );
}





/*
 * @brief Activates scrolling on the OLED display.
 *
 * This function enables scrolling based on the previously configured
 * scrolling parameters.
 */
void OLED_ActiveScrolling( void )
{
	/* Send Command to Activate Scrolling Based on the set Parameters */
	OLED_WriteCommand( OLED_ACTIVATE_SCROLL );
}





/*
 * @brief Configures and starts horizontal scrolling on the OLED display.
 *
 * This function sets up horizontal scrolling in the specified direction
 * between the given start and end pages at the defined speed.
 * It first deactivates any existing scrolling before applying new settings.
 *
 * @param direction:    The scroll direction (OLED_RIGHT_SCROLL or OLED_LEFT_SCROLL).
 * @param start_page:   The starting page for scrolling (valid values: 0 to 7).
 * @param end_page:     The ending page for scrolling (valid values: 0 to 7, must be greater than start_page).
 * @param scroll_speed: The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 */
void OLED_ScrollHorizontal( uint8 direction , uint8 start_page , uint8 end_page , uint8 scroll_speed )
{

	/* Ensure the Specified Parameters are within Valid Bounds */
	if( (start_page < end_page) && (end_page < OLED_TOTAL_PAGES) && (scroll_speed < 8) )
	{

		/* Stop any Active Scrolling Before Setting New Parameters */
		OLED_DeactiveScrolling();

		/* Start I2C Communication */
		I2C_Start();

		/* Send OLED Slave Address with Write Instruction */
		I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

		/* Send Command Mode Byte */
		I2C_WriteData( OLED_COMMAND_MODE );


		/* Select Scroll Direction */
		if( direction == OLED_RIGHT_SCROLL )
		{
			/* Set Right Horizontal Scroll */
			I2C_WriteData( OLED_SCROLL_HORIZ_RIGHT );
		}
		else
		{
			/* Set Left Horizontal Scroll */
			I2C_WriteData( OLED_SCROLL_HORIZ_LEFT );
		}


		/* Dummy Byte (reserved by SSD1306) */
		I2C_WriteData( OLED_DUMMY_BYTE_00 );

		/* Set Start Page */
		I2C_WriteData( start_page );

		/* Set Scrolling Speed */
		I2C_WriteData( scroll_speed );

		/* Set End Page */
		I2C_WriteData( end_page );

		/* Dummy Bytes (reserved by SSD1306) */
		I2C_WriteData( OLED_DUMMY_BYTE_00 );
		I2C_WriteData( OLED_DUMMY_BYTE_FF );


		/* Activate Scrolling */
		I2C_WriteData( OLED_ACTIVATE_SCROLL );


		/* Stop I2C Communication */
		I2C_Stop();
	}
}





/*
 * @brief Initiates vertical scrolling on the OLED display.
 *
 * This function scrolls the content vertically by a specified offset.
 * It utilizes the `OLED_Scroll` function with a predefined horizontal scroll setting.
 *
 * @param scroll_speed:    The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 * @param vertical_offset: The number of vertical rows to scroll per step (valid values: 0-63).
 */
void OLED_ScrollVertical( uint8 scroll_speed, uint8 vertical_offset )
{
	/* Calls OLED_Scroll with Predefined Parameters for Vertical Scrolling */
	OLED_Scroll( OLED_RIGHT_SCROLL , OLED_PAGE_0 , OLED_PAGE_0 , scroll_speed , vertical_offset );
}





/*
 * @brief Configures and starts diagonal scrolling on the OLED display.
 *
 * This function sets up diagonal scrolling by combining horizontal and vertical movements.
 * It first deactivates any existing scrolling before applying new settings.
 *
 * @param direction:       The scroll direction (OLED_RIGHT_SCROLL or OLED_LEFT_SCROLL).
 * @param start_page:      The starting page for scrolling (valid values: 0 to 7).
 * @param end_page:        The ending page for scrolling (valid values: 0 to 7, must be greater than or equal to start_page).
 * @param scroll_speed:    The speed of the scrolling effect (valid values: 0-7, see OLED_def.h -> SSD1306 Scroll Speed).
 * @param vertical_offset: The number of vertical rows to scroll per step (valid values: 0-63).
 */
void OLED_Scroll( uint8 direction , uint8 start_page, uint8 end_page, uint8 scroll_speed, uint8 vertical_offset )
{

	/* Ensure the Specified Parameters are within Valid Bounds */
	if( (start_page <= end_page) && (end_page < OLED_TOTAL_PAGES) && (scroll_speed < 8) && (vertical_offset < OLED_TOTAL_ROW) )
	{

		/* Stop any Active Scrolling Before Setting New Parameters */
		OLED_DeactiveScrolling();

		/* Start I2C Communication */
		I2C_Start();

		/* Send OLED Slave Address with Write Instruction */
		I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

		/* Send Command Mode Byte */
		I2C_WriteData( OLED_COMMAND_MODE );


		/* Set the Vertical Scrolling Area */
		I2C_WriteData( OLED_VERTICAL_SCROLL_AREA );

		/* Number of Rows to Skip from the Top (no skiped rows) */
		I2C_WriteData( OLED_FIRST_ROW );

		/* Total Number of Rows in the Scrollable Area */
		I2C_WriteData( OLED_TOTAL_ROW );


		/* Select Scroll Direction */
		if( direction == OLED_RIGHT_SCROLL )
		{
			/* Set Right Vertical Scroll */
			I2C_WriteData( OLED_SCROLL_VERT_RIGHT );
		}
		else
		{
			/* Set Left Vertical Scroll */
			I2C_WriteData( OLED_SCROLL_VERT_LEFT );
		}


		/* Dummy Byte (reserved by SSD1306) */
		I2C_WriteData( OLED_DUMMY_BYTE_00 );

		/* Set Start Page */
		I2C_WriteData( start_page );

		/* Set Scrolling Speed */
		I2C_WriteData( scroll_speed );

		/* Set End Page */
		I2C_WriteData( end_page );

		/* Vertical Scrolling Offset */
		I2C_WriteData(vertical_offset );

		/* Activate Scrolling */
		I2C_WriteData(OLED_ACTIVATE_SCROLL);

		/* Stop I2C Communication */
		I2C_Stop();
	}
}





/*
 * @brief Sends a command to the OLED display without restarting communication.
 *
 * This function writes a command to the OLED display in a continued sequence without
 * sending a start condition, slave address, or stop condition. It is typically used
 * when multiple commands need to be sent within an active I2C communication session.
 *
 * @param command: The command byte to be sent to the OLED display.
 */
void I2C_WriteOLEDCommand( uint8 command )
{
	/* Indicate that the Next Byte is a Command */
	I2C_WriteData( OLED_COMMAND_CONTINUE );

	/* Send the Actual Command */
	I2C_WriteData( command );
}





/*
 * @brief Sends a single command to the OLED display.
 *
 * This function initiates an I2C communication sequence, sends a command to the OLED display,
 * and then stops communication. It is used for standalone command transmissions.
 *
 * @param command: The command byte to be sent to the OLED display.
 */
void OLED_WriteCommand( uint8 command )
{

	/* Start I2C Communication */
	I2C_Start();

	/* Send OLED Slave Address with Write Instruction */
	I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

	/* Send Command Mode Byte */
	I2C_WriteData( OLED_COMMAND_MODE );

	/* Send the Command Byte */
	I2C_WriteData( command );

	/* Stop I2C Communication */
	I2C_Stop();
}





/*
 * @brief Prints a single character on the OLED display at the current cursor position.
 *
 * This function retrieves the character's font data from program memory (PROGMEM)
 * and writes it to the display. If the character is '\n' or if there is not enough
 * space on the current line, it moves to the next line before printing.
 *
 * @param character: The ASCII character to be printed.
 */
void OLED_PrintCharacter( uint8 character )
{

	/* Move to the Next line if there's not enough Space or if the Character is a Newline */
	if ( ( ( OLED_CurrentCol + OLED_FONT_SIZE ) > OLED_LAST_COL ) || ( character == '\n' ) )
	{
		OLED_GoToNextLine();
	}

	/* Validate that the Character is in the Font Table Before Printing and not Newline Character */
	if ( ( character != '\n' ) && ( character > 0x19 ) && ( ( character - 0x20 ) < ( FontTableSize / OLED_FONT_SIZE ) ) )
	{

		/* Variable to Store the Current Column Byte of the Character From the Font Table */
		uint8 charColByte;

		/* Adjust character index to match the font table */
		character -= 0x20;


		/* Start I2C Communication */
		I2C_Start();

		/* Send OLED Slave Address with Write Instruction */
		I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

		/* Set OLED to Data Mode for Writing Pixel Data */
		I2C_WriteData( OLED_DATA_MODE );


		/* Write Font Data (Character) Column by Column */
		for(uint8 colIndex = 0 ; colIndex < OLED_FONT_SIZE ; colIndex++ )
		{
			/* Read Font Data from PROGMEM (flash memory) */
			charColByte = pgm_read_byte( & FontTable[ character ][ colIndex ] );

			/* Send Character Column Data */
			I2C_WriteData( charColByte );
		}


		/* Update the Cursor Position */
		OLED_CurrentCol += OLED_FONT_SIZE;

		/* Add a Space After the Character if there's Room */
		if( OLED_CurrentCol != OLED_LAST_COL )
		{
			/* Print Space */
			I2C_WriteData( OLED_SPACE_BYTE );

			/* Update the Cursor Position */
			OLED_CurrentCol++;
		}


		/* Stop I2C Communication */
		I2C_Stop();
	}
}





/*
 * @brief Prints a null-terminated string on the OLED display.
 *
 * This function iterates through each character in the provided string
 * and prints.
 *
 * @param Str: Pointer to the null-terminated string to be displayed.
 */
void OLED_PrintString( const char * Str )
{
	/*  Loop through each Character of the String Until the NULL Character is found */
	for(uint8 CharacterIndex = 0 ; Str[CharacterIndex] != '\0' ; CharacterIndex++)
	{
		/* Print each Character on the OLED */
		OLED_PrintCharacter( (uint8) Str[CharacterIndex] );
	}
}





/*
 * @brief Prints an integer number on the OLED display.
 *
 * This function prints the given integer number on the OLED display.
 * If the number does not fit in the current line, it moves to the next line before printing.
 *
 * @param Number: The integer value to be displayed.
 */
void OLED_PrintNumber( sint32 Number )
{
	/* Convert the Integer Number to a String using base 10 */
	char str[12];
	DC_itoa( Number , str , 10 );

	/* Get the length of the converted number string */
	uint8 length = 0;
	while (str[length] != '\0')
	{
		length++;
	}

	/* Check if it its in the Current line, otherwise Move to the Next line */
	if( ( length * ( OLED_FONT_SIZE + 1 ) + OLED_CurrentCol ) > OLED_LAST_COL )
	{
		OLED_GoToNextLine();
	}

	/* Print each Character on the OLED */
	OLED_PrintString( str );
}





/*
 * @brief Sends a single byte of data to the OLED display.
 *
 * This function writes a raw byte to the OLED display, which can be used
 * for direct data transfer, such as drawing custom graphics or sending
 * raw pixel data.
 *
 * @param byte: The byte value to be sent to the display.
 */
void OLED_PrintByte( uint8 byte )
{
	/* Start I2C Communication */
	I2C_Start();

	/* Send OLED Slave Address with Write Instruction */
	I2C_SendSlaveAddress_Write( OLED_SLAVE_ADDRESS );

	/* Set OLED to Data Mode for Writing Pixel Data */
	I2C_WriteData( OLED_DATA_MODE );

	/* Send the Data Byte */
	I2C_WriteData( byte );

	/* Stop I2C Communication */
	I2C_Stop();
}





/*
 * @brief Retrieves the current page position of the cursor on the OLED display.
 *
 * This function returns the current page where the cursor is positioned.
 *
 * @return: The current page position (0-7).
 */
uint8 OLED_GetPage( void )
{
	/* Returns the Current Page Position of the Cursor on the OLED Display */
	return OLED_CurrentPage;
}





/*
 * @brief Retrieves the current column position of the cursor on the OLED display.
 *
 * This function returns the current column where the cursor is positioned.
 *
 * @return: The current column position (0-127).
 */
uint8 OLED_GetColumn( void )
{
	/* Returns the Current Column Position of the Cursor on the OLED Display */
	return OLED_CurrentCol;
}



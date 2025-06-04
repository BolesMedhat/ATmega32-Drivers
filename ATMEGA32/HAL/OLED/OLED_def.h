/****************************************************************************
 * @file    OLED_def.h
 * @author  Boles Medhat
 * @brief   OLED Driver Definitions Header File
 * @version 1.0
 * @date    [2025-03-06]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file contains all macros, constants, and SSD1306 command definitions
 * required for interfacing an OLED display module using the SSD1306 controller
 * over the I2C protocol. It includes addressing modes, hardware configuration,
 * scrolling commands, and timing settings.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the I2C module **before** calling any EEPROM
 *  			   driver function. This driver does not initialize I2C internally.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef OLED_DEF_H_
#define OLED_DEF_H_

#include "../../LIB/STD_TYPES.h"


/*------------------------------------------   macros    ----------------------------------------*/

#define PROGMEM			__attribute__((__progmem__))	/*Attribute to store variables in program memory (Flash) instead of RAM*/

/*Macro to read a byte from program memory (Flash) at the specified address*/
#define pgm_read_byte(addr)				\
(__extension__({						\
    uint16 __addr16 = (uint16)(addr);	\
    uint8 __result;						\
    __asm__								\
    (									\
        "lpm %0, Z" "\n\t"				\
        : "=r" (__result)				\
        : "z" (__addr16)				\
    );									\
    __result;							\
}))
/*_______________________________________________________________________________________________*/



/*------------------------------------------   values    ----------------------------------------*/

/*the OLED I2C Slave Address*/
#define OLED_SLAVE_ADDRESS						0x3C	/*0x3C is the 7-bit address used for communication via I2C*/


/*OLED Font Size*/
#define OLED_FONT_SIZE							5		/*Font size in bytes per character (width of character in pixels)*/


/*OLED Blank Space Byte*/
#define OLED_SPACE_BYTE							0x00	/*Blank space byte (0x00) used for empty regions in character rendering*/


/*SSD1306 Column Configuration*/
#define OLED_FIRST_COL							0		/*First column index in the display (leftmost pixel)*/
#define OLED_LAST_COL							127		/*Last column index in the display (rightmost pixel)*/
#define OLED_TOTAL_COLS							128		/*Total number of columns (horizontal pixels)*/


/*SSD1306 Row Configuration*/
#define OLED_FIRST_ROW							0		/*First row index in the display (topmost pixel)*/
#define OLED_LAST_ROW							63		/*Last row index in the display (bottommost pixel)*/
#define OLED_TOTAL_ROW							64		/*Total number of rows (vertical pixels)*/


/*SSD1306 Page Configuration*/
#define OLED_FIRST_PAGE							0		/*First page index (Page 0: Rows 0 - 7)*/
#define OLED_LAST_PAGE							7		/*Last page index (Page 7: Rows 56 - 63)*/
#define OLED_TOTAL_PAGES						8		/*Total number of pages (each page contains 8 rows)*/


/*SSD1306 Display Memory*/
#define OLED_TOTAL_PIXELS						8192	/*Total number of pixels in the display (128 × 64)*/
#define OLED_TOTAL_BYTES						1024	/*Total number of bytes required to store the entire screen (128 × 64 ÷ 8)*/


/*SSD1306 Scrolling Direction*/
#define OLED_RIGHT_SCROLL						0		/*Value representing rightward scrolling direction*/
#define OLED_LEFT_SCROLL						1		/*Value representing leftward scrolling direction*/


/*SSD1306 Pages*/
#define OLED_PAGE_0								0		/*Page 0: Rows 0 - 7*/
#define OLED_PAGE_1								1		/*Page 1: Rows 8 - 15*/
#define OLED_PAGE_2								2		/*Page 2: Rows 16 - 23*/
#define OLED_PAGE_3								3		/*Page 3: Rows 24 - 31*/
#define OLED_PAGE_4								4		/*Page 4: Rows 32 - 39*/
#define OLED_PAGE_5								5		/*Page 5: Rows 40 - 47*/
#define OLED_PAGE_6								6		/*Page 6: Rows 48 - 55*/
#define OLED_PAGE_7								7		/*Page 7: Rows 56 - 63*/


/*SSD1306 Control Commands*/
#define OLED_COMMAND_MODE						0x00	/*Control byte: Co=0, D/C#=0 → Last command in sequence, no more commands follow*/
#define OLED_COMMAND_CONTINUE					0x80	/*Control byte: Co=1, D/C#=0 → Another command follows, keep command mode active*/
#define OLED_DATA_MODE							0x40	/*Control byte: Co=0, D/C#=1 → Data mode for sending display data*/

#define OLED_DUMMY_BYTE_00						0x00	/*Required dummy byte (0x00) for certain SSD1306 commands*/
#define OLED_DUMMY_BYTE_FF						0xFF	/*Required dummy byte (0xFF) for certain SSD1306 commands*/


/*SSD1306 Fundamental Commands*/
#define OLED_SET_CONTRAST						0x81	/*Double byte command to select 1 out of 256 contrast steps*/

#define OLED_DISPLAY_RAM						0xA4	/*Single byte command to resume displaying content based on the RAM (normal operation)*/
#define OLED_ENTIRE_DISPLAY_ON					0xA5	/*Single byte command to force the entire display to turn ON (all pixels ON, regardless of RAM content*/

#define OLED_NORMAL_DISPALY						0xA6	/*Single byte command to normal  display 0:OFF, 1:ON  (0 in RAM: OFF in display panel,1 in RAM: ON  in display panel)*/
#define OLED_INVERSE_DISPALY					0xA7	/*Single byte command to inverse display 0:ON,  1:OFF (0 in RAM: ON  in display panel,1 in RAM: OFF in display panel)*/

#define OLED_DISPLAY_OFF						0xAE	/*Single byte command to display OFF (sleep mode)*/
#define OLED_DISPLAY_ON							0xAF	/*Single byte command to display ON in normal mode*/


/*SSD1306 Scrolling Commands*/
#define OLED_SCROLL_HORIZ_RIGHT					0x26	/*Continuous right horizontal scrolling (Rotate) for specific part of the screen with specific speed*/
#define OLED_SCROLL_HORIZ_LEFT					0x27	/*Continuous left  horizontal scrolling (Rotate) for specific part of the screen with specific speed*/

#define OLED_SCROLL_VERT_RIGHT					0x29	/*Continuous vertical and right horizontal scrolling (Rotate) for specific part of the screen with specific speed*/
#define OLED_SCROLL_VERT_LEFT					0x2A	/*Continuous vertical and left  horizontal scrolling (Rotate) for specific part of the screen with specific speed*/

#define OLED_DEACTIVATE_SCROLL					0x2E	/*Single byte command to stops any active scrolling effect and keeps the current display content static*/
#define OLED_ACTIVATE_SCROLL					0x2F	/*Single byte command to starts the previously configured scrolling effect*/

#define OLED_VERTICAL_SCROLL_AREA				0xA3	/*Triple byte command to define the vertical scrolling area, specifying the top fixed rows, scrolling rows, and bottom fixed rows*/

/*SSD1306 Scroll Speed*/
#define OLED_SPD_2F								0x07	/*2   frames delay (Extremely fast)*/
#define OLED_SPD_3F								0x04	/*3   frames delay (Very fast)*/
#define OLED_SPD_4F								0x05	/*4   frames delay (Fast)*/
#define OLED_SPD_5F								0x00	/*5   frames delay (Fastest scroll speed)*/
#define OLED_SPD_25F							0x06	/*25  frames delay (Moderate speed)*/
#define OLED_SPD_64F							0x01	/*64  frames delay (Medium speed)*/
#define OLED_SPD_128F							0x02	/*128 frames delay (Slower scroll speed)*/
#define OLED_SPD_256F							0x03	/*256 frames delay (Slowest scroll speed)*/


/*SSD1306 Addressing Setting Commands*/
#define OLED_SET_LOW_COLUMN_START				0x00	/*Set lower 4 bits of the column start address for page addressing mode (range: 0x00 to 0x0F)*/
#define OLED_SET_HIGH_COLUMN_START				0x10	/*Set higher 4 bits of the column start address for page addressing mode (range: 0x10 to 0x1F)*/

#define OLED_MEMORY_ADDRESSIND_MODE				0x20	/*Double byte command to select memory addressing mode (Horizontal, Vertical, Page mode)*/

#define OLED_COLUMN_ADDRESS						0x21	/*Triple byte command to set column start and end address (only for horizontal or vertical addressing mode)*/
#define OLED_PAGE_ADDRESS						0x22	/*Triple byte command to set page start and end address (only for horizontal or vertical addressing mode)*/

#define OLED_SET_PAGE_START						0xB0	/*Set page start address for page addressing mode (range: 0xB0 to 0xB7, corresponding to 8 pages)*/

/*SSD1306 Memory Addressing Modes*/
#define OLED_MEMORY_MODE_HORIZONTAL				0x00	/*Horizontal addressing mode*/
#define OLED_MEMORY_MODE_VERTICAL				0x01	/*Vertical addressing mode*/
#define OLED_MEMORY_MODE_PAGE					0x02	/*Page addressing mode*/


/*SSD1306 Hardware Configuration Commands*/
#define OLED_DISPLAY_START_LINE					0x40	/*Single byte command to set the row in RAM that will be the first line on the screen from 0d to 63d*/

#define OLED_SEG_REMAP_NORMAL					0xA0	/*Single byte command to set segment re-map to normal (column address 0d is mapped to SEG0)*/
#define OLED_SEG_REMAP_REVERSE					0xA1	/*Single byte command to set segment re-map to reversed (column address 127d is mapped to SEG0)*/

#define OLED_SET_MULTIPLEX_RATIO				0xA8	/*Double byte command to select multiplex ratio (number of COM lines)*/

#define OLED_COM_REMAP_NORMAL					0xC0	/*Single byte command to set COM (row) re-map to normal (COM0 to COM[N-1])*/
#define OLED_COM_REMAP_REVERSE					0xC8	/*Single byte command to set COM (row) re-map to reversed (COM[N-1] to COM0)*/

#define OLED_SET_DISPLAY_OFFSET					0xD3	/*Double byte command to set vertical shift by COM from 0d to 63d*/

#define OLED_SET_COM_PINS						0xDA	/*Double byte command to set COM pin hardware configuration*/

#define OLED_COM_PINS_SEQ						0x02	/*Sequential COM pin configuration, no remap*/
#define OLED_COM_PINS_ALT						0x12	/*Alternative COM pin configuration, remap enabled*/
#define OLED_COM_PINS_SEQ_R						0x22	/*Sequential COM pin configuration, remapped*/
#define OLED_COM_PINS_ALT_R						0x32	/*Alternative COM pin configuration, remapped*/


/*SSD1306 Timing & Driving Scheme Setting Commands*/
#define OLED_SET_DISPLAY_CLK_DIV				0xD5	/*Double byte command to set display clock divide ratio and oscillator frequency*/

#define OLED_SET_PRECHARGE_PERIOD				0xD9	/*Double byte command to set pre-charge period*/

#define OLED_SET_VCOMH_LEVEL					0xDB	/*Double byte command to set VCOMH deselect level*/
#define OLED_VCOMH_065_VCC						0x00	/*VCOMH Deselect Level = 0.65 × Vcc*/
#define OLED_VCOMH_077_VCC						0x20	/*VCOMH Deselect Level = 0.77 × Vcc (Default)*/
#define OLED_VCOMH_083_VCC						0x30	/*VCOMH Deselect Level = 0.83 × Vcc*/
#define OLED_VCOMH_086_VCC						0x40	/*VCOMH Deselect Level = 0.86 × Vcc*/

#define OLED_NOP								0xE3	/*Single byte command for no operation*/


/*SSD1306 Charge Pump Command*/
#define OLED_CHARGE_PUMP						0x8D	/*Double byte command to enable or disable charge pump regulator*/
#define OLED_CHARGE_PUMP_ENABLE					0x14	/*Enable charge pump*/
#define OLED_CHARGE_PUMP_DISABLE				0x10	/*Disable charge pump*/
/*_______________________________________________________________________________________________*/



/*------------------------------------------   masks    -----------------------------------------*/

#define OLED_START_ROW_OFFSET_msk				0x3F	/*Start row offset mask*/
/*_______________________________________________________________________________________________*/


#endif /* OLED_DEF_H_ */

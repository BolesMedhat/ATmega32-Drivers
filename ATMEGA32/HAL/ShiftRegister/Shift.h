/****************************************************************************
 * @file    Shift.h
 * @author  Boles Medhat
 * @brief   Shift Register Driver Header File
 * @version 1.3
 * @date    [2024-09-28]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file demonstrates the use of shift register driver functions with:
 * - 74HC595: Serial to Parallel (Shift-Out)
 * - 74HC165: Parallel to Serial (Shift-In)
 *
 * The following functions are included:
 * - SHIFT_OUT_Init: Initializes the pins for output shifting.
 * - SHIFT_IN_Init: Initializes the pins for input shifting.
 * - SHIFT_IN_Byte: Reads one byte of data from the shift register.
 * - SHIFT_OUT_Byte: Sends one byte of data to the shift register.
 * - SHIFT_OUT_Latch: Latches the shifted-out data to the shift register.
 * - SHIFT_IN_Latch: Latches the shifted-in data from the shift register.
 *
 * @note
 * - Requires `Shift_config.h` for macro-based configuration.
 *
 * @example for two 74HC595 (Shift-Out):
 * 		SHIFT_OUT_Init();
 * 		SHIFT_OUT_Byte( 0xAA );
 * 		SHIFT_OUT_Byte( 0x55 );
 * 		SHIFT_OUT_Latch();
 *
 * @example for two 74HC165 (Shift-In):
 *		SHIFT_IN_Init();
 * 		SHIFT_IN_Latch();
 * 		uint8 high_byte = SHIFT_IN_Byte();
 * 		uint8 low_byte = SHIFT_IN_Byte();
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef SHIFT_H_
#define SHIFT_H_

#include "../../LIB/STD_TYPES.h"
#include <util/delay.h>
#include "Shift_config.h"


/*
 * @brief Initializes the pins for shifting data out to the shift register.
 *
 * This function configures the clock, load, and data pins for the shift-out
 * operations. All pins are set to low initially.
 */
void SHIFT_OUT_Init(void);


/*
 * @brief Initializes the pins for shifting data in from the shift register.
 *
 * This function configures the clock, load, and data pins for the shift-in
 * operations. The data pin is configured as an input, while the clock and load
 * pins are configured as outputs. All pins are set to low initially.
 */
void SHIFT_IN_Init(void);


/*
 * @brief Sends one byte of data to the shift register.
 *
 * This function shifts out one byte of data to the shift register, sending
 * one bit at a time in the specified bit order (SHIFT_LSB_FIRST or SHIFT_MSB_FIRST).
 *
 * @param data: The byte of data to be sent to the shift register.
 */
void SHIFT_OUT_Byte(uint8 data);


/*
 * @brief Reads one byte of data from the shift register.
 *
 * This function shifts in one byte of data from the shift register by sending
 * clock pulses. The data is returned in the specified bit order (SHIFT_LSB_FIRST or SHIFT_MSB_FIRST).
 *
 * @return (uint8) The data read from the shift register.
 */
uint8 SHIFT_IN_Byte(void);


/*
 * @brief Latches data to 74HC595 output pins.
 *
 * This function pulses the latch pin (RCLK) to move the shifted serial data
 * into the output register, making it visible on the parallel output pins.
 */
void SHIFT_OUT_Latch(void);


/*
 * @brief Latches data from 74HC165 input pins.
 *
 * This function pulses the latch pin (SH/LD) to load the current state of
 * the parallel input pins into the shift register for serial reading.
 */
void SHIFT_IN_Latch(void);


#endif /* SHIFT_H_ */

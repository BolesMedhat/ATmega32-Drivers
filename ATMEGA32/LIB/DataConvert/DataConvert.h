/****************************************************************************
 * @file	DataConvert.h
 * @author  Boles Medhat
 * @brief   Data Conversion Utility Functions
 * @version 1.0
 * @date	[2025-01-15]
 * @license MIT License Copyright (c) 2025 Boles Medhat
 *
 * @details
 * This file provides lightweight conversion utilities for integer and float
 * to ASCII string and vice versa. Designed for embedded systems (AVR) without
 * relying on heavy standard libraries like stdio.h or stdlib.h.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef DATACONVERT_H_
#define DATACONVERT_H_

#include "../STD_TYPES.h"


/*
 * @brief Converts an integer to a string with a given base.
 *
 * This function supports conversions from base 2 for binary to base 16 for hex
 * and returns the resulting null-terminated string.
 *
 * @param value: Integer value to convert.
 * @param str:   Pointer to output buffer (should be large enough).
 * @param base:  Numerical base for conversion (e.g., 10 for decimal).
 */
void DC_itoa(sint32 value, char* str, uint8 base);


/*
 * @brief Converts a numeric string to an integer (base 10).
 *
 * This function parses a string containing decimal digits and converts it into a signed integer.
 *
 * @param str: Pointer to input string.
 *
 * @return Converted signed integer.
 */
sint32 DC_atoi(const char* str);


/*
 * @brief Converts a floating-point number to a string.
 *
 * This function converts a float into its ASCII representation with a given number of digits
 * after the decimal point.
 *
 * @param number:	  Floating-point number to convert.
 * @param str:		 Pointer to output buffer (should be large enough).
 * @param afterpoint:  Number of digits to show after the decimal point.
 */
void DC_ftoa(float32 number, char* str, uint8 afterpoint);


/*
 * @brief Converts a string to a floating-point number.
 *
 * This function parses a string representing a float (with optional sign and decimal point)
 * and converts it to a float32 value.
 *
 * @param: str Pointer to input numeric string.
 *
 * @return Converted float32 value.
 */
float32 DC_atof(const char* str);


/*
 * @brief Converts an 8-bit unsigned decimal value (0–99) to BCD (hex) format.
 *
 * This function encodes a decimal number into BCD (hex) format,
 * commonly used in digital displays, RTCs, and hardware interfaces.
 *
 * @example:
 *    Input: 45 (decimal)
 *    Output: 0x45 (BCD: upper nibble = 4, lower nibble = 5)
 *
 * @param decimal: The decimal value to convert (valid range: 0–99).
 *
 * @return (uint8) BCD-encoded (hex) value representing the decimal input.
 */
uint8 DC_decimal_to_hex( uint8 decimal );


/*
 * @brief Converts a BCD-encoded (hex) 8-bit value to a standard decimal value.
 *
 * This function decodes a BCD (hex) input into its equivalent base-10 decimal representation.
 * @example:
 *    Input: 0x45 (BCD)
 *    Output: 45 (decimal)
 *
 * @param hex: The BCD-encoded value to convert.
 *
 * @return (uint8) Decimal integer equivalent of the BCD input.
 */
uint8 DC_hex_to_decimal( uint8 hex );


#endif /* DATACONVERT_H_ */

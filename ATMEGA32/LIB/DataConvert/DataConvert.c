/****************************************************************************
 * @file	DataConvert.c
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


#include "DataConvert.h"





/*
 * @brief Reverses a string in place.
 *
 * This function reverses the order of characters in the given string.
 *
 * @param str: Pointer to the string to reverse.
 * @param len: Length of the string.
 */
static void reverse(char* str, sint32 len)
{
	/* Initialize two indexes: i at start, j at end */
	uint8 i = 0, j = len - 1;

	/* Temporary variable for swapping */
	char tmp;

	/* Loop until the two indexes meet or cross to reverse the string */
	while(i < j)
	{
		/* Store character at i in tmp */
		tmp = str[i];

		/* Copy character at j to position i, then increment i */
		str[i++] = str[j];

		/* Copy tmp to position j, then decrement j */
		str[j--] = tmp;
	}
}





/*
 * @brief Helper function to convert an integer to string with fixed width (used for fractional part).
 *
 * This function ensures the number is converted with leading zeros to fill a fixed number of digits.
 *
 * @param number: Integer to convert.
 * @param str:	Pointer to output buffer.
 * @param digits: Minimum number of digits to include (zero-padded).
 */
static void intToStr(uint32 number, char str[], uint8 digits)
{
	/* Index for string building */
	uint8 i = 0;

	/* Handle zero explicitly */
	if (number == 0)
	{
		/* Add '0' character explicitly */
		str[i++] = '0';
	}

	/* Continue while number > 0 or less than required digits */
	while (number != 0 || i < digits)
	{
		/* Extract last digit as char */
		str[i++] = (number % 10) + '0';

		/* Remove last digit */
		number /= 10;
	}

	/* Reverse string to correct digit order */
	reverse(str, i);

	/* Null-terminate string */
	str[i] = '\0';
}





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
void DC_itoa(sint32 value, char* str, uint8 base)
{
	/* Index for string building */
	uint8 i = 0;

	/* Flag to mark if number is negative */
	bool is_negative = false;

	/* Only base 2 to 16 supported */
	if (base < 2 || base > 16)
	{
		/* Invalid base, return empty string */
		str[0] = '\0';
		return;
	}

	/* Handle 0 explicitly */
	if (value == 0)
	{

		/* If zero, just add '0' char */
		str[i++] = '0';

		/* Null-terminate string */
		str[i] = '\0';
		return;
	}

	/* Handle negative numbers in base 10 only */
	if (value < 0 && base == 10)
	{
		/* Mark negative */
		is_negative = true;
		/* Convert to positive for processing */
		value = -value;
	}

	/* Process each digit */
	while (value != 0)
	{
		/* Get remainder (digit in base) */
		int rem = value % base;
		/* Convert digit to char: 0-9 or A-F for hex etc. */
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		/* Move to next digit */
		value /= base;
	}

	/* Add minus sign if negative */
	if (is_negative)
	{
		str[i++] = '-';
	}

	/* Null-terminate string */
	str[i] = '\0';

	/* Reverse string to correct digit order */
	reverse(str, i);

	/* Return pointer to resulting string */
	return;
}





/*
 * @brief Converts a numeric string to an integer (base 10).
 *
 * This function parses a string containing decimal digits and converts it into a signed integer.
 *
 * @param str: Pointer to input string.
 *
 * @return (sint32) Converted signed integer.
 */
sint32 DC_atoi(const char* str)
{
	/* Result accumulator */
	sint32 result = 0;

	/* Negative flag */
	bool is_negative = false;

	/* Check for negative sign */
	if (*str == '-')
	{
		/* Mark negative */
		is_negative = true;

		/* Move pointer past sign */
		str++;
	}

	/* While chars are digits */
	while (*str >= '0' && *str <= '9')
	{
		/* Accumulate digit value */
		result = result * 10 + (*str - '0');

		/* Move to next char */
		str++;
	}

	/* Return negative or positive result accordingly */
	if (is_negative == true)
	{
		return -result;
	}
	else
	{
		return result;
	}
}





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
void DC_ftoa(float32 number, char* str, uint8 afterpoint)
{
	/* Check if number is negative */
	if (number < 0)
	{
		/* Add minus sign to string */
		*str++ = '-';

		/* Make number positive for conversion */
		number = -number;
	}

	/* Extract integer part */
	sint32 ipart = (sint32)number;

	/* Extract fractional part */
	float32 fpart = number - (float32)ipart;

	/* Convert integer part to string (base 10) */
	DC_itoa(ipart, str, 10);

	/* Move pointer to end of integer string */
	while (*str) str++;

	/* Add decimal point */
	*str++ = '.';

	/* Multiply fractional part by 10^afterpoint */
	for (uint8 i = 0; i < afterpoint; i++)
	{
		fpart *= 10;
	}

	/* Convert fractional part to string with rounding */
	intToStr((uint32)(fpart + 0.5f), str, afterpoint);
}





/*
 * @brief Converts a string to a floating-point number.
 *
 * This function parses a string representing a float (with optional sign and decimal point)
 * and converts it to a float32 value.
 *
 * @param: str Pointer to input numeric string.
 *
 * @return (float32) Converted float32 value.
 */
float32 DC_atof(const char* str)
{
	/* Integer part accumulator */
	float32 result = 0.0;
	/* Fractional part accumulator */
	float32 fraction = 0.0;
	/* Divisor for fractional part */
	sint32 divisor = 1;
	/* Negative flag */
	bool is_negative = false;
	/* Fraction flag */
	bool is_fraction = false;
	/* Current digit */
	uint8 digit;

	/* Check for negative sign */
	if (*str == '-')
	{
		/* Mark negative */
		is_negative = true;
		/* Move past sign */
		str++;
	}

	/* Loop over string characters */
	while (*str)
	{
		/* Check for decimal point */
		if (*str == '.')
		{
			/* Enable fraction mode */
			is_fraction = true;
			/* Move past decimal point */
			str++;
			continue;
		}

		/* If character is a digit */
		if (*str >= '0' && *str <= '9')
		{
			/* Convert char to digit */
			digit = *str - '0';
			/* If parsing fractional part */
			if (is_fraction)
			{
				/* Increase divisor by factor of 10 */
				divisor *= 10;
				/* Accumulate fraction digits */
				fraction = fraction * 10 + digit;
			}
			else
			{
				/* Accumulate integer part */
				result = result * 10 + digit;
			}
		}
		else
		{
			/* Break on non-numeric character */
			break;
		}
		/* Advance to next char */
		str++;
	}

	/* Add fractional part divided by divisor */
	result = result + (fraction / divisor);

	/* Return negative or positive result accordingly */
	if (is_negative == true)
	{
		return -result;
	}
	else
	{
		return result;
	}
}





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
uint8 DC_decimal_to_hex( uint8 decimal )
{
	return ( ( decimal / 10 ) << 4 ) | ( decimal % 10 );
}





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
uint8 DC_hex_to_decimal( uint8 hex )
{
	return ( ( hex >> 4 ) * 10 ) + ( hex & 0x0F );
}

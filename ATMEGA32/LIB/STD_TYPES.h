/****************************************************************************
 * @file    STD_TYPES.h
 * @author  Boles Medhat
 * @brief   Standard Data Types Header File
 * @version 2.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file defines standard data types, boolean constants, NULL, and
 * common status macros used throughout embedded software development.
 * It ensures code portability and consistency across all modules and layers.
 *
 * The STD_TYPES file includes:
 * - Boolean type and constants (`true`, `false`, etc.)
 * - Signed and unsigned integers (8/16/32/64-bit)
 * - Floating point types (`float32`, `float64`)
 * - NULL pointer definition
 * - Standard status macros (`SUCCESS`, `ERROR`)
 *
 * This file is intended to be included in all driver and application layers.
 *
 * @note
 * - Type names and conventions are similar to AUTOSAR and widely used embedded standards.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean type definitions */
typedef unsigned char			bool;		/* 8-bit Boolean type: true or false (True or False) */

/* Boolean Values definitions */
#define false					0				/* Representing 0 value as false */
#define true					1				/* Representing 1 value as true */
#define False					0				/* Representing 0 value as False (alternative name) */
#define True					1				/* Representing 1 value as True (alternative name) */

/* Integer type definitions */
typedef unsigned char			uint8;			/* Unsigned 8-bit  integer:  0 to 255 */
typedef signed char				sint8;			/* Signed 	8-bit  integer:	 -128 to 127 */
typedef unsigned short			uint16;			/* Unsigned 16-bit integer:	 0 to 65535 */
typedef signed short			sint16;			/* Signed 	16-bit integer:	 -32768 to 32767 */
typedef unsigned long			uint32;			/* Unsigned 32-bit integer:	 0 to 4294967295 */
typedef signed long				sint32;			/* Signed 	32-bit integer:	 -2147483648 to 2147483647 */
typedef unsigned long long		uint64;			/* Unsigned 64-bit integer:	 0 to 18446744073709551615 */
typedef signed long long		sint64;			/* Signed 	64-bit integer:	 -9223372036854775808 to 9223372036854775807 */

/* Floating point type definitions */
typedef float					float32;		/* 32-bit floating-point: Single precision */
typedef double					float64;		/* 64-bit floating-point: Double precision */

/* NULL value definitions (if not already defined) */
#ifndef NULL
#define NULL					((void*)0)		/* define NULL value as a pointer to zero */
#endif

/* Error handling */
#define SUCCESS					0				/* Indicates the operation was successful */
#define ERROR					1				/* Indicates the operation failed */


#endif /* STD_TYPES_H_ */

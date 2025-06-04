/****************************************************************************
 * @file    BIT_MATH.h
 * @author  Boles Medhat
 * @brief   Bit Math (or Bit Manipulation) Macros Header File
 * @version 1.0
 * @date    [2025-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file provides a set of generic macros for performing bit-level operations
 * on registers and variables. These macros are commonly used in embedded systems
 * programming for efficient manipulation of control and status registers.
 *
 * The BIT_MATH file includes:
 * - Set, clear, toggle individual bits.
 * - Bit rotations (left and right).
 * - Bit checking (set/clear) and bit retrieval.
 *
 * This file is intended to be included in all driver and application layers.
 *
 * @note
 * - Use with caution on multi-byte registers to avoid unintended behavior.
 * - Designed for 8-bit values unless otherwise specified.
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef BIT_MATH_H_
#define BIT_MATH_H_


/* Set a Specific Bit in any Register */
#define SET_BIT( REG , BIT )				( ( REG ) |= ( 1 << ( BIT ) ) )


/* Clear a Specific Bit in any Register */
#define CLR_BIT( REG , BIT )				( ( REG ) &= ( ~ ( 1 << ( BIT ) ) ) )


/* Toggle a Specific Bit in any Register */
#define TOG_BIT( REG , BIT )				( ( REG ) ^= ( 1 << ( BIT ) ) )


/* Rotate Right the Register Value with Specific number of rotates */
#define ROR( REG , num )					( ( REG ) = ( ( REG ) >> ( num ) ) | ( ( REG ) << ( 8 - num ) ) )


/* Rotate Left the Register Value with Specific number of rotates */
#define ROL( REG , num )					( ( REG ) = ( ( REG ) << ( num ) ) | ( ( REG ) >> ( 8 - num ) ) )


/* Check if a Specific Bit is set in any Register and return true if yes */
#define IS_BIT_SET( REG , BIT )				( ( ( REG ) >> ( BIT ) ) & 0x01 )


/* Check if a Specific Bit is cleared in any Register and return true if yes */
#define IS_BIT_CLR( REG , BIT )				( ! ( ( ( REG ) >> (BIT) ) & 0x01 ) )


/* Get the value of a Specific Bit */
#define GET_BIT( REG , BIT )				( ( ( REG ) >> ( BIT ) ) & 0x01 )


#endif /* BIT_MATH_H_ */

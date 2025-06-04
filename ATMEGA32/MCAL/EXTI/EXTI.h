/****************************************************************************
 * @file    EXTI.h
 * @author  Boles Medhat
 * @brief   External Interrupt (EXTI) Driver Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-01]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for External Interrupt in ATmega32
 * microcontroller, It supports INT0, INT1, and INT2 with customizable pin modes,
 * sense control, and user-defined callback functions.
 *
 * The EXTI driver includes the following functionalities:
 * - Initialization of INT0, INT1, and INT2 interrupts.
 * - Dynamic runtime configuration for interrupt sense control.
 * - Callback function registration for each interrupt.
 * - Fine-grained control over enabling/disabling individual interrupts.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `EXTI_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef EXTI_INTERRUPT_H_
#define EXTI_INTERRUPT_H_

#include "../../LIB/BIT_MATH.h"
#include "EXTI_config.h"


/*
 * @brief Initializes the external interrupts based on configuration options.
 *
 * This function initializes the external interrupts (INT0, INT1, INT2) by configuring the pin modes,
 * sense control, and enabling/disabling interrupts.
 * It configures the external interrupts registers according to the defined macros in `EXTI_config.h`.
 * It also sets up global interrupt enable.
 *
 * @see `EXTI_config.h` for configuration options.
 */
void EXTI_Init( void );


/*
 * @brief Disables a specified external interrupt.
 *
 * This function disables the external interrupt corresponding to the specified ID (INT0, INT1, or INT2).
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 */
void EXTI_DisableInterrupt( uint8 interrupt_id );


/*
 * @brief Enables a specified external interrupt.
 *
 * This function enables the external interrupt corresponding to the specified ID (INT0, INT1, or INT2).
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 */
void EXTI_EnableInterrupt( uint8 interrupt_id );


/*
 * @brief Changes the sense control of a specified external interrupt.
 *
 * This function allows the runtime configuration of the sense control for an external interrupt
 * (INT0, INT1, or INT2) to one of the following modes: low level, any logic change, falling edge,
 * or rising edge.
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 * @param sense_mode:   The sense control mode:
 * 						 - EXTI_THE_LOW_LEVEL
 * 						 - EXTI_ANY_LOGIC_CHANGE
 * 						 - EXTI_THE_FALLING_EDGE
 * 						 - EXTI_THE_RISING_EDGE
 */
void EXTI_ChangeSenseControl( uint8 interrupt_id , uint8 sense_mode );


/*
 * @brief Sets a callback function for a specified external interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified external interrupt (INT0, INT1, or INT2) interrupt occurs.
 *
 * @example
 * void EXTI_InterruptHandler()
 * {
 *     // code
 * }
 * ...
 * EXTI_SetCallback( EXTI_INT0_ID , EXTI_InterruptHandler );
 *
 * @param interrupt_id: The interrupt ID (EXTI_INT0_ID, EXTI_INT1_ID, EXTI_INT2_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void EXTI_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) );


#endif /* EXTI_INTERRUPT_H_ */

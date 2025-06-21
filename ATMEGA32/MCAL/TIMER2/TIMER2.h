/******************************************************************************
 * @file    TIMER2.h
 * @author  Boles Medhat
 * @brief   TIMER2 Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER2 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, and time tracking.
 *
 * The TIMER2 driver includes the following functionalities:
 * - Initialization of TIMER2 with configurable options.
 * - Enable/Disable operations for starting or halting the timer.
 * - Set and get Timer/Compare register values.
 * - Interrupt enable/disable and callback function management.
 * - Time tracking in milliseconds based on timer overflows and compare matches.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER2_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER2_H_
#define TIMER2_H_

#include "../../LIB/BIT_MATH.h"
#include "TIMER2_config.h"


/*
 * @brief Initialize TIMER2 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC2),
 * preload values for TCNT2 and OCR2, interrupt enables, and the clock source.
 * It configures the TIMER2 registers according to the defined macros in `TIMER2_config.h`.
 *
 * @see `TIMER2_config.h` for configuration options.
 */
void TIMER2_Init( void );


/*
 * @brief Disable (stop) TIMER2 by clearing the clock source bits.
 *
 * This function stops the TIMER2 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER2_Disable( void );


/*
 * @brief Enable (resume) TIMER2 by reapplying the configured clock source.
 *
 * This function re-enables TIMER2 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER2_Init`, so it may not be necessary to call.
 */
void TIMER2_Enable( void );


/*
 * @brief Set the Output Compare Register (OCR2) value.
 *
 * This function set OCR2 value that determines when a compare match interrupt
 * is triggered or when the OC2 output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR2.
 */
void TIMER2_SetCompareValue( uint8 CompareValue );


/*
 * @brief Get the OCR2 register value.
 *
 * This function get OCR2 value of TIMER2.
 *
 * @return (uint8) value of OCR2 register.
 */
uint8 TIMER2_GetCompareValue( void );


/*
 * @brief Set the Timer Counter Register (TCNT2) value.
 *
 * This function set TCNT2 value that determines the current count of TIMER2
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT2.
 */
void TIMER2_SetTimerValue( uint8 TimerValue );


/*
 * @brief Get the current TIMER2 counter value.
 *
 * This function get TCNT2 value that determines the current count of TIMER2.
 *
 * @return: Current value of TCNT2 register.
 */
uint8 TIMER2_GetTimerValue( void );


/*
 * @brief Disable a specific TIMER2 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable.
 *        Use `TIMER2_OVF_ID` or `TIMER2_COMP_ID`.
 */
void TIMER2_InterruptDisable( uint8 interrupt_id );


/*
 * @brief Enable a specific TIMER2 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable.
 *        Use `TIMER2_OVF_ID` or `TIMER2_COMP_ID`.
 */
void TIMER2_InterruptEnable( uint8 interrupt_id );


/*
 * @brief Get the total time elapsed since TIMER2 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT2 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return: Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT2 after initialization.
 * @warning TIMER2_COUNT_MODE and any TIMER2 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER2_GetTime_ms( void );


/*
 * @brief Reset TIMER2 counter and overflow counter to zero.
 *
 * This function resets both TCNT2 and `TIMER2_Counter` to start counting from the beginning.
 */
void TIMER2_RESET( void );


/*
 * @brief Calculate Timer2 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer2 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT2 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT2:      Pointer to store the starting TCNT2 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT2 with initialTCNT2
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER2_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows, uint8 * initialTCNT2 );


/*
 * @brief Sets a callback function for a specified Timer2 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer2 (OVF,or COMP) interrupt occurs.
 *
 * @example TIMER2_SetCallback( TIMER2_OVF_ID , TIMER2_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID (TIMER2_OVF_ID, TIMER2_COMP_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER2_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) );


#endif /* TIMER2_H_ */

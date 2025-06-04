/******************************************************************************
 * @file    TIMER0.h
 * @author  Boles Medhat
 * @brief   TIMER0 Driver Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-07-02]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER0 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, and time tracking.
 *
 * The TIMER0 driver includes the following functionalities:
 * - Initialization of TIMER0 with configurable options.
 * - Enable/Disable operations for starting or halting the timer.
 * - Set and get Timer/Compare register values.
 * - Interrupt enable/disable and callback function management.
 * - Time tracking in milliseconds based on timer overflows and compare matches.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER0_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER0_H_
#define TIMER0_H_

#include "../../LIB/BIT_MATH.h"
#include "TIMER0_config.h"


/*
 * @brief Initialize TIMER0 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC0),
 * preload values for TCNT0 and OCR0, interrupt enables, and the clock source.
 * It configures the TIMER0 registers according to the defined macros in `TIMER0_config.h`.
 *
 * @see `TIMER0_config.h` for configuration options.
 */
void TIMER0_Init( void );


/*
 * @brief Disable (stop) TIMER0 by clearing the clock source bits.
 *
 * This function stops the TIMER0 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER0_Disable( void );


/*
 * @brief Enable (resume) TIMER0 by reapplying the configured clock source.
 *
 * This function re-enables TIMER0 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER0_Init`, so it may not be necessary to call.
 */
void TIMER0_Enable( void );


/*
 * @brief Set the Output Compare Register (OCR0) value.
 *
 * This function set OCR0 value that determines when a compare match interrupt
 * is triggered or when the OC0 output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR0.
 */
void TIMER0_SetCompareValue( uint8 CompareValue );


/*
 * @brief Get the OCR0 register value.
 *
 * This function get OCR0 value of TIMER0.
 *
 * @return (uint8) value of OCR0 register.
 */
uint8 TIMER0_GetCompareValue( void );


/*
 * @brief Set the Timer Counter Register (TCNT0) value.
 *
 * This function set TCNT0 value that determines the current count of TIMER0
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT0.
 */
void TIMER0_SetTimerValue( uint8 TimerValue );


/*
 * @brief Get the current TIMER0 counter value.
 *
 * This function get TCNT0 value that determines the current count of TIMER0.
 *
 * @return (uint8) Current value of TCNT0 register.
 */
uint8 TIMER0_GetTimerValue( void );


/*
 * @brief Disable a specific TIMER0 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable.
 *        Use `TIMER0_OVF_ID` or `TIMER0_COMP_ID`.
 */
void TIMER0_InterruptDisable( uint8 interrupt_id );


/*
 * @brief Enable a specific TIMER0 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable.
 *        Use `TIMER0_OVF_ID` or `TIMER0_COMP_ID`.
 */
void TIMER0_InterruptEnable( uint8 interrupt_id );


/*
 * @brief Get the total time elapsed since TIMER0 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT0 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return (uint64) Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT0 after initialization.
 * @warning TIMER0_COUNT_MODE and any TIMER0 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER0_GetTime_ms( void );


/*
 * @brief Reset TIMER0 counter and overflow counter to zero.
 *
 * This function resets both TCNT0 and `TIMER0_Counter` to start counting from the beginning.
 */
void TIMER0_RESET( void );


/*
 * @brief Calculate Timer0 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer0 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT0 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT0:      Pointer to store the starting TCNT0 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT0 with initialTCNT0
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER0_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows , uint8 * initialTCNT0 );


/*
 * @brief Sets a callback function for a specified Timer0 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer0 (OVF,or COMP) interrupt occurs.
 *
 * @example TIMER0_SetCallback( TIMER0_OVF_ID , TIMER0_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID (TIMER0_OVF_ID, TIMER0_COMP_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER0_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) );


#endif /* TIMER0_H_ */

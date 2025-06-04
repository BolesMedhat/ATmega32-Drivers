/******************************************************************************
 * @file    TIMER1.h
 * @author  Boles Medhat
 * @brief   TIMER1 Driver Header File - AVR ATmega32
 * @version 1.0
 * @date    [2024-07-05]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for TIMER0 in ATmega32 microcontroller,
 * supporting Normal, CTC, PWM, and Fast PWM modes. It includes initialization,
 * interrupt control, value setting/getting, callback registration, input capture functionality,
 * and time tracking.
 *
 * The TIMER1 driver includes the following functionalities:
 * - Initialization of TIMER1 with configurable options.
 * - Enable/Disable operations for starting or halting the timer.
 * - Set and get Timer/Compare register values.
 * - Interrupt enable/disable and callback function management.
 * - Time tracking in milliseconds based on timer overflows and compare matches.
 * - Input Capture functionality with edge detection and capture event handling.
 *
 * This driver is designed for modular and reusable embedded projects.
 *
 * @note
 * - Requires `TIMER1_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_

#include "../../LIB/BIT_MATH.h"
#include "TIMER1_config.h"


/*
 * @brief Initialize TIMER1 peripheral based on configuration options.
 *
 * This function configures the waveform generation mode, output compare mode (OC1A and OC1B),
 * preload values for TCNT1, OCR1A, and OCR1B, interrupt enables, and the clock source.
 * It configures the TIMER1 registers according to the defined macros in `TIMER1_config.h`.
 *
 * @see `TIMER1_config.h` for configuration options.
 */
void TIMER1_Init( void );


/*
 * @brief Disable (stop) TIMER1 by clearing the clock source bits.
 *
 * This function stops the TIMER1 by setting its clock source to "No Clock",
 * effectively halting the timer.
 */
void TIMER1_Disable( void );


/*
 * @brief Enable (resume) TIMER1 by reapplying the configured clock source.
 *
 * This function re-enables TIMER1 after it was disabled by setting
 * the configured clock source bits.
 *
 * @note This is already done in `TIMER1_Init`, so it may not be necessary to call.
 */
void TIMER1_Enable( void );


/*
 * @brief Set the Output Compare Register (OCR1A) value.
 *
 * This function set OCR1A value that determines when a compare match interrupt
 * is triggered or when the OC1A output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR1A.
 */
void TIMER1_SetCompare_A_Value( uint16 CompareAValue );


/*
 * @brief Get the OCR1A register value.
 *
 * This function get OCR1A value of TIMER1.
 *
 * @return (uint16) value of OCR1A register.
 */
uint16 TIMER1_GetCompare_A_Value( void );


/*
 * @brief Set the Output Compare Register (OCR1B) value.
 *
 * This function set OCR1B value that determines when a compare match interrupt
 * is triggered or when the OC1B output is toggled/cleared/set, depending on mode.
 *
 * @param CompareValue: Value to be set in OCR1B.
 */
void TIMER1_SetCompare_B_Value( uint16 CompareBValue );


/*
 * @brief Get the OCR1B register value.
 *
 * This function get OCR1B value of TIMER1.
 *
 * @return (uint16) value of OCR1B register.
 */
uint16 TIMER1_GetCompare_B_Value( void );


/*
 * @brief Set the Timer Counter Register (TCNT1) value.
 *
 * This function set TCNT1 value that determines the current count of TIMER1
 * and can be used to preload the timer for time offset adjustments.
 *
 * @param TimerValue: Value to be set in TCNT1.
 */
void TIMER1_SetTimerValue( uint16 TimerValue );


/*
 * @brief Get the current TIMER1 counter value.
 *
 * This function get TCNT1 value that determines the current count of TIMER1.
 *
 * @return (uint16) Current value of TCNT1 register.
 */
uint16 TIMER1_GetTimerValue( void );


/*
 * @brief Disable a specific TIMER1 interrupt.
 *
 * This function disables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to disable. This can be one of the following:
 *                     - TIMER1_OVF_ID   : Overflow Interrupt
 *                     - TIMER1_COMPA_ID : Compare Match A Interrupt
 *                     - TIMER1_COMPB_ID : Compare Match B Interrupt
 *                     - TIMER1_CAPT_ID  : Input Capture Event Interrupt
 */
void TIMER1_InterruptDisable( uint8 interrupt_id );


/*
 * @brief Enable a specific TIMER1 interrupt.
 *
 * This function enables either the overflow interrupt or compare match interrupt
 * based on the specified interrupt ID.
 *
 * @param interrupt_id: ID of the interrupt to enable. This can be one of the following:
 *                     - TIMER1_OVF_ID   : Overflow Interrupt
 *                     - TIMER1_COMPA_ID : Compare Match A Interrupt
 *                     - TIMER1_COMPB_ID : Compare Match B Interrupt
 *                     - TIMER1_CAPT_ID  : Input Capture Event Interrupt
 */
void TIMER1_InterruptEnable( uint8 interrupt_id );


/*
 * @brief Get the total time elapsed since TIMER1 started, in milliseconds.
 *
 * This function calculates time based on the current TCNT1 value,
 * the overflow counter,and the selected waveform generation mode.
 *
 * @return () Total elapsed time in milliseconds.
 *
 * @note Assumes no manual changes to TCNT1 after initialization.
 * @warning TIMER1_COUNT_MODE and any TIMER1 interrupt must be enabled
 * 			for this function to return correct values.
 */
uint64 TIMER1_GetTime_ms( void );


/*
 * @brief Reset TIMER1 counter and overflow counter to zero.
 *
 * This function resets both TCNT1 and `TIMER1_Counter` to start counting from the beginning.
 */
void TIMER1_RESET( void );


/*
 * @brief Calculate Timer1 interrupt timing parameters for a specified interval in milliseconds.
 *
 * This function determines how many Timer1 interrupts (overflows or compare matches)
 * are needed to generate an interrupt approximately every given number of milliseconds.
 * It also calculates the required starting value of TCNT1 to adjust for fractional timing.
 *
 * @param[in]  milliseconds:      Desired interrupt interval in milliseconds.
 * @param[out] requiredOverflows: Pointer to store the number of required interrupts.
 * @param[out] initialTCNT1:      Pointer to store the starting TCNT1 value to adjust for fraction.
 *
 * @note In your callback function, use a static or global counter to track the number of overflows.
 *       When the counter reaches requiredOverflows, reload TCNT1 with initialTCNT1
 *       and reset the counter to repeat the timing cycle.
 */
void TIMER1_Calc_ISR_Timing_ms( uint16 milliseconds, uint16 * requiredOverflows, uint16 * initialTCNT1 );


/*
 * @brief Sets a callback function for a specified Timer1 interrupt.
 *
 * This function sets a user-defined callback function to be called
 * when the specified Timer1 (OVF, COMPA, COMPB, or CAPT) interrupt occurs.
 *
 * @example TIMER1_SetCallback( TIMER1_OVF_ID , TIMER1_OVF_Interrupt_Function );
 *
 * @param interrupt_id: The interrupt ID (TIMER1_OVF_ID, TIMER1_COMP_ID).
 * @param CopyFuncPtr:  Pointer to the callback function. The function should have a
 * 						void return type and no parameters.
 */
void TIMER1_SetCallback( uint8 interrupt_id , void (*CopyFuncPtr)(void) );


/*
 * @brief Initializes the Input Capture Unit (ICU).
 *
 * This function configures the Input Capture Unit.
 * It sets up the noise canceler, the signal edge detection (rising or falling),
 * and enables the ICU interrupt if configured.
 * It configures the ICU registers according to the defined macros in TIMER1_config.h.
 *
 * @see TIMER1_config.h for configuration options.
 * @warning TIMER1 must be initialized before calling this function.
 */
void ICU_Init( void );


/*
 * @brief Sets the ICU to trigger on a falling edge.
 *
 * This function configures the Input Capture Unit to detect a falling edge as the trigger
 * for capturing the timer value.
 */
void ICU_FallingTriggerEdge( void );


/*
 * @brief Sets the ICU to trigger on a rising edge.
 *
 * This function configures the Input Capture Unit to detect a rising edge as the trigger
 * for capturing the timer value.
 */
void ICU_RisingTriggerEdge( void );


/*
 * @brief Clears the Input Capture Flag.
 *
 * This function clears the ICF1 flag in the TIFR register, which indicates that an
 * input capture event has occurred.
 */
void ICU_ClearFlag( void );


/*
 * @brief Reads the Input Capture Flag.
 *
 * This function checks whether the Input Capture Flag (ICF1) is set, indicating that
 * a capture event has occurred.
 *
 * @return 1 if the flag is set, 0 otherwise.
 */
uint8 ICU_GetFlag( void );


/*
 * @brief Retrieves the captured timer value.
 *
 * This function return the current value stored in the ICR1 register, which holds the
 * timer value at the time of the input capture event.
 *
 * @return (uint16) Captured value from the ICR1 register.
 */
uint16 ICU_GetICUvalue( void );


#endif /* TIMER1_H_ */

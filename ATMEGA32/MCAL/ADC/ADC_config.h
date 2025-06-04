/****************************************************************************
 * @file    ADC_config.h
 * @author  Boles Medhat
 * @brief   ADC Configuration Header File - AVR ATmega32
 * @version 2.0
 * @date    [2024-06-16]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This file contains configuration options for the ADC (Analog to Digital Converter)
 * module in ATmega32. It allows for setting up various parameters such as
 * selecting voltage reference, adjustment mode, interrupt behavior, trigger mode,
 * trigger source, timeout, and prescaler settings.
 *
 * @note
 * - All available choices (e.g., selecting voltage reference, adjustment mode) are
 *   defined in `ADC_def.h` and explained with comments there.
 * - Make sure `F_CPU` is defined properly; defaults to 8MHz if not set.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include "ADC_def.h"


#ifndef F_CPU
    #define F_CPU 8000000UL
    #warning "F_CPU not defined! Assuming 8MHz."
#endif


/*Set the Voltage Reference
 * choose between:
 * 1. ADC_VOLTAGE_REF_AREF
 * 2. ADC_VOLTAGE_REF_AVCC				<--the most used
 * 3. ADC_VOLTAGE_REF_2_56V
 */
#define ADC_VOLTAGE_REF					ADC_VOLTAGE_REF_AVCC


/*Set ADC ADJUST Mode
 * choose between:
 * 1. ADC_RIGHT_ADJUSTED				<--the most used
 * 2. ADC_LEFT_ADJUSTED
 */
#define ADC_ADJUSTMENT					ADC_RIGHT_ADJUSTED


/*Set ADC Interrupt Status
 * choose between:
 * 1. ADC_INT_DISABLE					<--the most used
 * 2. ADC_INT_ENABLE
 */
#define ADC_INT_STATUS					ADC_INT_DISABLE


/*Set ADC Auto Trigger Enable
 * choose between:
 * 1. ADC_MODE_SINGLE_CONVERSION		<--the most used
 * 2. ADC_MODE_AUTO_TRIGGER
 */
#define ADC_MODE						ADC_MODE_SINGLE_CONVERSION


/*Set ADC AUTO TRIGGER Source
 * choose between:
 * 1. ADC_ATS_FREE_RUNNING_msk			<--the most used
 * 2. ADC_ATS_ANALOG_COMP_msk
 * 3. ADC_ATS_EXTI0_msk
 * 4. ADC_ATS_TIMER0_COMP_msk
 * 5. ADC_ATS_TIMER0_OVF_msk
 * 6. ADC_ATS_TIMER1_COMP_msk
 * 7. ADC_ATS_TIMER1_OVF_msk
 * 8. ADC_ATS_TIMER1_CAPT_msk
 */
#define ADC_AUTO_TRIG_SRC				ADC_ATS_FREE_RUNNING_msk


/*Max Time to Wait for the Conversion to Finish
 * choose between:
 * 1. ADC_WAIT_FOREVER
 * 2. Any timeout value in CPU cycles (e.g., 150 for short wait)
 */
#define  ADC_COUNTOUT					150



/* Automatically select the smallest ADC prescaler that keeps ADC frequency within valid range (50kHz–200kHz) */
#if		F_CPU/2 <= ADC_FREQUENCY_MAX && F_CPU/2 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_2_msk

#elif	F_CPU/4 <= ADC_FREQUENCY_MAX && F_CPU/4 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_4_msk

#elif	F_CPU/8 <= ADC_FREQUENCY_MAX && F_CPU/8 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_8_msk

#elif	F_CPU/16 <= ADC_FREQUENCY_MAX && F_CPU/16 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_16_msk

#elif	F_CPU/32 <= ADC_FREQUENCY_MAX && F_CPU/32 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_32_msk

#elif	F_CPU/64 <= ADC_FREQUENCY_MAX && F_CPU/64 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_64_msk

#elif	F_CPU/128 <= ADC_FREQUENCY_MAX && F_CPU/128 >= ADC_FREQUENCY_MIN

    #define ADC_PRESCALER				ADC_PRESCALER_128_msk

#else
    #error "No valid ADC_PRESCALER found!"
#endif


#endif /* ADC_CONFIG_H_ */

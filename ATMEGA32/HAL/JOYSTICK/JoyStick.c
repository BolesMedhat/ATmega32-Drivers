/****************************************************************************
 * @file    JoyStick.c
 * @author  Boles Medhat
 * @brief   Joystick Driver Source File
 * @version 1.0
 * @date    [2024-09-09]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This driver provides a complete abstraction for interfacing with a 2-axis
 * analog joystick and button using the ADC and digital I/O peripherals.
 * It supports dead zone filtering and rescaling of analog values to signed
 * integer ranges, as well as direction detection based on X and Y positions.
 *
 * @note
 * - ⚠️ IMPORTANT: You must initialize the ADC module **before** using this driver.
 *   			   The joystick driver assumes the ADC is configured for 10-bit readings.
 * - Requires `JoyStick_config.h` for macro-based configuration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ****************************************************************************/


#include "JoyStick.h"





/*
 * @brief Initializes the joystick by configuring the ADC and button.
 *
 * This function configures the joystick button pin as an input with an internal pull-up resistor.
 */
void JOYSTICK_InitButton( void )
{
	/* Initialization the Joystick Button Pin Direction as Input with an internal pull-up resistor */
	DIO_SetPinDirection( JOYSTICK_BUTTON_PORT , JOYSTICK_BUTTON_PIN , INPUT_PULLUP );
}





/*
 * @brief Reads and processes the joystick's X-axis value.
 *
 * This function reads the raw ADC value for the X-axis, applies a dead zone filter, and maps
 * the value to a defined range. The function returns 0 if the joystick is within the dead zone.
 * the full Range is -JOYSTICK_X_ABS_MAX to JOYSTICK_X_ABS_MAX.
 *
 * @return: The processed X-axis value.
 */
sint16 JOYSTICK_Read_X_Axis( void )
{

	/* Read the Raw ADC Value for the X-axis */
	uint16 Raw_X_Value = ADC_Read_10_Bits( JOYSTICK_X_AXIS_CHANNEL );

	/* Check if the X Value is Outside the Dead Zone */
	if		( Raw_X_Value >= JOYSTICK_X_NEUTRAL + JOYSTICK_DEAD_ZONE )
	{
		/* Return the Value Mapped to the Positive Range */
		return MAPPING_RescaleValue( Raw_X_Value , (JOYSTICK_X_NEUTRAL + JOYSTICK_DEAD_ZONE) , 1023 , 0 , JOYSTICK_X_ABS_MAX );
	}
	else if	( Raw_X_Value <= JOYSTICK_X_NEUTRAL - JOYSTICK_DEAD_ZONE )
	{
		/* Return the Value Mapped to the Negative Range */
		return MAPPING_RescaleValue( Raw_X_Value , 0 , (JOYSTICK_X_NEUTRAL - JOYSTICK_DEAD_ZONE) , (-1 * JOYSTICK_X_ABS_MAX) , 0 );
	}
	else
	{
		/* Return 0 if the value is Within the Dead Zone */
		return 0;
	}
}





/*
 * @brief Reads and processes the joystick's Y-axis value.
 *
 * This function reads the raw ADC value for the Y-axis, applies a dead zone filter, and maps
 * the value to a defined range. The function returns 0 if the joystick is within the dead zone.
 * the full Range is -JOYSTICK_Y_ABS_MAX to JOYSTICK_Y_ABS_MAX.
 *
 * @return: The processed Y-axis value.
 */
sint16 JOYSTICK_Read_Y_Axis( void )
{

	/* Read the Raw ADC Value for the Y-axis */
	uint16 Raw_Y_Value = ADC_Read_10_Bits( JOYSTICK_Y_AXIS_CHANNEL );

	/* Check if the Y Value is Outside the Dead Zone */
	if		( Raw_Y_Value >= JOYSTICK_Y_NEUTRAL + JOYSTICK_DEAD_ZONE )
	{
		/* Return the Value Mapped to the Positive Range */
		return MAPPING_RescaleValue( Raw_Y_Value , (JOYSTICK_Y_NEUTRAL + JOYSTICK_DEAD_ZONE) , 1023 , 0 , JOYSTICK_Y_ABS_MAX );
	}
	else if	( Raw_Y_Value <= JOYSTICK_Y_NEUTRAL - JOYSTICK_DEAD_ZONE )
	{
		/* Return the Value Mapped to the Negative Range */
		return MAPPING_RescaleValue( Raw_Y_Value , 0 , (JOYSTICK_Y_NEUTRAL - JOYSTICK_DEAD_ZONE) , (-1 * JOYSTICK_Y_ABS_MAX) , 0 );
	}
	else
	{
		/* Return 0 if the value is Within the Dead Zone */
		return 0;
	}
}





/*
 * @brief Reads the state of the joystick button.
 *
 * This function returns the state of the joystick button.
 *
 * @return: The button state; 1 if pressed, 0 if not pressed.
 */
uint8 JOYSTICK_ReadButton( void )
{
	/* Return the Inverted Pin Value Because the Pin Uses an Internal Pull-up */
	return (! DIO_GetPinValue( JOYSTICK_BUTTON_PORT , JOYSTICK_BUTTON_PIN ));
}





/*
 * @brief Determines the direction of the joystick based on its X and Y-axis values.
 *
 * This function reads the raw ADC values for both the X and Y axes of the joystick. It then
 * compares these values against the joystick's center position and dead zone to determine
 * the direction in which the joystick is currently pushed.
 *
 * @return: The direction of the joystick:
 *         - JOYSTICK_DIRECTION_UP if the joystick is pushed up,
 *         - JOYSTICK_DIRECTION_DOWN if the joystick is pushed down,
 *         - JOYSTICK_DIRECTION_RIGHT if the joystick is pushed right,
 *         - JOYSTICK_DIRECTION_LEFT if the joystick is pushed left,
 *         - JOYSTICK_DIRECTION_CENTER if the joystick is within the dead zone.
 */
uint8 JOYSTICK_GetDirection( void )
{

	/* Read the Raw ADC Values for the X and Y Axes */
	uint16 Raw_X_Value = ADC_Read_10_Bits( JOYSTICK_X_AXIS_CHANNEL );
	uint16 Raw_Y_Value = ADC_Read_10_Bits( JOYSTICK_Y_AXIS_CHANNEL );


	/* Determine the Direction based on the X-axis Value */
	if		( Raw_Y_Value >= JOYSTICK_X_NEUTRAL +  JOYSTICK_DEAD_ZONE )
	{
		/* Return that the Joystick is Pushed Up */
		return JOYSTICK_DIRECTION_DOWN;
	}
	else if	( Raw_Y_Value <= JOYSTICK_X_NEUTRAL - JOYSTICK_DEAD_ZONE )
	{
		/* Return that the Joystick is Pushed Down */
		return JOYSTICK_DIRECTION_UP;
	}

	/* Determine the Direction based on the Y-axis Value */
	else if	( Raw_X_Value >= JOYSTICK_Y_NEUTRAL +  JOYSTICK_DEAD_ZONE )
	{
		/* Return that the Joystick is Pushed Right */
		return JOYSTICK_DIRECTION_RIGHT;
	}
	else if	( Raw_X_Value <= JOYSTICK_Y_NEUTRAL - JOYSTICK_DEAD_ZONE )
	{
		/* Return that the Joystick is Pushed Left */
		return JOYSTICK_DIRECTION_LEFT;
	}

	/* Joystick is Within the Dead Zone */
	else
	{
		/* Return that the Joystick is in the Center */
		return JOYSTICK_DIRECTION_CENTER;
	}
}


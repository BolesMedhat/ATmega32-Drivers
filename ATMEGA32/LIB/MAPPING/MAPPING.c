/****************************************************************************
 * @file    MAPPING.c
 * @author  Boles Medhat
 * @brief   Value Mapping Module - Linear Range Scaling
 * @version 1.0
 * @date    [2024-09-11]
 * @license MIT License Copyright (c) 2024 Boles Medhat
 *
 * @details
 * This module provides a utility function to map a signed 16-bit integer from one
 * numerical range to another using a linear transformation. It is useful in
 * embedded applications for signal scaling, sensor data normalization, and control
 * system calibration.
 *
 *
 * @contact
 * LinkedIn : https://www.linkedin.com/in/boles-medhat
 * GitHub   : https://github.com/BolesMedhat
 *
 ******************************************************************************/


#include "MAPPING.h"


/*
 * @brief Maps a value from one range to another.
 *
 * This function takes an input value within a specified old range
 * (OldMin to OldMax) and maps it to a new range (NewMin to NewMax).
 * It performs a linear transformation based on the provided ranges.
 *
 * @param Value:   The input value to be mapped.
 * @param OldMin:  The lower bound of the old range.
 * @param OldMax:  The upper bound of the old range.
 * @param NewMin:  The lower bound of the new range.
 * @param NewMax:  The upper bound of the new range.
 *
 * @return:        The mapped value in the new range. If OldMin is equal to OldMax,
 *                the function returns zero to avoid division by zero.
 */
sint16 MAPPING_RescaleValue( sint16 Value ,  sint16 OldMin ,  sint16 OldMax ,  sint16 NewMin ,  sint16 NewMax )
{


	/* Check if the Old Range is Invalid (OldMin == OldMax), Which Would Cause Division by Zero */
	if( OldMin == OldMax )
	{
		/* Return 0 as a Default to Avoid Division by Zero */
		return 0;
	}
	else
	{
		return ( Value - OldMin ) * ( NewMax - NewMin ) / ( OldMax - OldMin ) + NewMin ;
	}
}

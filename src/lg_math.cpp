/*******************************************************************************
* File:		lg_math.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		7 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../include/lg_math.h"

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Abs
*******************************************************************************/
float Abs (float fValue) {

	// If negative
	if (fValue < 0) {

		// Return positive
		return (fValue * -1);

	// Positive
	} else {

		// Return positive
		return (fValue);
	}
}

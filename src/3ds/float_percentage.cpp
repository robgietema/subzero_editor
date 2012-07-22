/*******************************************************************************
* File:		float_percentage.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/float_percentage.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			FLOAT_PERCENTAGE ()
*******************************************************************************/
FLOAT_PERCENTAGE::FLOAT_PERCENTAGE ()
{
	// Initialize percentage
	FLOAT_PERCENTAGE::fPercentage = 1;
}

/*******************************************************************************
* Name:			~FLOAT_PERCENTAGE ()
*******************************************************************************/
FLOAT_PERCENTAGE::~FLOAT_PERCENTAGE ()
{

}
		
/*******************************************************************************
* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
*******************************************************************************/
int FLOAT_PERCENTAGE::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading FLOAT_PERCENTAGE chunk");

	// Check chunk length
	if (iNrOfBytes < 2)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	FLOAT_PERCENTAGE::fPercentage = GetFloat (bp3DSData);
	
	// Check percentage
	if (FLOAT_PERCENTAGE::fPercentage > 1)
	{
		// Set to default
		FLOAT_PERCENTAGE::fPercentage = 1;
		
		// Print status
		VerbosePrintf ("Invalid percentage, reset to 1.0");
	}

	// Print status
	VerbosePrintf ("Percentage: %f", FLOAT_PERCENTAGE::fPercentage);

	// Print status
	VerbosePrintf ("End reading FLOAT_PERCENTAGE chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetPercentage ()
*******************************************************************************/
int FLOAT_PERCENTAGE::GetPercentage (float* fPercentage)
{
	// Set return value
	*fPercentage = FLOAT_PERCENTAGE::fPercentage;
	
	// Return no error
	return (0);
}

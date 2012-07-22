/*******************************************************************************
* File:		light_off.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/light_off.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			LIGHT_OFF ()                                                   *
*******************************************************************************/
LIGHT_OFF::LIGHT_OFF ()
{
	// Initialize status
	LIGHT_OFF::bLightOff = false;
}

/*******************************************************************************
* Name:			~LIGHT_OFF ()                                                  *
*******************************************************************************/
LIGHT_OFF::~LIGHT_OFF ()
{

}

/*******************************************************************************
* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)                      *
*******************************************************************************/
int LIGHT_OFF::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading LIGHT_OFF chunk");

	// Check chunk length
	if (iNrOfBytes < 1)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get status from buffer
	if (bp3DSData[0] == 0)
	{
		LIGHT_OFF::bLightOff = false;
	}
	else
	{
		LIGHT_OFF::bLightOff = true;
	}
	
	// Print status
	VerbosePrintf ("End reading LIGHT_OFF chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetStatus (bool* bStatus)                                      *
*******************************************************************************/
int LIGHT_OFF::GetStatus (bool* bStatus)
{
	// Set return value
	*bStatus = LIGHT_OFF::bLightOff;
	
	// Return no error
	return (0);
}

/*******************************************************************************
* File:		master_scale.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/master_scale.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MASTER_SCALE ()
*******************************************************************************/
MASTER_SCALE::MASTER_SCALE ()
{
	// Initialize scale
	MASTER_SCALE::fScale = 1;
}

/*******************************************************************************
* Name:			~MASTER_SCALE ()
*******************************************************************************/
MASTER_SCALE::~MASTER_SCALE ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MASTER_SCALE::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading MASTER_SCALE chunk");

	// Check chunk length
	if (iNrOfBytes < 4)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	MASTER_SCALE::fScale = GetFloat (bp3DSData);
	
	// Print status
	VerbosePrintf ("Scale: %f", MASTER_SCALE::fScale);

	// Print status
	VerbosePrintf ("End reading MASTER_SCALE chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetScale ()
*******************************************************************************/
int MASTER_SCALE::GetScale (float* fScale)
{
	// Set return value
	*fScale = MASTER_SCALE::fScale;
	
	// Return no error
	return (0);
}

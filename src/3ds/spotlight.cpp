/*******************************************************************************
* File:		spotlight.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/spotlight.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			SPOTLIGHT ()
*******************************************************************************/
SPOTLIGHT::SPOTLIGHT ()
{
	// Initialize member variables
	SPOTLIGHT::fTargetX = 0;
	SPOTLIGHT::fTargetY = 0;
	SPOTLIGHT::fTargetZ = 0;
	SPOTLIGHT::fHotSpot = 0;
	SPOTLIGHT::fFalloff = 0;
	SPOTLIGHT::bUsed = false;
}

/*******************************************************************************
* Name:			~SPOTLIGHT ()
*******************************************************************************/
SPOTLIGHT::~SPOTLIGHT ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int SPOTLIGHT::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading SPOTLIGHT chunk");

	// Check chunk length
	if (iNrOfBytes < (5 * 4))
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get spotlight data from chunk
	SPOTLIGHT::fTargetX = GetFloat (bp3DSData);
	SPOTLIGHT::fTargetY = GetFloat (bp3DSData + 4);
	SPOTLIGHT::fTargetZ = GetFloat (bp3DSData + 8);
	SPOTLIGHT::fHotSpot = GetFloat (bp3DSData + 12);
	SPOTLIGHT::fFalloff = GetFloat (bp3DSData + 16);
	
	// Set spotlight to used	
	SPOTLIGHT::bUsed = true;
	
	// Print status
	VerbosePrintf ("End reading SPOTLIGHT chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:		Used ()
*******************************************************************************/
bool SPOTLIGHT::Used (void)
{
	// Return used
	return (SPOTLIGHT::bUsed);
}

/*******************************************************************************
* Name:			GetSpotLight ()
*******************************************************************************/
int SPOTLIGHT::GetSpotLight (float* fTargetX, float* fTargetY, float* fTargetZ,
					float* fHotSpot, float* fFalloff)
{
	// Set return values
	*fTargetX = SPOTLIGHT::fTargetX;
	*fTargetY = SPOTLIGHT::fTargetY;
	*fTargetZ = SPOTLIGHT::fTargetZ;
	*fHotSpot = SPOTLIGHT::fHotSpot;
	*fFalloff = SPOTLIGHT::fFalloff;

	// Return no error
	return (0);
}

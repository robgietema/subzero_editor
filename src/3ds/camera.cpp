/*******************************************************************************
* File:		camera.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/camera.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			CAMERA ()
*******************************************************************************/
CAMERA::CAMERA() {
}

/*******************************************************************************
* Name:			~CAMERA ()
*******************************************************************************/
CAMERA::~CAMERA() {
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int CAMERA::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading CAMERA chunk");

	// Check chunk length
	if (iNrOfBytes < (8 * 4))
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get camera data from chunk
	CAMERA::fX 		 = GetFloat (bp3DSData);
	CAMERA::fY 		 = GetFloat (bp3DSData + 4);
	CAMERA::fZ 		 = GetFloat (bp3DSData + 8);
	CAMERA::fTargetX = GetFloat (bp3DSData + 12);
	CAMERA::fTargetY = GetFloat (bp3DSData + 16);
	CAMERA::fTargetZ = GetFloat (bp3DSData + 20);
	CAMERA::fBank 	 = GetFloat (bp3DSData + 24);
	CAMERA::fLens 	 = GetFloat (bp3DSData + 28);
	
	// Print status
	VerbosePrintf ("Camera coordinates (%f, %f, %f)", CAMERA::fX, CAMERA::fY, CAMERA::fZ);
	
	// Print status
	VerbosePrintf ("End reading CAMERA chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* File:		mat_map_rotation.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_map_rotation.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_MAP_ROTATION ()
*******************************************************************************/
MAT_MAP_ROTATION::MAT_MAP_ROTATION ()
{

}

/*******************************************************************************
* Name:			~MAT_MAP_ROTATION ()
*******************************************************************************/
MAT_MAP_ROTATION::~MAT_MAP_ROTATION ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_MAP_ROTATION::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Print status
	VerbosePrintf ("Begin reading MAT_MAP_ROTATION chunk");

	// Get version from buffer
	MAT_MAP_ROTATION::fRotation = GetFloat (bp3DSData);
	
	// Print status
	VerbosePrintf ("Map blur: %f", MAT_MAP_ROTATION::fRotation);
		
	// Print status
	VerbosePrintf ("End reading MAT_MAP_ROTATION chunk");

	// Return no error
	return (0);
}

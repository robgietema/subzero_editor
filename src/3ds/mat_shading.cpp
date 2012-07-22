/*******************************************************************************
* File:		mat_shading.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_shading.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_SHADING ()
*******************************************************************************/
MAT_SHADING::MAT_SHADING ()
{
	// Initialize display method
	MAT_SHADING::iDisplayMethod = WIREFRAME;
}

/*******************************************************************************
* Name:			~MAT_SHADING ()
*******************************************************************************/
MAT_SHADING::~MAT_SHADING ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_SHADING::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading MAT_SHADING chunk");

	// Check chunk length
	if (iNrOfBytes < 2)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	MAT_SHADING::iDisplayMethod = GetShort (bp3DSData);
	
	// Check displaymode
	if (MAT_SHADING::iDisplayMethod > 4)
	{
		// Set to default
		MAT_SHADING::iDisplayMethod = 0;
		
		// Print status
		VerbosePrintf ("Invalid displaymode, reset to wireframe");
	}

	// Print status
	VerbosePrintf ("Shading: %d", MAT_SHADING::iDisplayMethod);

	// Print status
	VerbosePrintf ("End reading MAT_SHADING chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetDisplayMethod ()
*******************************************************************************/
int MAT_SHADING::GetDisplayMethod (int* iDisplayMethod)
{
	// Set return value
	*iDisplayMethod = MAT_SHADING::iDisplayMethod;
	
	// Return no error
	return (0);
}

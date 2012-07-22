/*******************************************************************************
* File:		mat_bump_display_per.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_bump_display_per.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_BUMP_DISPLAY_PER ()
*******************************************************************************/
MAT_BUMP_DISPLAY_PER::MAT_BUMP_DISPLAY_PER ()
{
	// Initalize percentage
	MAT_BUMP_DISPLAY_PER::iPercentage = 100;
}

/*******************************************************************************
* Name:			~MAT_BUMP_DISPLAY_PER ()
*******************************************************************************/
MAT_BUMP_DISPLAY_PER::~MAT_BUMP_DISPLAY_PER ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_BUMP_DISPLAY_PER::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading MAT_BUMP_DISPLAY_PER chunk");

	// Check chunk length
	if (iNrOfBytes < 2)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	MAT_BUMP_DISPLAY_PER::iPercentage = GetShort (bp3DSData);
	
	// Check displaymode
	if (MAT_BUMP_DISPLAY_PER::iPercentage > 100)
	{
		// Set to default
		MAT_BUMP_DISPLAY_PER::iPercentage = 100;
		
		// Print status
		VerbosePrintf ("Invalid percentage, reset to 100");
	}

	// Print status
	VerbosePrintf ("Percentage: %d", MAT_BUMP_DISPLAY_PER::iPercentage);

	// Print status
	VerbosePrintf ("End reading MAT_BUMP_DISPLAY_PER chunk");

	// Return no error
	return (0);
}

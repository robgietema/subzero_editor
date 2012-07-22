/*******************************************************************************
* File:		int_percentage.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/int_percentage.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			INT_PERCENTAGE ()
*******************************************************************************/
INT_PERCENTAGE::INT_PERCENTAGE ()
{
	// Initalize percentage
	INT_PERCENTAGE::iPercentage = 100;
}

/*******************************************************************************
* Name:			~INT_PERCENTAGE ()
*******************************************************************************/
INT_PERCENTAGE::~INT_PERCENTAGE ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int INT_PERCENTAGE::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading INT_PERCENTAGE chunk");

	// Check chunk length
	if (iNrOfBytes < 2)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	INT_PERCENTAGE::iPercentage = GetShort (bp3DSData);
	
	// Check displaymode
	if (INT_PERCENTAGE::iPercentage > 100)
	{
		// Set to default
		INT_PERCENTAGE::iPercentage = 100;
		
		// Print status
		VerbosePrintf ("Invalid percentage, reset to 100");
	}

	// Print status
	VerbosePrintf ("Percentage: %d", INT_PERCENTAGE::iPercentage);

	// Print status
	VerbosePrintf ("End reading INT_PERCENTAGE chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetPercentage ()
*******************************************************************************/
int INT_PERCENTAGE::GetPercentage (int* iPercentage)
{
	// Set return value
	*iPercentage = INT_PERCENTAGE::iPercentage;
	
	// Return no error
	return (0);
}

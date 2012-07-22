/*******************************************************************************
* File:		mat_name.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_name.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_NAME ()
*******************************************************************************/
MAT_NAME::MAT_NAME ()
{
	// Initalize material name
	strcpy (MAT_NAME::acName, "");
}

/*******************************************************************************
* Name:			~MAT_NAME ()
*******************************************************************************/
MAT_NAME::~MAT_NAME ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_NAME::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading MAT_NAME chunk");

	// Check chunk length
	if (iNrOfBytes < 1)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get name from buffer
	GetString (bp3DSData, MAT_NAME::acName);

	// Print status
	VerbosePrintf ("Materialname: %s", MAT_NAME::acName);

	// Print status
	VerbosePrintf ("End reading MAT_NAME chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetMatName ()
*******************************************************************************/
int MAT_NAME::GetMatName (char acMatName[256])
{
	// Check for empty string
	if (strlen (MAT_NAME::acName) == 0)
	{
		// Set error
		ErrorPrintf ("Invalid material name");
		
		// return error
		return (-1);
	}
	
	// Set return value
	strcpy (acMatName, MAT_NAME::acName);
	
	// Return no error
	return (0);
}


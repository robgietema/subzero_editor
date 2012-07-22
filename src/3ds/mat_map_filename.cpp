/*******************************************************************************
* File:		mat_map_filename.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_map_filename.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_MAP_FILENAME ()
*******************************************************************************/
MAT_MAP_FILENAME::MAT_MAP_FILENAME ()
{

}

/*******************************************************************************
* Name:			~MAT_MAP_FILENAME ()
*******************************************************************************/
MAT_MAP_FILENAME::~MAT_MAP_FILENAME ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_MAP_FILENAME::Read3DS (int iNrOfBytes, byte* bp3DSData) {
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Print status
	VerbosePrintf ("Begin reading MAT_MAP_FILENAME chunk");

	// Get data from buffer
	GetString (bp3DSData, MAT_MAP_FILENAME::acFilename);
	
	// Print status
	VerbosePrintf ("Map filename: %s", MAT_MAP_FILENAME::acFilename);
		
	// Print status
	VerbosePrintf ("End reading MAT_MAP_FILENAME chunk");

	// Return no error
	return (0);
}

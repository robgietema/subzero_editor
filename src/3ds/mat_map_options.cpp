/*******************************************************************************
* File:		mat_map_options.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_map_options.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_MAP_OPTIONS ()
*******************************************************************************/
MAT_MAP_OPTIONS::MAT_MAP_OPTIONS ()
{

}

/*******************************************************************************
* Name:			~MAT_MAP_OPTIONS ()
*******************************************************************************/
MAT_MAP_OPTIONS::~MAT_MAP_OPTIONS ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_MAP_OPTIONS::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk

	// Print status
	VerbosePrintf ("Begin reading MAT_MAP_OPTIONS chunk");

	// Get version from buffer
	MAT_MAP_OPTIONS::iOptions = GetShort (bp3DSData);
	
	// Print status
	VerbosePrintf ("Map options: %d", MAT_MAP_OPTIONS::iOptions);
		
	// Print status
	VerbosePrintf ("End reading MAT_MAP_OPTIONS chunk");

	// Return no error
	return (0);
}

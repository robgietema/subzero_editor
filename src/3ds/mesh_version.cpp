/*******************************************************************************
* File:		mesh_version.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mesh_version.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MDATA ()
*******************************************************************************/
MESH_VERSION::MESH_VERSION ()
{
	// Initialize version
	MESH_VERSION::lVersion = 0;
}

/*******************************************************************************
* Name:			~MDATA ()
*******************************************************************************/
MESH_VERSION::~MESH_VERSION ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MESH_VERSION::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading MESH_VERSION chunk");

	// Check chunk length
	if (iNrOfBytes < 4)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	MESH_VERSION::lVersion = GetInt (bp3DSData);

	// Print status
	VerbosePrintf ("Version: %d", MESH_VERSION::lVersion);

	// Print status
	VerbosePrintf ("End reading MESH_VERSION chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetVersion ()
*******************************************************************************/
int MESH_VERSION::GetVersion (long* lVersion)
{
	// Set return values
	*lVersion = MESH_VERSION::lVersion;
	
	// Return no error
	return (0);
}

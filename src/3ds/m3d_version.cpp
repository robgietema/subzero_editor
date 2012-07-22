/*******************************************************************************
* File:		m3d_version.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/m3d_version.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			M3D_VERSION ()
*******************************************************************************/
M3D_VERSION::M3D_VERSION()
{
	// Initialize version
	M3D_VERSION::lVersion = 0;
}

/*******************************************************************************
* Name:			~M3D_VERSION ()
*******************************************************************************/
M3D_VERSION::~M3D_VERSION()
{

}

/*******************************************************************************
* Name:			Read3DS (int iNrOfBytes, byte* bp3DSData)
*******************************************************************************/
int M3D_VERSION::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	// Print status
	VerbosePrintf ("Begin reading M3D_VERSION chunk");

	// Check chunk length
	if (iNrOfBytes < 4)
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get version from buffer
	M3D_VERSION::lVersion = GetInt (bp3DSData);
	
	// Print status
	VerbosePrintf ("3DS file-version: %d",lVersion);

	// Print status
	VerbosePrintf ("End reading M3D_VERSION chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
*
* Name:			GetVersion (long* lVersion)
* Function:		This function return the version number.
* Pre:          -
* Post:         lVersion contains the version number.
*
*******************************************************************************/
int M3D_VERSION::GetVersion (long* lVersion)
{
	// Set return value
	*lVersion = M3D_VERSION::lVersion;

	// Return no error
	return (0);
}

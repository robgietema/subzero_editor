/*******************************************************************************
* File:		named_object.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/named_object.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			NAMED_OBJECT ()
*******************************************************************************/
NAMED_OBJECT::NAMED_OBJECT()
{
	// Initialize member variables
	NAMED_OBJECT::iNrOfNTriObjects	= 0;
	NAMED_OBJECT::iNrOfLights 		= 0;
	NAMED_OBJECT::iNrOfCameras 		= 0;
	NAMED_OBJECT::cCamera			= NULL;
	NAMED_OBJECT::lLight			= NULL;
	NAMED_OBJECT::oNTriObject		= NULL;
}

/*******************************************************************************
* Name:			~NAMED_OBJECT ()
*******************************************************************************/
NAMED_OBJECT::~NAMED_OBJECT()
{
	// If allocated
	if (NAMED_OBJECT::oNTriObject) {

		// Delete
		delete []NAMED_OBJECT::oNTriObject;
	}

	// If allocated
	if (NAMED_OBJECT::lLight) {

		// Delete
		delete []NAMED_OBJECT::lLight;
	}

	// If allocated
	if (NAMED_OBJECT::cCamera) {

		// Delete
		delete []cCamera;
	}
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int NAMED_OBJECT::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;		// Pointer to current byte in chunk
	int iChunkID;				// Chunk id
	long lChunkLength;			// Chunk length
	int iNTriObjectCount = 0;	// Number of n_tri_objects
	int iCameraCount = 0;		// Number of cameras
	int iLightCount = 0;		// Number of lights

	// Print status
	VerbosePrintf ("Begin reading NAMED_OBJECT chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}
	
	// Get name from buffer
	GetString (bp3DSData, NAMED_OBJECT::acName);

	// Print status
	VerbosePrintf ("Objectname: %s", NAMED_OBJECT::acName);
	
	// Set current byte
	iCurrentByte += (strlen (NAMED_OBJECT::acName) + 1);

	// Count number of matentries and named objects and lights
	while (iCurrentByte < iNrOfBytes)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;
		
		// Get chunk length
		lChunkLength = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;
		
		// Check if length is correct
		if (lChunkLength > (iNrOfBytes - iCurrentByte + CHUNKHEADER_SIZE))
		{
			// Set error chunk size invalid
			ErrorPrintf ("Chunk size invalid");

			// Return error
			return (-1);
		}
		
		// Check chunk id
		switch (iChunkID)
		{
			case N_TRI_OBJECT_CHUNK:
				// Increase n_tri_object count
				iNTriObjectCount++;				
				break;
			case CAMERA_CHUNK:
				// Increase camera count
				iCameraCount++;
				break;
			case LIGHT_CHUNK:
				// Increase light count
				iLightCount++;
				break;
			default:
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Check if > 0
	if (iNTriObjectCount > 0) {

		// Allocate n_tri_object list
		oNTriObject = new N_TRI_OBJECT[iNTriObjectCount];
	}

	// Check if count > 0
	if (iCameraCount > 0) {

		// Allocate camera list
		cCamera = new CAMERA[iCameraCount];
	}

	// Check if > 0
	if (iLightCount > 0) {

		// Allocate light list
		lLight = new LIGHT[iLightCount];
	}

	// Reset current byte
	iCurrentByte = strlen (NAMED_OBJECT::acName) + 1;

	// Get chunks from NAMED_OBJECT chunk
	while (iCurrentByte < iNrOfBytes)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;
		
		// Get chunk length
		lChunkLength = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;
		
		// Check if length is correct
		if (lChunkLength > (iNrOfBytes - iCurrentByte + CHUNKHEADER_SIZE))
		{
			// Set error chunk size invalid
			ErrorPrintf ("Chunk size invalid");

			// Return error
			return (-1);
		}
		
		// Check chunk id
		switch (iChunkID)
		{
			case N_TRI_OBJECT_CHUNK:
				// Print status
				VerbosePrintf ("N_TRI_OBJECT chunk found");

				// Read N_TRI_OBJECT chunk
				if (NAMED_OBJECT::oNTriObject[iNrOfNTriObjects].Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}
				
				// Increase number of n_tri_objects
				iNrOfNTriObjects++;
				break;
			case CAMERA_CHUNK:
				// Print status
				VerbosePrintf ("CAMERA chunk found");

				// Read N_TRI_OBJECT chunk
				if (NAMED_OBJECT::cCamera[iNrOfCameras].Read3DS 
					(lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}
				
				// Increase number of cameras
				iNrOfCameras++;
				break;
			case LIGHT_CHUNK:
				// Print status
				VerbosePrintf ("LIGHT chunk found");

				// Read LIGHT chunk
				if (NAMED_OBJECT::lLight[iNrOfLights].Read3DS 
					(lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}
				
				// Increase number of lights
				iNrOfLights++;
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in NAMED_OBJECT: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading NAMED_OBJECT chunk");

	// Return no error
	return (0);
}

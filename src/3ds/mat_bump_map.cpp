/*******************************************************************************
* File:		mat_bump_map.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		2 January 2004
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_bump_map.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_BUMP_MAP ()
*******************************************************************************/
MAT_BUMP_MAP::MAT_BUMP_MAP ()
{

}

/*******************************************************************************
* Name:			~MAT_BUMP_MAP ()
*******************************************************************************/
MAT_BUMP_MAP::~MAT_BUMP_MAP ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_BUMP_MAP::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading MAT_BUMP_MAP chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from MAT_SHININESS chunk
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
			case INT_PERCENTAGE_CHUNK:
				// Print status
				VerbosePrintf ("INT_PERCENTAGE chunk found");

				// Read INT_PERCENTAGE chunk
				if (MAT_BUMP_MAP::pIntPercentage.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_MAP_BLUR_CHUNK:
				// Print status
				VerbosePrintf ("MAT_MAP_BLUR chunk found");

				// Read MAT_MAP_BLUR chunk
				if (MAT_BUMP_MAP::bBlur.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_MAP_FILENAME_CHUNK:
				// Print status
				VerbosePrintf ("MAT_MAP_FILENAME chunk found");

				// Read MAT_MAP_FILENAME chunk
				if (MAT_BUMP_MAP::fFilename.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_MAP_OPTIONS_CHUNK:
				// Print status
				VerbosePrintf ("MAT_MAP_OPTIONS chunk found");

				// Read MAT_MAP_OPTIONS chunk
				if (MAT_BUMP_MAP::oOptions.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}
				break;
			case MAT_MAP_ROTATION_CHUNK:
				// Print status
				VerbosePrintf ("MAT_MAP_ROTATION chunk found");

				// Read MAT_MAP_OPTIONS chunk
				if (MAT_BUMP_MAP::rRotation.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MAT_BUMP_DISPLAY_PER_CHUNK:
				// Print status
				VerbosePrintf ("MAT_BUMP_DISPLAY_PER chunk found");

				// Read MAT_BUMP_DISPLAY_PER chunk
				if (MAT_BUMP_MAP::dDisplay.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in MAT_BUMP_MAP: %x with size: %d", iChunkID, lChunkLength - CHUNKHEADER_SIZE);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading MAT_BUMP_MAP chunk");

	// Return no error
	return (0);
}

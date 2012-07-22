/*******************************************************************************
* File:		m3dmagic.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/m3dmagic.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			M3DMAGIC ()
*******************************************************************************/
M3DMAGIC::M3DMAGIC ()
{

}

/*******************************************************************************
* Name:			~M3DMAGIC ()
*******************************************************************************/
M3DMAGIC::~M3DMAGIC ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int M3DMAGIC::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading M3DMAGIC chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from M3DMAGIC chunk
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
			case M3D_VERSION_CHUNK:
				// Print status
				VerbosePrintf ("M3D_VERSION chunk found");

				// Read M3D_VERSION chunk
				if (M3DMAGIC::vVersion.Read3DS (lChunkLength - CHUNKHEADER_SIZE,
					bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MDATA_CHUNK:
				// Print status
				VerbosePrintf ("MDATA chunk found");

				// Read MDATA chunk
				if (M3DMAGIC::dData.Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {
					// Return error
					return (-1);
				}
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in M3DMAGIC: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading M3DMAGIC chunk");

	// Return no error
	return (0);
}

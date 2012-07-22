/*******************************************************************************
* File:		light.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/light.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			LIGHT ()
*******************************************************************************/
LIGHT::LIGHT ()
{
	// Initialize member variables
	LIGHT::fX = 0;
	LIGHT::fY = 0;
	LIGHT::fZ = 0;
}

/*******************************************************************************
* Name:			~LIGHT ()
*******************************************************************************/
LIGHT::~LIGHT ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int LIGHT::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 12;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading LIGHT chunk");

	// Check chunk length
	if (iNrOfBytes < (3 * 4))
	{
		// Set error chunk size invalid
		ErrorPrintf ("Chunk size invalid");

		// Return error
		return (-1);
	}

	// Get camera data from chunk
	LIGHT::fX = GetFloat (bp3DSData);
	LIGHT::fY = GetFloat (bp3DSData + 4);
	LIGHT::fZ = GetFloat (bp3DSData + 8);

	// Check chunk length
	if (iNrOfBytes < ((3 * 4) + 6))
	{
		// Return no error
		return (0);
	}
	
	// Get chunks from LIGHT chunk
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
			case COLOR_24_CHUNK:
				// Print status
				VerbosePrintf ("COLOR_24 chunk found");

				// Read COLOR_24 chunk
				if (LIGHT::cColor24.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case LIN_COLOR_24_CHUNK:
				// Print status
				VerbosePrintf ("LIN_COLOR_24 chunk found");

				// Read COLOR_24 chunk
				if (LIGHT::cLinColor24.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case COLOR_F_CHUNK:
				// Print status
				VerbosePrintf ("COLOR_F chunk found");

				// Read COLOR_F chunk
				if (LIGHT::cColorF.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case LIN_COLOR_F_CHUNK:
				// Print status
				VerbosePrintf ("LIN_COLOR_F chunk found");

				// Read COLOR_F chunk
				if (LIGHT::cLinColorF.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case SPOTLIGHT_CHUNK:
				// Print status
				VerbosePrintf ("SPOTLIGHT chunk found");

				// Read SPOTLIGHT chunk
				if (LIGHT::lSpotLight.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case LIGHT_OFF_CHUNK:
				// Print status
				VerbosePrintf ("LIGHT_OFF chunk found");

				// Read LIGHT_OFF chunk
				if (LIGHT::lLightOff.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in LIGHT: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}
	
	// Print status
	VerbosePrintf ("End reading LIGHT chunk");

	// Return no error
	return (0);
}

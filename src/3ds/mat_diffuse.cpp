/*******************************************************************************
* File:		mat_diffuse.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_diffuse.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_DIFFUSE ()
*******************************************************************************/
MAT_DIFFUSE::MAT_DIFFUSE()
{

}

/*******************************************************************************
* Name:			~MAT_DIFFUSE ()
*******************************************************************************/
MAT_DIFFUSE::~MAT_DIFFUSE()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_DIFFUSE::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading MAT_DIFFUSE chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from MAY_AMBIENT chunk
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
				if (MAT_DIFFUSE::cColor24.Read3DS (lChunkLength - 
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
				if (MAT_DIFFUSE::cLinColor24.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in MAT_DIFFUSE: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading MAT_DIFFUSE chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetColor ()
*******************************************************************************/
int MAT_DIFFUSE::GetColor (byte* bRed, byte* bGreen, byte* bBlue)
{
	byte 	bR;		// Red
	byte	bG;		// Green
	byte	bB;		// Blue

	// Get values
	if (cColor24.GetColor (&bR, &bG, &bB) != 0)
	{
		// Return error
		return (-1);
	}
		
	// Set return values
	*bRed 	= bR;
	*bGreen = bG;
	*bBlue	= bB;

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetLinColor ()
*******************************************************************************/
int MAT_DIFFUSE::GetLinColor (byte* bRed, byte* bGreen, byte* bBlue)
{
	byte 	bR;		// Red
	byte	bG;		// Green
	byte	bB;		// Blue

	// Get values
	if (cLinColor24.GetColor (&bR, &bG, &bB) != 0)
	{
		// Return error
		return (-1);
	}
		
	// Set return values
	*bRed 	= bR;
	*bGreen = bG;
	*bBlue	= bB;

	// Return no error
	return (0);
}

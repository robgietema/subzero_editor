/*******************************************************************************
* File:		mat_self_illum.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mat_self_illum.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MAT_SELF_ILLUM ()
*******************************************************************************/
MAT_SELF_ILLUM::MAT_SELF_ILLUM ()
{

}

/*******************************************************************************
* Name:			~MAT_SELF_ILLUM ()
*******************************************************************************/
MAT_SELF_ILLUM::~MAT_SELF_ILLUM ()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MAT_SELF_ILLUM::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading MAT_SELF_ILLUM chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from MAT_SELF_ILLUM chunk
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
				if (MAT_SELF_ILLUM::pIntPercentage.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in MAT_SELF_ILLUM: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading MAT_SELF_ILLUM chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetShininess ()
*******************************************************************************/
int MAT_SELF_ILLUM::GetShininess (int* iPercentage)
{
	int 	iPer;		// Percentage
	
	// Get percentage
	if (pIntPercentage.GetPercentage (&iPer) != 0)
	{
		// return error
		return (-1);
	}
	
	// Set return value
	*iPercentage = iPer;
	
	// Return no error
	return (0);
}

/*******************************************************************************
* File:		n_tri_object.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/n_tri_object.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			N_TRI_OBJECT ()
*******************************************************************************/
N_TRI_OBJECT::N_TRI_OBJECT()
{

}

/*******************************************************************************
* Name:			~N_TRI_OBJECT ()
*******************************************************************************/
N_TRI_OBJECT::~N_TRI_OBJECT()
{

}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int N_TRI_OBJECT::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;	// Pointer to current byte in chunk
	int iChunkID;			// Chunk id
	long lChunkLength;		// Chunk length

	// Print status
	VerbosePrintf ("Begin reading N_TRI_OBJECT chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get chunks from N_TRI_OBJECT chunk
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
			case POINT_ARRAY_CHUNK:
				// Print status
				VerbosePrintf ("POINT_ARRAY chunk found");

				// Read POINT_ARRAY chunk
				if (N_TRI_OBJECT::pPointArray.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case FACE_ARRAY_CHUNK:
				// Print status
				VerbosePrintf ("FACE_ARRAY chunk found");

				// Read FACE_ARRAY chunk
				if (N_TRI_OBJECT::fFaceArray.Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}				
				break;
			case TEX_VERTS_CHUNK:
				// Print status
				VerbosePrintf ("TEX_VERTS chunk found");

				// Read TEX_VERTS chunk
				if (N_TRI_OBJECT::tTexVerts.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case LOCAL_AXIS_CHUNK:
				// Print status
				VerbosePrintf ("LOCAL_AXIS chunk found");

				// Read LOCAL_AXIS chunk
				if (N_TRI_OBJECT::lLocalAxis.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in N_TRI_OBJECT: %x with size: %d", iChunkID, lChunkLength - CHUNKHEADER_SIZE);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading N_TRI_OBJECT chunk");

	// Return no error
	return (0);
}

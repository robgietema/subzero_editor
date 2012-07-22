/*******************************************************************************
* File:		face_array.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/face_array.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			FACE_ARRAY ()
*******************************************************************************/
FACE_ARRAY::FACE_ARRAY()
{
	// Initialize member variables
	FACE_ARRAY::iNrOfFaces 			= 0;
	FACE_ARRAY::iNrOfMshMatGroups 	= 0;
	FACE_ARRAY::fFaces				= NULL;
	FACE_ARRAY::mMshMatGroups		= NULL;
}

/*******************************************************************************
* Name:			~FACE_ARRAY ()
*******************************************************************************/
FACE_ARRAY::~FACE_ARRAY()
{
	// If allocated
	if (FACE_ARRAY::fFaces) {

		// Delete
		delete []FACE_ARRAY::fFaces;
	}

	// If allocated
	if (FACE_ARRAY::mMshMatGroups) {

		// Delete
		delete []FACE_ARRAY::mMshMatGroups;
	}
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int FACE_ARRAY::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iChunkID;				// Chunk id
	long lChunkLength;			// Chunk length
	int iCount;					// Counter
	int iFaceCount;				// Number of faces
	int iMshMatGroupCount = 0;	// Number of msh_mat_groups
	int iCurrentByte;			// Pointer to current byte in buffer

	// Print status
	VerbosePrintf ("Begin reading FACE_ARRAY chunk");

	// Check for zero length
	if (iNrOfBytes < (2 + (2 * 3)))
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Get face count
	iFaceCount = GetShort (bp3DSData);

	// Check if list > 0
	if (iFaceCount > 0) {

		// Allocate face list
		FACE_ARRAY::fFaces = new FACE_3DS[iFaceCount];
	}

	// Print status
	VerbosePrintf ("%d faces found", iFaceCount);

	// Get points from FACE_ARRAY chunk
	for (iCount = 0; iCount < iFaceCount; iCount++) {
		// Get point		
		FACE_ARRAY::fFaces[iCount].iA = GetShort (bp3DSData+2+(iCount*8));
		FACE_ARRAY::fFaces[iCount].iB = GetShort (bp3DSData+2+(iCount*8)+2);
		FACE_ARRAY::fFaces[iCount].iC = GetShort (bp3DSData+2+(iCount*8)+4);
		FACE_ARRAY::fFaces[iCount].iEdge = GetShort (bp3DSData+2+(iCount*8)+6);

		// Print status
		VerbosePrintf ("Face: %d %d %d %d", 
			FACE_ARRAY::fFaces[iCount].iA, FACE_ARRAY::fFaces[iCount].iB,
			FACE_ARRAY::fFaces[iCount].iC, FACE_ARRAY::fFaces[iCount].iEdge);
	}
	
	// Number of faces
	FACE_ARRAY::iNrOfFaces = iFaceCount;

	// Set currentbyte
	iCurrentByte = (iFaceCount * 8) + 2;

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE + iCurrentByte)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Count number of msh_mat_groups
	while (iCurrentByte < iNrOfBytes)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;
		
		// Get chunk length
		lChunkLength = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;
		
		// Print status
		VerbosePrintf ("ChunkID: %x", iChunkID);
		VerbosePrintf ("Chunklength: %d", lChunkLength);
		VerbosePrintf ("NrOfBytes: %d", iNrOfBytes);
		VerbosePrintf ("iCurrentByte: %d", iCurrentByte);
				
		// Check if length is correct
		if (lChunkLength > (iNrOfBytes - iCurrentByte + CHUNKHEADER_SIZE))
		{
			// Set error chunk size invalid
			ErrorPrintf ("Chunk size invalid");

			// Return error
			return (-1);
		}
		
		// Check chunk id
		switch (iChunkID) {

			case MSH_MAT_GROUP_CHUNK:
				// Increase msh_mat_group count
				iMshMatGroupCount++;				
				break;
			default:
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Check if > 0
	if (iMshMatGroupCount > 0) {

		// Allocate msh_mat_group list
		FACE_ARRAY::mMshMatGroups = new MSH_MAT_GROUP[iMshMatGroupCount];
	}

	// Reset current byte
	iCurrentByte = (iFaceCount * 8) + 2;

	// Get chunks from FACE_ARRAY chunk
	while (iCurrentByte < iNrOfBytes)
	{
		// Get chunk id
		iChunkID = Get3DSChunkID (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKID_SIZE;
		
		// Get chunk length
		lChunkLength = GetInt (bp3DSData + iCurrentByte);
		iCurrentByte += CHUNKLENGTH_SIZE;

		// Print status
		VerbosePrintf ("ChunkID: %x", iChunkID);
		VerbosePrintf ("Chunklength: %d", lChunkLength);
		VerbosePrintf ("NrOfBytes: %d", iNrOfBytes);
		VerbosePrintf ("iCurrentByte: %d", iCurrentByte);
				
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
			case MSH_MAT_GROUP_CHUNK:
				// Print status
				VerbosePrintf ("MSH_MAT_GROUP chunk found");

				// Read MSH_MAT_GROUP chunk
				if (FACE_ARRAY::mMshMatGroups[iNrOfMshMatGroups].Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}
				
				// Increase number of msh_mat_groups
				FACE_ARRAY::iNrOfMshMatGroups++;
				break;
			case FACE_SMOOTHING_CHUNK:
				// Print status
				VerbosePrintf ("FACE_SMOOTHING chunk found");

				// Read FACE_SMOOTHING chunk
				if (FACE_ARRAY::sFaceSmoothing.Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte, iFaceCount) != 0) {

					// Return error
					return (-1);
				}
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in FACEARRAY: %x with size: %d", iChunkID, lChunkLength - CHUNKHEADER_SIZE);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading FACE_ARRAY chunk");

	// Return no error
	return (0);
}

/*******************************************************************************
* Name:			GetFaces ()
*******************************************************************************/
int FACE_ARRAY::GetFaces (int* iNrOfFaces, FACE_MAT** fFaces)
{
	FACE_MAT*	fFaceList;		// List of faces
	int 		iCount1;		// Counter
	int			iCount2;		// Counter
	char		acMaterial[16];	// Material name

	// Allocate facelist
	fFaceList = new FACE_MAT[FACE_ARRAY::iNrOfFaces];

	// Build faces / materials list
	for (iCount1 = 0; iCount1 < FACE_ARRAY::iNrOfFaces; iCount1++)
	{
		// Set a,b,c and edge values in list
		fFaceList[iCount1].iA 		= FACE_ARRAY::fFaces[iCount1].iA;
		fFaceList[iCount1].iB 		= FACE_ARRAY::fFaces[iCount1].iB;
		fFaceList[iCount1].iC 		= FACE_ARRAY::fFaces[iCount1].iC;
		fFaceList[iCount1].iEdge 	= FACE_ARRAY::fFaces[iCount1].iEdge;
		
		// Initialize material name
		strcpy (fFaceList[iCount1].acMat, "");
		
		// Find material in material list
		for (iCount2 = 0; iCount2 < FACE_ARRAY::iNrOfMshMatGroups; iCount2++)
		{
			// Get material name
			FACE_ARRAY::mMshMatGroups[iCount2].GetMaterialName 
				(iCount1, acMaterial);
			
			// Check if empty string is returned
			if (strcmp (acMaterial, "") != 0)
			{
				// Set material name in list
				strcpy (fFaceList[iCount1].acMat, acMaterial);
			}
		}
	}

	// Set return values
	*iNrOfFaces = FACE_ARRAY::iNrOfFaces;
	*fFaces = fFaceList;

	// return no error
	return (0);
}

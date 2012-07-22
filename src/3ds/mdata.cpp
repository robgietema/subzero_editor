/*******************************************************************************
* File:		mdata.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/3ds/mdata.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* Name:			MDATA ()
*******************************************************************************/
MDATA::MDATA()
{
	// Initialize member variables
	MDATA::iNrOfMatEntries 	 = 0;
	MDATA::iNrOfNamedObjects = 0;
	MDATA::eMatEntry = NULL;
	MDATA::oNamedObject = NULL;
}

/*******************************************************************************
* Name:			~MDATA ()
*******************************************************************************/
MDATA::~MDATA()
{
	// If allocated
	if (MDATA::eMatEntry) {

		// Delete
		delete []MDATA::eMatEntry;
	}

	// If allocated
	if (MDATA::oNamedObject) {

		// Delete
		delete []MDATA::oNamedObject;
	}
}

/*******************************************************************************
* Name:			Read3DS ()
*******************************************************************************/
int MDATA::Read3DS (int iNrOfBytes, byte* bp3DSData)
{
	int iCurrentByte = 0;		// Pointer to current byte in chunk
	int iChunkID;				// Chunk id
	long lChunkLength;			// Chunk length
	int iMatEntryCount = 0;		// Number of material entries in buffer
	int iNamedObjectCount = 0;	// Number of named objects in buffer
	int iUnknown = 0;

	// Print status
	VerbosePrintf ("Begin reading MDATA chunk");

	// Check for zero length
	if (iNrOfBytes <= CHUNKHEADER_SIZE)
	{
		// Set error file contains no data
		ErrorPrintf ("File contains no data");

		// Return error
		return (-1);
	}

	// Print status
	VerbosePrintf ("Counting subchunks in MDATA chunk");

	// Count number of matentries and named objects
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
			case MAT_ENTRY_CHUNK:
				// Increase material entry count
				iMatEntryCount++;				
				break;
			case NAMED_OBJECT_CHUNK:
				// Increase named object count
				iNamedObjectCount++;
				break;
			default:
				iUnknown++;
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("Total subchunks: %d", iNamedObjectCount+iMatEntryCount+iUnknown);

	// Check if > 0
	if (iMatEntryCount > 0) {

		// Allocate material entry list
		eMatEntry = new MAT_ENTRY[iMatEntryCount];
	}

	// Check if > 0
	if (iNamedObjectCount > 0) {

		// Allocate named object list
		oNamedObject = new NAMED_OBJECT[iNamedObjectCount];
	}

	// Reset current byte
	iCurrentByte = 0;

	// Get chunks from MDATA chunk
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
			case MESH_VERSION_CHUNK:
				// Print status
				VerbosePrintf ("MESH_VERSION chunk found");

				// Read MESH_VERSION chunk
				if (MDATA::vMeshVersion.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}				
				break;
			case MASTER_SCALE_CHUNK:
				// Print status
				VerbosePrintf ("MASTER_SCALE chunk found");

				// Read MASTER_SCALE chunk
				if (MDATA::sMasterScale.Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}
				break;
			case MAT_ENTRY_CHUNK:
				// Print status
				VerbosePrintf ("MAT_ENTRY chunk found");

				// Read MAT_ENTRY chunk
				if (MDATA::eMatEntry[iNrOfMatEntries].Read3DS (lChunkLength - 
					CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0)
				{
					// Return error
					return (-1);
				}
				
				// Increase number of material entries
				iNrOfMatEntries++;
				break;
			case NAMED_OBJECT_CHUNK:
				// Print status
				VerbosePrintf ("NAMED_OBJECT chunk found");

				// Read NAMED_OBJECT chunk
				if (MDATA::oNamedObject[iNrOfNamedObjects].Read3DS (lChunkLength - CHUNKHEADER_SIZE, bp3DSData + iCurrentByte) != 0) {

					// Return error
					return (-1);
				}
				
				// Increase number of named objects
				iNrOfNamedObjects++;
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found in MDATA: %x", iChunkID);
				break;
		}
		
		// Set pointer
		iCurrentByte += (lChunkLength - CHUNKHEADER_SIZE);
	}

	// Print status
	VerbosePrintf ("End reading MDATA chunk");

	// Return no error
	return (0);
}

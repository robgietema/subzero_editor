/*******************************************************************************
* File:		lg_objectlib.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		1 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/objectlib/lg_objectlib.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGObjectLib::LGObjectLib
*******************************************************************************/
LGObjectLib::LGObjectLib () {
	LGObjectLib::iNrOfObjects = 0;
	LGObjectLib::opObjects = NULL;
}

/*******************************************************************************
* LGObjectLib::~LGObjectLib
*******************************************************************************/
LGObjectLib::~LGObjectLib () {

	// If allocated
	if (LGObjectLib::opObjects) {

		// Delete
		delete []LGObjectLib::opObjects;
	}
}

/*******************************************************************************
* LGObjectLib::readFromFile
*******************************************************************************/
int LGObjectLib::readFromFile (char* cpFilename) {
	int		iCurrentByte=0;		// Current byte in the buffer
	int		iFileLength;		// Length of the file
	FILE*	fpFile;				// Input file
	byte*	bpData;				// Buffer
	int		iChunkID;			// Chunk ID
	int		iChunkSize;			// Chunk size
	int		iCurrentObject=0;	// Current sub object

	// Open file
	if ((fpFile  = fopen (cpFilename, "rb" )) == NULL) {

		// Print error
		ErrorPrintf ("Input file could not be opened");

		// Return error
		return (-1);
	}

	// Get file length
	fseek (fpFile, 0, SEEK_END);
	iFileLength = ftell (fpFile);

	// Reset file pointer to begin
	fseek (fpFile, 0, SEEK_SET);

	// Allocate buffer
	bpData = new byte[iFileLength];

	// Read buffer
	fread (bpData, sizeof (char), iFileLength, fpFile);

	// Check header
	if (strncmp ((char*)bpData, "OBL", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Read number of objects
		LGObjectLib::iNrOfObjects = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Check if > 0
		if (LGObjectLib::iNrOfObjects > 0) {

			// Alloc objects
			LGObjectLib::opObjects = new LGObject[LGObjectLib::iNrOfObjects];
		}

		// Print status
		VerbosePrintf ("Number of objects: %d", LGObjectLib::iNrOfObjects);

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no objectlib file");

		// Return error
		return (-1);
	}

	// Get other chunks
	while (iCurrentByte < iFileLength) {
		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "OBJ", 3) == 0) iChunkID = OBJ_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += SIZE_CHUNKID;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;

		// Read chunk
		switch (iChunkID) {
			case OBJ_ID:
				// Print status
				VerbosePrintf ("OBJ chunk found");
				
				// Read objects
				LGObjectLib::opObjects[iCurrentObject].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT);

				// Inc current object
				iCurrentObject++;
				break;
			default:
				// Print status
				VerbosePrintf ("Read Scene: Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += (iChunkSize - SIZE_CHUNKID - SIZE_INT);
	}
	
	// Free buffer
	delete []bpData;
	
	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectLib::initDefaultValues
*******************************************************************************/
int LGObjectLib::initDefaultValues () {

	// Print status
	VerbosePrintf ("Init objectlib values");

	// Set default values
	LGObjectLib::iNrOfObjects = 1;
	LGObjectLib::opObjects = new LGObject[LGObjectLib::iNrOfObjects];

	// Init objects
	LGObjectLib::opObjects[0].initDefaultValues ();

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectLib::writeToFile
*******************************************************************************/
int LGObjectLib::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wb"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header id
	PrintChunkID (fpFile, "OBL");

	// Print chunk size
	PrintInt (fpFile, LGObjectLib::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGObjectLib::iNrOfObjects);

	// Print objects
	for (int iCount = 0; iCount < LGObjectLib::iNrOfObjects; iCount++) {

		// Write object
		LGObjectLib::opObjects[iCount].write (fpFile);
	}

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectLib::getChunkHeaderSize
*******************************************************************************/
int LGObjectLib::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;	// Chunk id
	iChunkHeaderSize += SIZE_INT;		// Chunk size
	iChunkHeaderSize += SIZE_INT;		// Number of objects

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGObjectLib::getChunkSize
*******************************************************************************/
int LGObjectLib::getChunkSize () {
	int iChunkSize = LGObjectLib::getChunkHeaderSize ();		// Chunk size

	// Add subobjects sizes
	for (int iCount = 0; iCount < LGObjectLib::iNrOfObjects; iCount++) {

		// Add object size
		iChunkSize += LGObjectLib::opObjects[iCount].getChunkSize ();
	}

	// Return chunk size
	return (iChunkSize);
}

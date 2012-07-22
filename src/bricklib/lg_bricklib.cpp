/*******************************************************************************
* File:		lg_bricklib.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		20 November 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/bricklib/lg_bricklib.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGBrickLib::LGBrickLib
*******************************************************************************/
LGBrickLib::LGBrickLib () {

	// Init values
	LGBrickLib::iNrOfEntries = 0;
	LGBrickLib::epBricks = NULL;
}

/*******************************************************************************
* LGBrickLib::~LGBrickLib
*******************************************************************************/
LGBrickLib::~LGBrickLib () {

	// If allocated
	if (LGBrickLib::epBricks) {

		// Delete
		delete []LGBrickLib::epBricks;
	}
}

/*******************************************************************************
* LGBrickLib::readFromFile
*******************************************************************************/
int LGBrickLib::readFromFile (char* cpFilename) {
	int		iCurrentByte=0;			// Current byte in the buffer
	int		iFileLength;			// Length of the file
	FILE*	fpFile;					// Input file
	byte*	bpData;					// Buffer
	int		iChunkID;				// Chunk ID
	int		iChunkSize;				// Chunk size
	int		iCurrentEntry=0;		// Current sub object

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
	if (strncmp ((char*)bpData, "BLB", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iCurrentByte += 4;

		// Read number of objectgroups
		LGBrickLib::iNrOfEntries = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Check if > 0
		if (LGBrickLib::iNrOfEntries > 0) {

			// Alloc entries
			LGBrickLib::epBricks = new LGBrickLibEntry[LGBrickLib::iNrOfEntries];
		}

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no bricklib file");

		// Return error
		return (-1);
	}

	// Get other chunks
	while (iCurrentByte < iFileLength) {
		// Get chunk id
		if (strncmp ((char*)(bpData + iCurrentByte), "BEN", 3) == 0) iChunkID = BEN_ID;
		else iChunkID = UNKNOWN_ID;
		iCurrentByte += 3;

		// Get chunk size
		iChunkSize = GetInt (bpData + iCurrentByte);
		iCurrentByte += 4;

		// Read chunk
		switch (iChunkID) {
			case BEN_ID:
				// Print status
				VerbosePrintf ("BEN chunk found");

				// Read objects
				LGBrickLib::epBricks[iCurrentEntry].read (bpData + iCurrentByte, iChunkSize - SIZE_CHUNKID - SIZE_INT);

				// Load textures
				LGBrickLib::epBricks[iCurrentEntry].loadTextures ();

				// Inc current entries
				iCurrentEntry++;
				break;
			default:
				// Print status
				VerbosePrintf ("Unknown chunk found");
				break;
		}

		// Set current byte
		iCurrentByte += iChunkSize;
	}

	// Free buffer
	delete []bpData;
	
	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLib::initDefaultValues
*******************************************************************************/
int LGBrickLib::initDefaultValues () {

	// Values
	LGBrickLib::iNrOfEntries = 95;

	// Alloc entries
	LGBrickLib::epBricks = new LGBrickLibEntry[LGBrickLib::iNrOfEntries];

	// Init brick
	for (int iCount = 0; iCount < LGBrickLib::iNrOfEntries; iCount++) {

		LGBrickLib::epBricks[iCount].initDefaultValues (iCount);
		LGBrickLib::epBricks[iCount].loadTextures ();
	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLib::writeToFile
*******************************************************************************/
int LGBrickLib::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wb"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header id
	PrintChunkID (fpFile, "BLB");

	// Print chunk size
	PrintInt (fpFile, LGBrickLib::getChunkSize ());

	// Print number of objects
	PrintInt (fpFile, LGBrickLib::iNrOfEntries);

	// Print objects
	for (int iCount = 0; iCount < LGBrickLib::iNrOfEntries; iCount++) {

		// Write object
		LGBrickLib::epBricks[iCount].write (fpFile);
	}

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLib::draw
*******************************************************************************/
int LGBrickLib::draw (int iEntry, int iColor) {

	// Draw brick
	LGBrickLib::epBricks[iEntry].draw (iColor);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGBrickLib::getChunkHeaderSize
*******************************************************************************/
int LGBrickLib::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Number of entries

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGBrickLib::getChunkSize
*******************************************************************************/
int LGBrickLib::getChunkSize () {
	int iChunkSize = LGBrickLib::getChunkHeaderSize ();		// Chunk size

	// Add subobjects sizes
	for (int iCount = 0; iCount < LGBrickLib::iNrOfEntries; iCount++) {

		// Add object size
		iChunkSize += LGBrickLib::epBricks[iCount].getChunkSize ();
	}

	// Return chunk size
	return (iChunkSize);
}

/*******************************************************************************
* LGBrickLib::getBlockIndex
*******************************************************************************/
int LGBrickLib::getBlockIndex (int iBlockNumber) {
	int iIndex = -1;		// Index
	int iCount;				// Counter

	// Find block
	for (iCount = 0; iCount < LGBrickLib::iNrOfEntries; iCount++) {

		// If match
		if (LGBrickLib::epBricks[iCount].iBlockNumber == iBlockNumber) {
			
			// Set index
			iIndex = iCount;
		}
	}

	// Return index
	return (iIndex);
}

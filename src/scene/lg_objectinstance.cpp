/*******************************************************************************
* File:		lg_objectinstance.cpp
* Author:	Tycoon (tycoon@planetdescent.com)
* Date:		3 December 2003
*******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////
#include "../../include/scene/lg_objectinstance.h"
#include "../../include/objectlib/lg_objectlib.h"
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

/*******************************************************************************
* LGObjectInstance::LGObjectInstance
*******************************************************************************/
LGObjectInstance::LGObjectInstance () {

	// Init values
	LGObjectInstance::vOffset.fX = 0.0f;
	LGObjectInstance::vOffset.fY = 0.0f;
	LGObjectInstance::vOffset.fZ = 0.0f;
	LGObjectInstance::iTime = 0;
	LGObjectInstance::iObject = 0;
}

/*******************************************************************************
* LGObjectInstance::~LGObjectInstance
*******************************************************************************/
LGObjectInstance::~LGObjectInstance () {
}

/*******************************************************************************
* LGObjectInstance::initDefaultValues
*******************************************************************************/
int LGObjectInstance::initDefaultValues (LGVertex3f vOffset, int iTime) {

	// Print status
	VerbosePrintf ("Init object with time: %d", iTime);

	// Set values
	LGObjectInstance::iTime = iTime;
	LGObjectInstance::vOffset = vOffset;
	LGObjectInstance::iObject = 0;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::readFromFile
*******************************************************************************/
int LGObjectInstance::readFromFile (char* cpFilename) {
	int		iCurrentByte=0;			// Current byte in the buffer
	int		iFileLength;			// Length of the OOF file
	FILE*	fpFile;					// Input file
	byte*	bpData;					// Buffer

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
	if (strncmp ((char*)bpData, "OBI", 3) == 0) {

		// Set current byte
		iCurrentByte += 3;

		// Skip Chunksize
		iCurrentByte += 4;

		// Get properties
		LGObjectInstance::iTime = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;
		LGObjectInstance::vOffset = GetVertex3f (bpData + iCurrentByte);
		iCurrentByte += SIZE_VERTEX3F;
		LGObjectInstance::iObject = GetInt (bpData + iCurrentByte);
		iCurrentByte += SIZE_INT;

	// No header found
	} else {
		// Print error
		ErrorPrintf ("This is no objectinstance file");

		// Return error
		return (-1);
	}

	// Free buffer
	delete []bpData;
	
	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::read
*******************************************************************************/
int LGObjectInstance::read (byte* bpData, int iDataSize) {
	int iCurrentByte=0;			// Current byte
	int iCurrentObjectGroup=0;	// Current object group
	int iChunkID=0;				// Chunk ID
	int iChunkSize=0;			// Chunk size

	// Print status
	VerbosePrintf ("Begin OBI");

	// Get variables from buffer
	LGObjectInstance::iTime = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;
	LGObjectInstance::vOffset = GetVertex3f (bpData + iCurrentByte);
	iCurrentByte += SIZE_VERTEX3F;
	LGObjectInstance::iObject = GetInt (bpData + iCurrentByte);
	iCurrentByte += SIZE_INT;

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::writeToFile
*******************************************************************************/
int LGObjectInstance::writeToFile (char* cpFilename) {
	FILE* fpFile;		// Output file

	// Open output file
	if (!(fpFile = fopen (cpFilename, "wb"))) {

		// Print error
		printf ("Error opening file: %s", cpFilename);

		// Return error
		return (-1);
	}

	// Print header id
	PrintChunkID (fpFile, "OBI");

	// Print chunk size
	PrintInt (fpFile, LGObjectInstance::getChunkSize ());

	// Print properties
	PrintInt (fpFile, LGObjectInstance::iTime);
	PrintVertex3f (fpFile, LGObjectInstance::vOffset);
	PrintInt (fpFile, LGObjectInstance::iObject);

	// Close file
	fclose (fpFile);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::write
*******************************************************************************/
int LGObjectInstance::write (FILE* fpFile) {

	// Print header id
	PrintChunkID (fpFile, "OBJ");

	// Print chunk size
	PrintInt (fpFile, LGObjectInstance::getChunkSize ());

	// Print properties
	PrintInt (fpFile, LGObjectInstance::iTime);
	PrintVertex3f (fpFile, LGObjectInstance::vOffset);
	PrintInt (fpFile, LGObjectInstance::iObject);

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::getChunkHeaderSize
*******************************************************************************/
int LGObjectInstance::getChunkHeaderSize () {
	int iChunkHeaderSize = 0;		// Chunk size

	// Add chunk fields
	iChunkHeaderSize += SIZE_CHUNKID;		// Id
	iChunkHeaderSize += SIZE_INT;			// Chunk size
	iChunkHeaderSize += SIZE_INT;			// Time
	iChunkHeaderSize += SIZE_VERTEX3F;		// Offset
	iChunkHeaderSize += SIZE_INT;			// Object

	// Return chunk size
	return (iChunkHeaderSize);
}

/*******************************************************************************
* LGObjectInstance::getChunkSize
*******************************************************************************/
int LGObjectInstance::getChunkSize () {
	int iChunkSize = LGObjectInstance::getChunkHeaderSize ();		// Chunk size

	// Return chunk size
	return (iChunkSize);
}

/*******************************************************************************
* LGObjectInstance::draw
*******************************************************************************/
int LGObjectInstance::draw (int iFrame) {
	extern LGObjectLib oObjectLib;	// Objectlib

	// If anim start
//	if ((iFrame >= LGObjectInstance::iTime) && (iFrame < LGObjectInstance::iTime + LGObjectInstance::iAnimLength)) {

		// Draw object
		oObjectLib.opObjects[LGObjectInstance::iObject].draw (iFrame - LGObjectInstance::iTime);

	// Else and of anim
//	} else if (iFrame >= LGObjectInstance::iTime + LGObjectInstance::iAnimLength) {

		// Draw static model
//		LGObjectInstance::drawStatic ();
//	}

	// Return no error
	return (0);
}

/*******************************************************************************
* LGObjectInstance::drawStatic
*******************************************************************************/
int LGObjectInstance::drawStatic () {

	// Todo

	// Return no error
	return (0);
}

